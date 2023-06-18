package torrent.client.controller;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import torrent.client.model.Client;
import torrent.client.view.TorrentView;
import torrent.common.ByteArrayWrapper;
import torrent.common.FileLoader;
import torrent.protocol.Parser;
import torrent.server.Server;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.HexFormat;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class TorrentController {
    private final static Logger logger = LogManager.getLogger(TorrentController.class);
    int port;
    boolean standardMode;
    public TorrentController(TorrentView view, int port, boolean stdMode) {
        this.port = port;
        standardMode = stdMode;

        Random random = new Random();
        ByteBuffer tmp = ByteBuffer.wrap(new byte[4]);
        for (int i = 0; i < 4; ++i) {
            tmp.put((byte)(random.nextInt() % 255));
        }

        String id = "NSU_FIT_Lab-" + HexFormat.of().formatHex(tmp.array());
        myID = id.getBytes();
        logger.info("ID torrent: " + Arrays.toString(myID));

        try {
            server = new Server(myID, files, port, standardMode);
        } catch (IOException ex) {
            logger.fatal("Server creating error. " + ex.getMessage());
            throw new RuntimeException(ex.getMessage());
        }
        serverThread = new Thread(() -> server.start(), "Server");
        serverThread.start();
        this.view = view;

    }
    Map<ByteArrayWrapper, Parser> files = FileLoader.getTorrentFiles();
    TorrentView view;
    Server server;
    Thread serverThread;
    Thread loadThread = null;
    Client client = null;
    Parser currentTorrent = null;
    byte[] myID;

    AtomicInteger downloadedPiece = new AtomicInteger(0);

    public AtomicInteger getDownloadedPiece() { return downloadedPiece; }

    public void createClient() {
        client = new Client(myID, files, this, port, standardMode);
    }

    public boolean setFile(File file) {
        downloadedPiece.set(0);
        try { currentTorrent = new Parser(file); }
            catch (IOException ex) { return false; }

        var downloadFile = FileLoader.getDownloadFile(currentTorrent.getName(), port);
        try (FileInputStream in = new FileInputStream(downloadFile)) {
            for (int i = 0; i < currentTorrent.getPiecesHash().size(); ++i) {
                var tmpPiece = in.readNBytes((int) currentTorrent.getPieceLength().longValue());

                MessageDigest sha1;
                try {
                    sha1 = MessageDigest.getInstance("SHA-1");
                } catch (NoSuchAlgorithmException e) {
                    throw new RuntimeException(e);
                }
                var pieceHash = sha1.digest(tmpPiece);


                if (Arrays.equals(pieceHash, currentTorrent.getPiecesHash().get(i))) {
                    downloadedPiece.incrementAndGet();
                }
            }
        } catch (IOException ex) {
            logger.fatal("Exception on set first progress: " + ex.getMessage());
            return false;
        }

        return true;
    }

    public Parser getParser() {
        return currentTorrent;
    }

    public void load() {
        Runnable task = () -> client.start(currentTorrent);
        loadThread = new Thread(task, "LoadFile");
        loadThread.start();
    }

    public double getProgress() {
        return (double)downloadedPiece.get()/currentTorrent.getPiecesHash().size();
    }

    public int getPort() { return port; }
    public boolean isDownloading() {
        if (loadThread == null) return false;
        return loadThread.isAlive();
    }

    public void endProgram() {
        server.closeAll();
        if (loadThread != null) { loadThread.interrupt(); }
    }
}
