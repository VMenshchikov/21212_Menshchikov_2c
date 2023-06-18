package torrent.protocol;

public enum MessageID {
    HANDSHAKE,
    KEEP_ALIVE,
    BITMAP,
    CHOKE,
    UN_CHOKE,
    INTERESTED,
    NOT_INTERESTED,
    HAVE,
    REQUEST,
    PIECE,
    CANCEL,
    UNDEFINED
}
