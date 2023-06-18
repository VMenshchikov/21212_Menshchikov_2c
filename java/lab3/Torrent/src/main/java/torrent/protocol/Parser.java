package torrent.protocol;


import java.io.*;
import java.nio.charset.StandardCharsets;
import java.security.NoSuchAlgorithmException;
import java.util.*;

import com.dampcake.bencode.Bencode;
import com.dampcake.bencode.Type;
import org.jetbrains.annotations.NotNull;

import java.security.MessageDigest;

public class Parser {
    private byte[] fileHash;
    private ArrayList<byte[]> piecesHash = new ArrayList<>();
    private String name;
    private Long length;
    private Long pieceLength;
    private Long paddingSize;

    public ArrayList<byte[]> getPiecesHash() { return piecesHash; }
    public byte[] getFileHash() { return fileHash; }
    public Long getLength() { return length; }
    public Long getPieceLength() { return pieceLength; }
    public String getName() { return name; }
    public Long getPaddingSize() { return paddingSize; }

    public Parser (File torrent) throws IOException {
        Bencode bc = new Bencode(StandardCharsets.ISO_8859_1);
        Map pars;

        try (FileInputStream stream = new FileInputStream(torrent)) {
            pars = bc.decode(stream.readAllBytes(), Type.DICTIONARY);
        }
        Map info = (Map)pars.get("info");

        MessageDigest sha1;
        try {
             sha1 = MessageDigest.getInstance("SHA-1");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
        sha1.update(bc.encode(info));

        fileHash = sha1.digest();
        name = info.get("name").toString();
        length = (Long)info.get("length");
        pieceLength = (Long)info.get("piece length");
        paddingSize = pieceLength - length % pieceLength;


        String tmpPieces = (String)info.get("pieces");
        InputStream is = new ByteArrayInputStream(tmpPieces.getBytes(StandardCharsets.ISO_8859_1));
        for (int i = 0; i < tmpPieces.length(); i+=20) {
            piecesHash.add(is.readNBytes(20));
        }
    }
}
