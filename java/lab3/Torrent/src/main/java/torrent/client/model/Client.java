package torrent.client.model;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jetbrains.annotations.NotNull;
import torrent.client.controller.TorrentController;
import torrent.common.ByteArrayWrapper;
import torrent.common.FileLoader;
import torrent.common.Peer;
import torrent.protocol.BTMessages;
import torrent.protocol.MessageID;
import torrent.protocol.Parser;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.ProtocolException;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.ClosedSelectorException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.PriorityBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;




public class Client {

    private final static Logger logger = LogManager.getLogger(Client.class);
    private final byte[] myID;
    ConcurrentLinkedQueue<InetSocketAddress> peers;
    Map<ByteArrayWrapper, Parser> files;
    PriorityBlockingQueue<Peer> priorityPeers = new PriorityBlockingQueue<>();
    Thread connectingThread = null;
    Thread scatteringThread = null;

    //CountDownLatch latchScatter
    //final ReentrantLock lockConnecting = new ReentrantLock(), lockScatter = new ReentrantLock();
    //final Condition

    private final TorrentController controller;
    int myServerPort;
    boolean standard;
    public Client(byte[] ID, Map<ByteArrayWrapper, Parser> torrents, TorrentController controller, int localServerPort, boolean standardMode) {
        myID = ID;
        files = torrents;
        this.controller = controller;
        myServerPort = localServerPort;
        standard = standardMode;


    }
    public void start(@NotNull Parser parser)  {
        logger.info("Start load " + parser.getName());
        BitSet piecesInfo;
        try {
            piecesInfo = checkPieces(parser);
            if (piecesInfo.nextClearBit(0) == parser.getPiecesHash().size()) {
                System.out.println("!!!!!!");
            }
        } catch (IOException ex) {
            logger.fatal("Exception in loadPieces: " + ex.getMessage());
            return;
        }
        downloadFile(parser, piecesInfo);
    }
    private void downloadFile(@NotNull Parser parser, BitSet piecesInfo)  {
        Selector selector;
        try {
            selector = Selector.open();
        } catch (IOException ex) {
            logger.fatal("Cant open readable selector. " + ex.getMessage());
            return;
        }
        peers = getPeers();

        CountDownLatch latch = new CountDownLatch(1);
        connectingThread = connecting(parser.getFileHash(), selector, latch);

        try(RandomAccessFile file = new RandomAccessFile(FileLoader.getDownloadFile(parser.getName(), standard ? -1 : myServerPort), "rw")) {
            AtomicInteger tasksCount = new AtomicInteger(0);

            while(!(piecesInfo.get(0) && piecesInfo.nextClearBit(0) == parser.getPiecesHash().size())) { // есть не скачанный кусок
                if (Thread.currentThread().isInterrupted()) { break; }
                logger.debug("First while iteration");

                if (selector.keys().size() == 0) {
                    logger.debug("Wait connections peers");
                    try {
                        latch.await();
                    } catch (InterruptedException e) {
                        logger.fatal("Interrupt connect.");
                        break;
                    }
                }
                scatterPieces(piecesInfo, parser, tasksCount, selector);

                while (tasksCount.get() > 0 || scatteringThread.isAlive()) {
                    logger.debug("@@@ " + tasksCount.get() + " " + scatteringThread.isAlive());
                    if (Thread.currentThread().isInterrupted()) { break; }
                    logger.debug("Second while iteration.");
                    if (0 == selector.keys().size()) { // нет подключенных пиров(селектор подключенных пиров пуст)
                        scatteringThread.interrupt();
                        break;
                    }
                    try {
                        selector.select();
                    } catch (ClosedSelectorException ex) {
                        continue;
                    }



                    var channelsKeys = selector.selectedKeys();
                    logger.debug("Select " + channelsKeys.size() + " channels.");
                    for (var key : channelsKeys) {
                        var inputChanel = (SocketChannel) key.channel();
                        boolean checkKey = true;

                        for (var peer : priorityPeers) {
                            if (peer.getSocketChannel().equals(inputChanel)) {
                                logger.debug("@@ " + peer.getTasksCount().get());
                            }
                            if (peer.getSocketChannel().equals(inputChanel) && peer.getTasksCount().get() == 0) {
                               checkKey = false;
                            }
                        }

                        if (!checkKey) {
                            logger.debug("Empty socket.");
                            continue;
                        }


                        SocketAddress address;
                        try {
                            address = inputChanel.getRemoteAddress();
                        } catch (IOException ex) {
                            logger.debug("Server disconnect (getRemoteAddress). ??????????????");
                            continue;
                        }


                        ByteBuffer message;
                        try {
                            message = Peer.getMessage(inputChanel);
                            if (message == null) continue;
                        } catch (IOException ex) {
                            logger.info("Peer " + address + " disconnect." + tasksCount.get());
                            /////////////////////////////////////////////////////////////
                            priorityPeers.forEach((peer) -> {
                                if (peer.getSocketChannel().equals(inputChanel)) {
                                    priorityPeers.remove(peer);
                                    tasksCount.set(tasksCount.get() - peer.getTasksCount().get());
                                    peer.getTasksCount().set(0);
                                }
                            });
                            logger.info("Peer " + address + " disconnect2. " + tasksCount.get());
                            key.cancel();
                            inputChanel.close();
                            //latchScatter = new CountDownLatch(1);
                            //latchConnect = new CountDownLatch(1);
                            peers.add((InetSocketAddress) address);
                            continue;
                        }

                        switch (BTMessages.getType(message)) {
                            case UN_CHOKE -> logger.info("Server " + address + " send UN_CHOKE message. Continue.");
                            case PIECE -> {message.flip();
                                var pieceNum = message.getInt();
                                logger.info("Recv piece num " + pieceNum);
                                var beginPos = message.getInt();
                                byte[] tmp = new byte[(int) parser.getPieceLength().longValue()];
                                message.get(tmp);

                                byte[] piece;
                                if (pieceNum == (int) Math.ceil((double) parser.getLength() / (double) parser.getPieceLength()) - 1 && parser.getPaddingSize() > 0) {
                                    piece = Arrays.copyOf(tmp, (int) (parser.getPieceLength() - parser.getPaddingSize()) - beginPos);
                                } else {
                                    piece = tmp;
                                }
                                var referenceHash = parser.getPiecesHash().get(pieceNum);
                                MessageDigest sha1;
                                try {
                                    sha1 = MessageDigest.getInstance("SHA-1");
                                } catch (NoSuchAlgorithmException e) {
                                    throw new RuntimeException(e);
                                }

                                var pieceHash = sha1.digest(piece);
                                if (!Arrays.equals(referenceHash, pieceHash)) {
                                    logger.error("Peer: " + address +
                                            ". Wrong hash of piece " + pieceNum +
                                            ". Recv: " + HexFormat.of().formatHex(pieceHash) +
                                            ". Reference: " + HexFormat.of().formatHex(referenceHash));
                                    logger.fatal(Arrays.toString(piece));
                                    logger.fatal(piece.length + " " + parser.getPieceLength());
                                    refreshTask(priorityPeers, pieceNum, parser, tasksCount);
                                    continue;
                                }
                                file.seek(pieceNum * parser.getPieceLength() + beginPos);
                                file.write(piece);
                                piecesInfo.set(pieceNum);
                                controller.getDownloadedPiece().incrementAndGet();
                                tasksCount.decrementAndGet();
                                priorityPeers.forEach((peer) -> {
                                    if (peer.getSocketChannel().equals(inputChanel)) {
                                        peer.getTasksCount().decrementAndGet();
                                    }
                                });
                            }
                            case CHOKE -> logger.info("Server " + address + "send CHOKE. Ignore. haha");
                            case KEEP_ALIVE -> logger.info("Server " + address + "send KA message.");
                            case UNDEFINED -> logger.error("Server " + address + "send UNDEFINED message.");
                            default -> logger.info("Server " + address + "send message (default brunch).");
                        }
                    }
                }
            }
        } catch (IOException ex) {
            logger.fatal("Exception on read loop " + ex.getMessage());
        }
        logger.info("End download. Interrupt connecting thread, close all SocketChannels.");
        System.out.println(scatteringThread.isAlive() + " " + connectingThread.isAlive());
        if (scatteringThread.isAlive()) { scatteringThread.interrupt(); }
        if (connectingThread.isAlive()) { connectingThread.interrupt(); }
        for (var key : selector.keys()) {
            try {
                key.channel().close();
            } catch (IOException ex) {
                logger.fatal("Exception on close channel: " + ex.getMessage());
            }
            key.cancel();
        }
        System.out.println("end load");
        System.out.flush();
    }
    private void refreshTask(@NotNull PriorityBlockingQueue<Peer> priorityPeers, int pieceNum, Parser parser, AtomicInteger tasksCount) {
        for (var peer :  priorityPeers) {
            try {
                if (peer.getBitField().get(pieceNum)) {
                    if (!peer.sendRequest(pieceNum, parser.getPieceLength())) {
                        priorityPeers.remove(peer);
                        logger.info("Peer: " + peer.getSocketChannel().getRemoteAddress() + " disconnected.");
                    } else {
                        tasksCount.incrementAndGet();
                        peer.getTasksCount().incrementAndGet();
                        priorityPeers.remove(peer);
                        priorityPeers.add(peer);
                        break;
                    }
                }
            } catch (IOException ex) {
                logger.fatal("Peer cant refreshTask " + ex.getMessage());
            }
        }
    }
    private void scatterPieces(@NotNull BitSet piecesInfo, Parser parser, AtomicInteger tasksCount, Selector selector) {
       Runnable scatter = () -> {
            logger.info("Start scatter. " + parser.getPiecesHash().size());
            boolean scatterB = false;
            while (!scatterB) {
                for (int currentBit = 0; currentBit < parser.getPiecesHash().size(); currentBit++) {
                    if (Thread.currentThread().isInterrupted()) {
                        scatterB = true;
                        break;
                    }
                    if (piecesInfo.get(currentBit)) {
                        continue;
                    }
                    for (var peer : priorityPeers) {
                        try {
                            if (!peer.getBitField().get(currentBit)) {
                                continue;
                            }
                            if (!peer.sendRequest(currentBit, parser.getPieceLength())) {
                                priorityPeers.remove(peer);
                                tasksCount.set(tasksCount.get() - peer.getTasksCount().get());
                                logger.info("Peer: " + peer.getSocketChannel().getRemoteAddress() + " disconnected.");
                                continue;
                            }
                            logger.debug("Request piece num " + currentBit + ". Peer: " + peer.getSocketChannel().getRemoteAddress());
                            tasksCount.incrementAndGet();
                            peer.getTasksCount().incrementAndGet();
                            logger.fatal("&&&&& " + tasksCount.get() + " " + peer.getTasksCount().get());
                            priorityPeers.remove(peer);
                            priorityPeers.add(peer);
                            selector.wakeup();
                            scatterB = true;
                            break;
                        } catch (IOException ex) {
                            logger.fatal("Peer cant send request " + ex.getMessage());
                        }
                    }
                }
            }
            System.out.println("scattering interrupt");
            System.out.flush();
            logger.info("End scatter.");

       };

        scatteringThread = new Thread(scatter, "ScatterPieces thread");
        scatteringThread.start();
        System.out.println("start " + connectingThread.isAlive());
    }
    private @NotNull Thread connecting(byte[] fileHash, Selector finishConnectSelector, CountDownLatch latch) {
        Runnable connectingTask = () -> {
            Selector waitConnection;
            try {
                waitConnection = Selector.open();
            } catch (IOException ex) {
                logger.fatal("Cant open selector: waitConnections. " + ex.getMessage());
                throw new RuntimeException("Cant open selector: waitConnections");
            }
            while (!Thread.currentThread().isInterrupted()) {
                try {
                    if (!peers.isEmpty()) {
                        SocketChannel socketChannel = SocketChannel.open();
                        var connectAddress = peers.remove();
                        //logger.debug("ConnectAddress: " + connectAddress.getAddress() + ":" + connectAddress.getPort());
                        socketChannel.configureBlocking(false);
                        socketChannel.connect(connectAddress);
                        socketChannel.register(waitConnection, SelectionKey.OP_CONNECT);
                    }
                    if (0 != waitConnection.select(100)) {
                        for (var key : waitConnection.selectedKeys()) {
                            var tmpChannel = (SocketChannel) key.channel();
                            var address = tmpChannel.getRemoteAddress();
                            try {
                                tmpChannel.finishConnect();
                            } catch (IOException ex) {
                                peers.add((InetSocketAddress) address);
                                continue;
                            }

                            if (tmpChannel.isConnected()) {
                                try {
                                    firstContact(tmpChannel, fileHash);
                                } catch (ProtocolException ex) {
                                    logger.info(ex.getMessage() + " Ignore this peer.");
                                    tmpChannel.close();
                                    continue;
                                } catch (IOException ex ) {
                                    logger.error(address + " " + ex.getMessage() + " Reconnecting.");
                                    peers.add((InetSocketAddress) address);
                                    tmpChannel.close();
                                    continue;
                                } finally {
                                    key.cancel();
                                }
                                tmpChannel.register(finishConnectSelector, SelectionKey.OP_READ);
                                latch.countDown();
                            }
                        }
                    }
                } catch (IOException ex) {
                    logger.fatal("Error in while loop. " + ex.getMessage());
                    ex.printStackTrace();
                }
            }
            System.out.println("interrupt connections");
            System.out.flush();
        };
        var thread = new Thread(connectingTask, "Connections thread");
        thread.start();
        return thread;
    }

