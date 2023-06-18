package game.logic.table;

import javafx.scene.paint.Color;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Scanner;

import game.logic.table.infoEnums.*;

public class Table {
    private static final int tableWidth = 48; //36-canon
    private static final int tableHeight = 28;
    private CellInfo[][] gameTableInfo;
    public static int getTableWidth() {return tableWidth;}
    public static int getTableHeight() {
        return tableHeight;
    }
    public CellInfo[][] getGameTableInfo() { return gameTableInfo; }
    private char[][] lvlTable;

    private int startEatCount = 0;

    public int getStartEatCount() { return startEatCount; }

    public void loadLvl(@NotNull String lvl) {
        lvlTable = new char[tableHeight][tableWidth];
        try (Scanner sc = new Scanner(Table.class.getResourceAsStream(lvl))) {
            for (int y = 0; y < tableHeight; ++y) {
                if (!sc.hasNextLine()) {
                    String err = "Height lvl < tableHeight. " + lvl;
                    System.err.println(err);
                    throw new RuntimeException(err);
                }
                char[] tmp = sc.nextLine().toCharArray();
                if (tmp.length > tableWidth) {
                    String err = "Width lvl in line " + Integer.toString(y)
                            + "!= table Width\n" + lvl;
                    System.err.println(err);
                    throw new RuntimeException(err);
                }
                System.arraycopy(tmp, 0, lvlTable[y], 0, tmp.length);
                for (int i = 0; i < tableWidth; i++) {
                    if (lvlTable[y][i] == '\u0000') {
                        lvlTable[y][i] = ' ';
                    }
                }
            }
        }
        fillTableInfo();
    }
    private void fillTableInfo() {
        startEatCount = 0;
        gameTableInfo = new CellInfo[tableHeight][tableWidth];
        for (int y = 0; y < tableHeight; ++y) {
            for (int x = 0; x < tableWidth; ++x) {
                gameTableInfo[y][x] = new CellInfo();
            }
        }


        for (int y = 0; y < tableHeight; ++y) {
            for (int x = 0; x < tableWidth; ++x) {
                switch (lvlTable[y][x]) {
                    case '#':
                    case '&':
                        addWallsInfo(x,y);
                        break;
                    case '*':
                        gameTableInfo[y][x].type = Type.EAT;
                        gameTableInfo[y][x].color = Color.GREY;
                        startEatCount++;
                        break;
                    case 'O':
                        gameTableInfo[y][x].type = Type.BIGEAT;
                        gameTableInfo[y][x].color = Color.RED;
                        break;
                    case ' ':
                        gameTableInfo[y][x].type = Type.EMPTY;
                        break;
                    case 'B':
                        gameTableInfo[y][x].type = Type.BERRY;
                        gameTableInfo[y][x].color = Color.GREY;
                    case '$':
                    case '?':
                        break;
                    default:
                        System.out.println("unexpected cell");
                }
            }
        }

    }
    private void addWallsInfo(int x, int y) {
        Direction prevDirection = Direction.RIGHT;
        gameTableInfo[y][x].type = Type.CORN;
        gameTableInfo[y][x].corn = Corner.LTOP;
        x++;
        
        while (lvlTable[y][x] != '$' && lvlTable[y][x] != '?') {
            if (lvlTable[y][x] == '#') lvlTable[y][x] = '$';
            if (lvlTable[y][x] == '&') lvlTable[y][x] = '?';

            boolean extrawall = false;
            if (lvlTable[y][x] == '?') {
                //gameTableInfo[y][x].type = Type.EXTRAWALL;
                extrawall = true;
                gameTableInfo[y][x].color = Color.web("0xA7FF52");
            }
            else {
                extrawall = false;
            }

            switch (prevDirection) {
                case RIGHT -> {
                    if (checkReachability(x,y, Direction.TOP)){
                        gameTableInfo[y][x].type = Type.CORN;
                        gameTableInfo[y][x].corn = Corner.RDOWN;
                        y--;
                        prevDirection = Direction.TOP;
                    } else
                        if (checkReachability(x, y, Direction.RIGHT)) {
                            gameTableInfo[y][x].type = extrawall ? Type.EXTRAWALL : Type.LINE;
                            gameTableInfo[y][x].pos = Position.HORIZONTAL;
                            x++;
                            prevDirection = Direction.RIGHT;
                        } else
                            if (checkReachability(x, y, Direction.DOWN)) {
                                gameTableInfo[y][x].type = Type.CORN;
                                gameTableInfo[y][x].corn = Corner.RTOP;
                                y++;
                                prevDirection = Direction.DOWN;
                            }
                }
                case DOWN -> {
                    if (checkReachability(x, y, Direction.RIGHT)) {
                        gameTableInfo[y][x].type = Type.CORN;
                        gameTableInfo[y][x].corn = Corner.LDOWN;
                        x++;
                        prevDirection = Direction.RIGHT;

                    } else
                        if (checkReachability(x, y, Direction.DOWN)) {
                            gameTableInfo[y][x].type = extrawall ? Type.EXTRAWALL : Type.LINE;
                            gameTableInfo[y][x].pos = Position.VERTICAL;
                            y++;
                            prevDirection = Direction.DOWN;
                        } else
                            if (checkReachability(x, y, Direction.LEFT)) {
                                gameTableInfo[y][x].type = Type.CORN;
                                gameTableInfo[y][x].corn = Corner.RDOWN;
                                x--;
                                prevDirection = Direction.LEFT;
                            }
                }
                case LEFT -> {
                    if (checkReachability(x, y, Direction.DOWN)) {
                        gameTableInfo[y][x].type = Type.CORN;
                        gameTableInfo[y][x].corn = Corner.LTOP;
                        y++;
                        prevDirection = Direction.DOWN;
                    } else
                        if (checkReachability(x, y, Direction.LEFT)) {
                            gameTableInfo[y][x].type = extrawall ? Type.EXTRAWALL : Type.LINE;
                            gameTableInfo[y][x].pos = Position.HORIZONTAL;
                            x--;
                            prevDirection = Direction.LEFT;
                        } else
                            if (checkReachability(x, y, Direction.TOP)) {
                                gameTableInfo[y][x].type = Type.CORN;
                                gameTableInfo[y][x].corn = Corner.LDOWN;
                                y--;
                                prevDirection = Direction.TOP;
                            }
                }
                case TOP -> {
                    if (checkReachability(x, y, Direction.LEFT)) {
                        gameTableInfo[y][x].type = Type.CORN;
                        gameTableInfo[y][x].corn = Corner.RTOP;
                        x--;
                        prevDirection = Direction.LEFT;
                    } else
                        if (checkReachability(x, y, Direction.TOP)) {
                            gameTableInfo[y][x].type = extrawall ? Type.EXTRAWALL : Type.LINE;
                            gameTableInfo[y][x].pos = Position.VERTICAL;
                            y--;
                            prevDirection = Direction.TOP;
                        } else if(checkReachability(x,y, Direction.RIGHT)) {
                            gameTableInfo[y][x].type = Type.CORN;
                            gameTableInfo[y][x].corn = Corner.LTOP;
                            x++;
                            prevDirection = Direction.RIGHT;
                        }
                }
            }
        }
    }
    @Contract(pure = true)
    private boolean checkReachability(int x, int y, @NotNull Direction direction) {
        switch (direction) {
            case RIGHT -> {
                if (x+1 == tableWidth) return false;
                if (lvlTable[y][x + 1] == '#') return true;
                if (lvlTable[y][x + 1] == '&') return true;
                return false;
            }
            case DOWN -> {
                if (y+1 == tableHeight) return false;
                if (lvlTable[y + 1][x] == '#') return true;
                if (lvlTable[y + 1][x] == '&') return true;
                return false;
            }
            case LEFT -> {
                if (x-1 == -1) return false;
                if (lvlTable[y][x - 1] == '#') return true;
                if (lvlTable[y][x - 1] == '&') return true;
                return false;
            }
            case TOP -> {
                if (y - 1 == -1 ) return false;
                if (lvlTable[y - 1][x] == '#') return true;
                if (lvlTable[y - 1][x] == '&') return true;
                return false;
            }
            default -> throw new RuntimeException("Undeclared direction");
        }
    }


}
