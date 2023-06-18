package torrent.common;

import org.jetbrains.annotations.Nullable;
import torrent.protocol.BTMessages;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.ClosedChannelException;
import java.nio.channels.SocketChannel;
import java.util.BitSet;
import java.util.concurrent.atomic.AtomicInteger;

public class Peer implements Comparable<Peer>{
    @Override
    public int compareTo(Peer other) {
        return Integer.compare(tasksCount.get(), other.getTasksCount().get());
    }

    private AtomicInteger tasksCount = new AtomicInteger(0);
    public AtomicInteger getTasksCount() { return tasksCount; }
    private SocketChannel socketChannel;

    public SocketChannel getSocketChannel() { return socketChannel; }

    private BitSet bitField = null;

    public BitSet getBitField() { return bitField; }

    public void setBitField(BitSet bitField) { this.bitField = bitField; }

    public Peer(SocketChannel socket) {
        this.socketChannel = socket;
    }

    public static @Nullable ByteBuffer getMessage(SocketChannel socketChannel) throws IOException{
        ByteBuffer len = ByteBuffer.allocate(4);
        len.order(ByteOrder.BIG_ENDIAN);
        ByteBuffer message = null;
        boolean flagKAM = true;
        while (flagKAM) {
            while (len.position() != len.limit()) {
                var readied =  socketChannel.read(len);
                if (readied == 0 ) { // сообщение не было отправлено (read вернул 0)
                    return null;
                }
                if (readied == -1) {
                    throw new ClosedChannelException();
                }
            }
            len.flip();
            int sizeMessage = len.getInt();
            if (sizeMessage == 0) {
                len.position(0);
                continue;
            }
            if (sizeMessage < 0) {
                return null;
            }
            flagKAM = false;
            message = ByteBuffer.allocate(sizeMessage);
            message.order(ByteOrder.BIG_ENDIAN);
            while (message.position() != message.limit()) {
                var readied =  socketChannel.read(message);
                //if (readied == 0 ) { // сообщение не было отправлено (read вернул 0)
                //    return null;
                //}
                //if (readied == -1) {
                //    throw new ClosedChannelException();
                //}
            }
            message.position(0);
        }
        return message;
    }


    public boolean sendRequest(int pieceNum, long pieceLen) {
        try {
            var message = ByteBuffer.wrap(BTMessages.genRequest(pieceNum, 0, (int)pieceLen));
            while (message.position() != message.limit()) {
                socketChannel.write(message);
            }
        } catch (IOException e) { return false; }
        return true;
    }

}