    private boolean firstContact(@NotNull SocketChannel channel, byte[] fileHash) throws IOException {
        InetSocketAddress socketAddress = (InetSocketAddress) channel.getRemoteAddress();
        logger.info("Peer:" + socketAddress.getAddress() + " connecting is " + channel.isConnected());
        channel.write(ByteBuffer.wrap(BTMessages.genHandShake(fileHash, myID)));

        ByteBuffer response = ByteBuffer.allocate(68);
        while (response.position() != response.limit()) {
            channel.read(response);
        }
        response.flip();

        if (BTMessages.getType(response) != MessageID.HANDSHAKE) {
            throw new ProtocolException("Server: " + socketAddress + " responded with not a handshake.");
        }
        logger.info("Server: " + channel.getRemoteAddress() + " responded with a handshake.");

        response.position(28);
        response.limit(68);
        byte[] serverFileHash = new byte[20];
        response.get(serverFileHash);
        if (!Arrays.equals(serverFileHash, fileHash)) {
            throw new ProtocolException("Server" + socketAddress + "responded wrong hashFile");
        }

        Peer peer = new Peer(channel);
        ByteBuffer message;
        while ((message = Peer.getMessage(peer.getSocketChannel())) == null) {

        }
        if (BTMessages.getType(message) != MessageID.BITMAP) {
            throw new ProtocolException("Server: " + socketAddress + " responded with not a bitmap.");
        }
        logger.info("Server: " + channel.getRemoteAddress() + " responded with a bitmap.");

        peer.setBitField(BitSet.valueOf(message.array()));
        peer.getSocketChannel().write(ByteBuffer.wrap(BTMessages.genInterested()));



        priorityPeers.add(peer);
        return true;
    }
    private @NotNull Parser foundFile(File torrent) throws IOException {
        var parser = new Parser(torrent);
        var fileHash = new ByteArrayWrapper(parser.getFileHash());
        boolean fileIsFound = false;
        for (var i : files.keySet()) {
            if (i.equals(fileHash)) {
                fileIsFound = true;
                break;
            }
        }
        logger.info("File: " + HexFormat.of().formatHex(fileHash.data()) + " found: " + fileIsFound);
        if (!fileIsFound) {
            files.put(fileHash, parser);
        }
        return parser;
    }
    private @NotNull BitSet checkPieces(@NotNull Parser parser) throws IOException {
        var fileHash = parser.getFileHash();

        File download = FileLoader.getDownloadFile(parser.getName(), standard ? -1 : myServerPort);
        logger.info("File: " + HexFormat.of().formatHex(fileHash) + " exist is " + download.exists());
        int pieceSize = (int)parser.getPieceLength().longValue();
        int countPiece = (int) Math.ceil((double) parser.getLength() / pieceSize);
        BitSet res = new BitSet(countPiece + 1);

        if (!download.exists()) {
            logger.info("Create file " + logger.getName());
            download.createNewFile();
            try (FileOutputStream out = new FileOutputStream(download)) {
                var tmp = new byte[pieceSize];
                tmp[0] = 1;
                for (int i = 0; i < countPiece - 1; ++i) {
                    out.write(tmp);
                }

                if (parser.getPaddingSize() != 0) {
                    out.write(new byte[pieceSize - (int)parser.getPaddingSize().longValue()]);
                } else { out.write(tmp); }
                res.set(0, countPiece, false);

            }
        } else {
            try(FileInputStream in = new FileInputStream(download)) {
                byte[] piece;
                byte[] hash;
                MessageDigest sha1;
                try {
                    sha1 = MessageDigest.getInstance("SHA-1");
                } catch (NoSuchAlgorithmException e) {
                    throw new RuntimeException(e);
                }

                for (int i = 0; i < countPiece; ++i) {
                    piece = in.readNBytes(pieceSize);
                    hash = parser.getPiecesHash().get(i);
                    res.set(i, Arrays.equals(hash, sha1.digest(piece)));

                }
            }
        }
        logger.debug("pieces hash array length: " + res.length());
        return res;
    }
    private @NotNull  ConcurrentLinkedQueue<InetSocketAddress> getPeers(){
        ConcurrentLinkedQueue<InetSocketAddress> peersAddres = new  ConcurrentLinkedQueue<>();
        try (InputStream input = this.getClass().getResourceAsStream("peers.txt")){
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            String peer;
            while ((peer = reader.readLine()) != null) {
                var tmp = peer.split(":");

                if (Objects.equals(tmp[0], "127.0.0.1") && Objects.equals(tmp[1], String.valueOf(myServerPort))) { continue; }
                peersAddres.add(new InetSocketAddress(tmp[0], Integer.parseInt(tmp[1])));
            }
        } catch (IOException ex) {
            logger.error("getPeers: " + ex.getMessage());
            throw new RuntimeException("Peers not found");
        }
        return peersAddres;
    }
}