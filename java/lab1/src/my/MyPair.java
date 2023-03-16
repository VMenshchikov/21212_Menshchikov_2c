package my;

public class MyPair<First, Second> {
    private First first = null;
    private Second second = null;

    public MyPair(){};
    public MyPair(First f, Second s) {
        first = f;
        second = s;
        }
    
    public First getFirst() { return first; }
    public Second getSecond() { return second; }

    public void setFirst(First t) { first = t; }
    public void setSecond(Second t) { second = t; }
}