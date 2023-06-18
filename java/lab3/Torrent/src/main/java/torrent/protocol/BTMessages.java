package torrent.protocol;



import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public class BTMessages {


    public static byte @NotNull [] genHandShake(byte @NotNull [] hash, byte @NotNull [] id) {

        if (hash.length != 20) throw new IllegalArgumentException("hash.length != 20);");
        if (id.length != 20) throw new IllegalArgumentException("id.length != 20. Current length is " + id.length);


        byte[] handShake = new byte[68];

        System.arraycopy(new byte[]{19}, 0, handShake, 0, 1);
        System.arraycopy("BitTorrent protocol".getBytes(), 0, handShake, 1, 19);
        System.arraycopy(new byte[]{0, 0, 0, 0, 0, 0, 0, 0}, 0, handShake, 20, 8);
        System.arraycopy(hash, 0, handShake, 28, 20);
        System.arraycopy(id, 0, handShake, 48, 20);



        return handShake;
    }
    private static boolean isHandShake(@NotNull byte @NotNull [] message) {
        if (message.length != 68) return false;
        var sub = Arrays.copyOfRange(message, 0, 20);
                //message.substring(0, 28).getBytes();
        byte[] reference = new byte[20];
        System.arraycopy(new byte[]{19}, 0, reference, 0, 1);
        System.arraycopy("BitTorrent protocol".getBytes(), 0, reference, 1, 19);
        //System.arraycopy(new byte[]{0, 0, 0, 0, 0, 0, 0, 0}, 0, reference, 20, 8);
        return Arrays.equals(reference, sub);
    }

    @Contract(value = " -> new", pure = true)
    public static byte @NotNull [] genKeepAlive() {
        return new byte[]{0, 0, 0, 0};
    }

    @Contract(value = " -> new", pure = true)
    public static byte @NotNull [] genChoke() {
        return new byte[]{0, 0, 0, 1, 0};
    }

    @Contract(value = " -> new", pure = true)
    public static byte @NotNull [] genUnChoke() {
        return new byte[]{0, 0, 0, 1, 1};
    }

    @Contract(value = " -> new", pure = true)
    public static byte @NotNull [] genInterested() {
        return new byte[]{0, 0, 0, 1, 2};
    }

    @Contract(value = " -> new", pure = true)
    public static byte @NotNull [] genNotInterested() {
        return new byte[]{0, 0, 0, 1, 3};
    }

    @Contract(pure = true)
    public static byte @NotNull [] genRequest(int piece, int begin, int len) {
        byte[] always = new byte[]{0, 0, 0, 13, 6};

        ByteBuffer request = ByteBuffer.wrap(new byte[17]);
        request.put(always); //<len><id>
        request.putInt(piece); //<index>
        request.putInt(begin); //<begin>
        request.putInt(len); //<length>
        request.order(ByteOrder.BIG_ENDIAN);
        return request.array();
    }

    @Contract(pure = true)
    public static byte @NotNull [] genPiece(int piece, int begin, byte @NotNull [] block) {
        ByteBuffer request = ByteBuffer.wrap(new byte[13 + block.length]);
        request.putInt(9 + block.length);
        request.put((byte)7);
        request.putInt(piece);
        request.putInt(begin);
        request.put(block);
        request.order(ByteOrder.BIG_ENDIAN);
        return request.array();
    }

    @Contract(pure = true)
    public static byte @NotNull [] genCansel(int piece, int begin, int len) {
        byte[] always = new byte[]{0, 0, 0, 13, 8};

        ByteBuffer request = ByteBuffer.wrap(new byte[13]);
        request.put(always); //<len><id>
        request.putInt(piece); //<index>
        request.putInt(begin); //<begin>
        request.putInt(len); //<length>
        request.order(ByteOrder.BIG_ENDIAN);
        return request.array();
    }

    @Contract(pure = true)
    public static byte @NotNull [] genBitfield(byte @NotNull [] bitfield) {
        ByteBuffer request = ByteBuffer.wrap(new byte[13 + bitfield.length]);
        request.putInt(1 + bitfield.length);
        request.put((byte)5);
        request.put(bitfield);
        request.order(ByteOrder.BIG_ENDIAN);
        return request.array();
    }

    public static byte @NotNull [] genHave(int piece) {
        byte[] always = new byte[]{0, 0, 0, 9, 4};

        ByteBuffer request = ByteBuffer.wrap(new byte[9]);
        request.put(always); //<len><id>
        request.putInt(piece); //<index>
        request.order(ByteOrder.BIG_ENDIAN);
        return request.array();
    }

    public static MessageID getType(@NotNull ByteBuffer message) {
        if (isHandShake(message.array())) return MessageID.HANDSHAKE;
        var tmp = switch (message.get()) {
            case 0 -> MessageID.CHOKE;
            case 1 -> MessageID.UN_CHOKE;
            case 2 -> MessageID.INTERESTED;
            case 3 -> MessageID.NOT_INTERESTED;
            case 4 -> MessageID.HAVE;
            case 5 -> MessageID.BITMAP;
            case 6 -> MessageID.REQUEST;
            case 7 -> MessageID.PIECE;
            case 8 -> MessageID.CANCEL;
            default -> MessageID.UNDEFINED;
        };
        message.compact();
        return tmp;
    }


}
