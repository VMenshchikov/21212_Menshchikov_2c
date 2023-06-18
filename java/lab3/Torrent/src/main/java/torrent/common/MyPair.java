package torrent.common;

public class MyPair<First, Second> {
    private First first = null;
    private Second second = null;
    

    public MyPair(){};
    public MyPair(First f, Second s) {
        first = f;
        second = s;
    }
    
    /**
     * @return First value
     */
    public First getFirst() { return first; }
    /**
     * @return second value
     */
    public Second getSecond() { return second; }

    /**
     * set first value
     * @param t
     */
    public void setFirst(First t) { first = t; }
    /**
     * set second value
     * @param t
     */
    public void setSecond(Second t) { second = t; }
}