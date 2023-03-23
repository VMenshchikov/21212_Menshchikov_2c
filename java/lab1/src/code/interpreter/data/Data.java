package interpreter.data;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.lang.RuntimeException;
import java.util.Arrays;
import java.util.List;

import my.MyPair;


/**
 * Хранит и обрабатывает код Befunge-93
 */
public class Data{
    private eDirection direction = eDirection.RIGHT;
    private ArrayList<char[]> code = new ArrayList<>();
    private LinkedList<Long> stack = new LinkedList<Long>();
    private MyPair<Integer, Integer> pos = new MyPair<>(-1,0);
    private MyPair<Integer, Integer> sizeCode = new MyPair<>(0,0);
           
    /**
     * Загружает данные из файла 'f' и фиксирует размер кода 'xSize', 'ySize'
     * @param f
     * @param xSize
     * @param ySize
     */
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

    /**
     * @return следующий символ кода в заданном направлении 
     * @see setDirections  
     * */ 
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
                    exit("enum???");   //???????????????????????????????????????????????????????
            }
        return ' '; // иначе ругается
    }
    
    /**
     * устанавливает направление движения для дальнейшего исполнения
     * @see getNextChar
     */
    public void setDirections(eDirection d) {
        direction = d;
    }

    /**
     * Пропускает следующий символ кода
     */
    public void skipCh() {
        getNextChar(); //  не обрабатываем
    }

    /**
     * @return верхний объект стека программы, если стек пустой,
     * то возвращает 0
     */
    public Long popStack() {
        if (stack.size() == 0) {
            return 0l;
        }
        return stack.removeFirst();       
    }

    /**
     * Кладет Long на стек программы 
     * @param i
     */
    public void pushStack(long i) {
        stack.addFirst(i);
    }

    /**
     * Кладет Character на стек программы
     * Преобразует Character в Long 
     * @param c
     */
    public void pushStack(Character c) {
        pushStack((long)Character.getNumericValue(c));
    }

    private void exit(String str) {
        throw new RuntimeException(str);
    }

    /**
     * Меняет код программы. Кладет в ячейку (coord.first, coord.second)
     * символ ch
     * @param coord
     * @param ch
     * @see MyPair
     */
    public void setCode(MyPair<Long, Long> coord, Character ch) {
        code.get(coord.getSecond().intValue())[coord.getFirst().intValue()] = ch;
        return;
    }

    /**
     * @param coord
     * @return Достает из ячейки (cord.first, coord,second)
     *  символ и кладет на стек, ячейка не затирается
     * @see pushStack
     * @see MyPair
     */
    public char getCode(MyPair<Integer, Integer> coord) {
        return code.get(coord.getSecond())[coord.getFirst()];
    }
};
