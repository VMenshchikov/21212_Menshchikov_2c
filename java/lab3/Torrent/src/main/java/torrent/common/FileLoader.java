package torrent.common;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jetbrains.annotations.NotNull;
import torrent.protocol.Parser;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.HexFormat;
import java.util.Objects;

public class FileLoader {
    private final static String torrentPath = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/torrent";
    private final static String downloadPath = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/download";
    private final static String serverPath = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/server";

    //for test in local loop
    private final static String downloadPath1 = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/download_1701";
    private final static String downloadPath2 = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/download_1702";
    private final static String downloadPath3 = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/download_1703";
    private final static String serverPath1 = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/server_1701";
    private final static String serverPath2 = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/server_1702";
    private final static String serverPath3 = "/home/dogshawa/Рабочий стол/oop/21212_Menshchikov/java/lab3/files/server_1703";


    private final static Logger logger = LogManager.getLogger(FileLoader.class);

    public static @NotNull HashMap<ByteArrayWrapper, Parser> getTorrentFiles() {
        logger.debug("Start load files .torrent");
        HashMap<ByteArrayWrapper, Parser> files = new HashMap<>();
        File dirTorrent = new File(torrentPath);
        logger.info("Files directory: " + dirTorrent.getPath());
        for (var file : Objects.requireNonNull(dirTorrent.listFiles())) {
            Parser tmp;
            try {
                tmp = new Parser(file);
                logger.info("Create Parser for file " + file.getName() + ". Hash: " + HexFormat.of().formatHex(tmp.getFileHash()));
            } catch (IOException ex) {
                logger.fatal("IOExeption: " + ex.getMessage());
                throw new RuntimeException(ex.getMessage());
            }
            files.put(new ByteArrayWrapper(tmp.getFileHash()), tmp);
        }
        logger.debug("End load files");

        return files;
    }

    public static @NotNull File getDownloadFile(String name, int num) {
        if (num == -1) {
            return new File(downloadPath + "/" + name);
        }

        switch (num) {
            case 1701 -> {
                return new File(downloadPath1 + "/" + name);
            }
            case 1702 -> {
                return new File(downloadPath2 + "/" + name);
            }
            case 1703 -> {
                return new File(downloadPath3 + "/" + name);
            }
            default -> {
                return new File(downloadPath + "/" + name);
            }
        }
    }

    public static @NotNull File getServerFile(String name, int num) {
        if (num == -1) {
            return new File(serverPath + "/" + name);
        }

        switch (num) {
            case 1701 -> {
                return new File(serverPath1 + "/" + name);
            }
            case 1702 -> {
                return new File(serverPath2 + "/" + name);
            }
            case 1703 -> {
                return new File(serverPath3 + "/" + name);
            }
            default -> {
                return new File(serverPath + "/" + name);
            }
        }    }
}



