package torrent.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import org.jetbrains.annotations.NotNull;

import torrent.Torrent;
import torrent.common.ByteArrayWrapper;
import torrent.common.FileLoader;
import torrent.common.MyPair;
import torrent.common.Peer;
import torrent.protocol.BTMessages;
import torrent.protocol.MessageID;
import torrent.protocol.Parser;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.concurrent.*;

public class Server {
    private final static Logger logger = LogManager.getLogger(Server.class);
    ThreadPoolExecutor threadPool = null;
    private final byte[] myID;
    Map<ByteArrayWrapper, Parser> files;
    ServerSocketChannel listener;
    boolean standardMode;
    int myPort;
    public Server(byte[] ID, Map<ByteArrayWrapper, Parser> torrents, int port, boolean stdMode) throws IOException {
        standardMode = stdMode;
        myID = ID;
        files = torrents;
        myPort = port;
        try {
            listener = ServerSocketChannel.open();
            listener.bind(new InetSocketAddress(port));
        } catch (IOException ex) {
            logger.fatal("Exception in create ServerSocket: " + ex.getMessage());
            throw ex;
        }
        logger.info("Server created. Port: " + port);
    }

    Selector selector = Selector.open();
    Thread acceptThread = null;
    Thread selectorThread = null;
    ConcurrentHashMap<SocketAddress, MyPair<Parser, RandomAccessFile>> mapPeers = new ConcurrentHashMap<SocketAddress, MyPair<Parser,RandomAccessFile>>();

