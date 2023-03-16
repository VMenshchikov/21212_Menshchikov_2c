package interpreter.data;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.lang.RuntimeException;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

import my.MyPair;

public class Data{
    private eDirection direction = eDirection.RIGHT;
    private ArrayList<char[]> code = new ArrayList<>();
    private LinkedList<Long> stack;
    private MyPair<Integer, Integer> pos = new MyPair<>(-1,0);
    private MyPair<Integer, Integer> sizeCode = new MyPair<>(0,0);

    public void loadData(File f, Integer xSize, Integer ySize) {
        try (Scanner sc = new Scanner(f);) {
            sizeCode.setFirst(xSize);
            sizeCode.setSecond(ySize);
            for (int i = 0; i < sizeCode.getSecond(); ++i) {
                if (sc.hasNextLine()) {
                    char[] tmp = sc.nextLine().toCharArray();
                    char[] res = new char[sizeCode.getFirst()];
                    Arrays.fill(res, ' ');
                    System.arraycopy(tmp, 0, res, 0, tmp.length);
                    code.add(res);
                } else {
                   char[] a = new char[sizeCode.getFirst()];
                   Arrays.fill(a, ' ');
                   code.add(a);
                }
            }
        } catch (FileNotFoundException e) {
            exit(e.getMessage());            
        }
    }

    public char getNextChar() {
            switch (direction) {
                case  LEFT:
                    pos.setFirst(pos.getFirst() - 1); // x--
                    if (pos.getFirst().intValue() == -1) pos.setFirst(sizeCode.getFirst() - 1); // if x == -1..
                    return code.get(pos.getSecond())[pos.getFirst()]; // return y String x symbol
                case RIGHT:
                    pos.setFirst((pos.getFirst() + 1) % sizeCode.getFirst()); // ++x % maxX
                    return code.get(pos.getSecond())[pos.getFirst()]; // return -//-
                case TOP: 
                    pos.setSecond(pos.getSecond() - 1); // y--
                    if (pos.getSecond().intValue() == -1)  pos.setSecond(sizeCode.getSecond() - 1);  //if y == -1..                
                    return code.get(pos.getSecond())[pos.getFirst()]; //return -//-
                
                case DOWN: 
                    pos.setSecond((pos.getSecond() + 1) % sizeCode.getSecond()); // ++y % maxY
                    return code.get(pos.getSecond())[pos.getFirst()]; //return -//-                
                default:
                    exit("enum???");
            }
        return ' '; // иначе ругается
    }
    
    public void setDirections(eDirection d) {
        direction = d;
    }

    public void skipCh() {
        getNextChar(); //  не обрабатываем
    }

    public Long popStack() {
        if (stack.size() == 0) {
            return 0l;
        }
        return stack.removeFirst();       
    }

    public void pushStack(long i) {
        if (stack == null) {
            stack = new LinkedList<Long>();
        }
        stack.addFirst(i);
    }

    public void pushStack(Character c) {
        pushStack((long)Character.getNumericValue(c));
    }

    private void exit(String str) {
        throw new RuntimeException(str);
    }

    public void setCode(MyPair<Long, Long> coord, Character ch) {
        code.get(pos.getSecond())[pos.getFirst()] = ch;
    }

    public char getCode(MyPair<Integer, Integer> coord) {
        return code.get(coord.getSecond())[coord.getFirst()];
    }
};