    private void acceptThreadCreate() {
        Runnable acceptTask = () -> {
            SocketAddress remoteAddress;
            while (!Thread.currentThread().isInterrupted()) {
                SocketChannel client = null;
                RandomAccessFile file = null;
                try {
                    client = listener.accept();
                    remoteAddress = client.getRemoteAddress();
                } catch (IOException ex) {
                    logger.fatal("Client cant created. " + ex.getMessage() + ". " + ex.getClass().getName());
                    if (ex instanceof ClosedByInterruptException){
                        if (threadPool != null) { threadPool.shutdownNow(); }
                        break;
                    }
                    continue;
                }

                try {
                    ByteBuffer message = ByteBuffer.allocate(68);
                    while (message.position() != message.limit()) {
                        client.read(message);
                    }
                    message.flip();

                    if (BTMessages.getType(message) != MessageID.HANDSHAKE) {
                        logger.error("Client: " + remoteAddress + " responded with not a handshake.");
                        client.close();
                        continue;
                    }
                    logger.info("Client: " + remoteAddress + " responded with a handshake.");
                    message.position(28);
                    message.limit(68);

                    byte[] fileHash = new byte[20];
                    byte[] clientID = new byte[20];
                    message.get(fileHash);
                    message.get(clientID);

                    if (Arrays.equals(clientID, myID)) {
                        logger.fatal("ClientID and myID is equals. Close connection.");
                        client.close();
                        continue;
                    }

                    Parser torrent = null;
                    BitSet bitField = null;
                    try {
                        torrent = foundFile(fileHash);
                        file = new RandomAccessFile(FileLoader.getServerFile(torrent.getName(), standardMode ? -1 : myPort), "r");

                        bitField = getBitFieldPieces(torrent);
                    } catch (IOException ex) {
                        if (torrent == null) { //foundFile exception
                            logger.fatal("Torrent file " + HexFormat.of().formatHex(fileHash) + " not found.");
                        }
                        if (ex instanceof FileNotFoundException) { // getBitField exceptions
                            logger.fatal("File " + torrent.getName() + " not exist.");
                        } else {
                            logger.fatal("File " + torrent.getName() + " ." + ex.getMessage());
                        }
                        try {
                            byte[] tmp = new byte[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                            client.write(ByteBuffer.wrap(BTMessages.genHandShake(tmp, myID)));
                        } catch (IOException e) {
                            logger.fatal("Can not send message. " + e.getMessage());
                            client.close();
                            continue;
                        }
                        client.close();
                        continue;
                    }

                    try {
                        logger.info("Client: " + client.getRemoteAddress() + ". Send HS and BitMap.");
                        var tmp = ByteBuffer.wrap(BTMessages.genHandShake(torrent.getFileHash(), myID));
                        tmp.flip();
                        tmp.limit(68);
                        client.write(tmp);

                        tmp = ByteBuffer.wrap(BTMessages.genBitfield(bitField.toByteArray()));
                        tmp.flip();
                        tmp.limit(bitField.toByteArray().length + 5);
                        client.write(tmp);

                        client.write(ByteBuffer.wrap(BTMessages.genUnChoke()));
                    } catch (IOException ex) {
                        logger.fatal("Can not send message. " + ex.getMessage());
                        client.close();
                        continue;
                    }
                    mapPeers.put(remoteAddress, new MyPair<>(torrent, file));
                    client.configureBlocking(false);
                    client.register(selector, SelectionKey.OP_READ);
                    selector.wakeup();

                } catch (IOException ex) {
                    logger.fatal("Client: " + remoteAddress + ". Cant open IStream. " + ex.getMessage());
                }
            }
        };
        acceptThread = new Thread(acceptTask, "AcceptThread");
        acceptThread.start();
    }

    private void selectorTreadCreate() {
        Runnable selectorTask = () -> {
            try {
                while (!Thread.currentThread().isInterrupted()) {
                    if (selector.keys().size() == 0) {
                        continue;
                    }
                    try {
                        selector.select();
                    } catch (ClosedSelectorException ex) {
                        continue;
                    }
                    for (var key : selector.selectedKeys()) {
                        try {
                            SocketChannel channel = (SocketChannel) key.channel();
                            var address = channel.getRemoteAddress();
                            ByteBuffer message;
                            try {
                                message = Peer.getMessage(channel);
                            } catch (IOException ex) {
                                mapPeers.remove(address);
                                key.cancel();
                                channel.close();
                                if (selector.keys().size() == 0) {
                                }
                                continue;
                            }
                            if (message == null) {
                                continue;
                            }
                            var pair = mapPeers.get(address);
                            RandomAccessFile file = pair.getSecond();
                            Parser torrent = pair.getFirst();
                            switch (BTMessages.getType(message)) {
                                case UNDEFINED -> logger.error("Client: " + address + " send UNDEFINED message. Continue with UB");
                                case INTERESTED -> logger.info("Client: " + address + " send INTERESTED. Continue with UB");
                                case REQUEST -> {
                                    message.flip();
                                    int piece = message.getInt(),
                                            begin = message.getInt(),
                                            len = message.getInt();
                                    logger.info("Client: " + address + " send REQUEST. Pieces: " + piece);

                                    byte[] block = new byte[len];
                                    file.seek(piece * torrent.getPieceLength() + begin);
                                    int readInt = file.read(block);
                                    if (readInt != len) {
                                        Arrays.fill(block, readInt, block.length, (byte) 0);
                                    }
                                    var response = ByteBuffer.wrap(BTMessages.genPiece(piece, begin, block));
                                    try {
                                        while (response.position() != response.limit()) {
                                            var a = channel.write(response);
                                        }
                                    } catch (IOException ex) {
                                        mapPeers.remove(address);
                                        key.cancel();
                                        channel.close();
                                        continue;
                                    }
                                    logger.debug("Send piece num " + piece);
                                }
                                default -> logger.info("Client: " + address + " send message(default branch).");
                            }
                        } catch (IOException ex) {
                            logger.error("SelectorThread exception: " + ex.getMessage());
                            ex.printStackTrace();
                        }
                    }
                }
            } catch (IOException ex) {
                logger.fatal("Exception on selectorThread: "+ ex.getMessage());
            }
        };
        selectorThread = new Thread(selectorTask, "SelectorThread");
        selectorThread.start();
    }
    public void start() {
        acceptThreadCreate();
        selectorTreadCreate();
    }
    private Parser foundFile(byte @NotNull [] torrent) throws FileNotFoundException {
        var tmp = new ByteArrayWrapper(torrent);
        if (!files.containsKey(tmp)) { throw new FileNotFoundException("Torrent file not found."); }
        return files.get(tmp);
    }
    private @NotNull BitSet getBitFieldPieces(@NotNull Parser torrent) throws IOException {
        File file = FileLoader.getServerFile(torrent.getName(), standardMode ? -1 : myPort);
        if (!file.exists()) { throw new FileNotFoundException("File " + torrent.getName() + "not found."); }
        var fileHashes = torrent.getPiecesHash();
        BitSet ret = new BitSet(fileHashes.size());

        MessageDigest sha1;
        try {
            sha1 = MessageDigest.getInstance("SHA-1");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        try (FileInputStream in = new FileInputStream(file)) {

            for (int i = 0; i < fileHashes.size(); ++i) {
                var tmp =  sha1.digest(in.readNBytes((int)torrent.getPieceLength().longValue()));
                ret.set(i, Arrays.equals(tmp, fileHashes.get(i)));
            }
        }
        return ret;
    }

    public void closeAll() {

        selector.keys().forEach((key) -> {
            try {
                key.channel().close();
                key.cancel();
            } catch (IOException ex) {
                logger.fatal("Exception on close key/channel: " + ex.getMessage());
            }

        });
        for (var el: mapPeers.values()) {
            try {
                el.getSecond().close();
            } catch (IOException ex) {
                logger.fatal("Exception on close file: " + ex.getMessage());
            }
        }
        acceptThread.interrupt();
        selectorThread.interrupt();
        selector.wakeup();
    }
}
