package game.logic.gameWindow.units;

import game.logic.table.Table;
import game.logic.table.infoEnums.Direction;
import game.logic.table.infoEnums.Type;
import org.jetbrains.annotations.NotNull;

import java.util.Random;

public abstract class UnitLogic {

    static Random rand = new Random();
    boolean rage = false;
    boolean stopped = false;

    UnitModel model;
    Direction curDirection = Direction.TOP;
    Direction nextDirection = Direction.TOP;
    PosUnit curPos = new PosUnit();
    PosUnit spawnPos;
    final int msToUpdateDirection = 500;
    boolean extrawallMove = false;
    public boolean killPacman = false;

    public void setRage(boolean rage) { this.rage = rage; }
    public boolean isRage() { return rage; }

    public UnitModel getModel() { return model; }

    public void setStopped(boolean stopped) { this.stopped = stopped; }

    public boolean isStopped() { return stopped; }

    public PosUnit getCurPos() { return curPos; }
    public void setCurPos(@NotNull PosUnit newPos) {
        curPos.posX = newPos.posX;
        curPos.posY = newPos.posY;
    }

    public PosUnit getSpawnPos() { return spawnPos; }

    public Direction getCurDirection() { return curDirection; }
    public void setNextDirection(Direction nextDirection) { this.nextDirection = nextDirection; }

    public void move(Table table) {
    if (!checkReachability(table, curDirection)) {
        return;
    };

        int moveX = 0;
        int moveY = 0;
        switch (curDirection) {
            case DOWN -> { moveY = 1; }
            case TOP -> { moveY = -1; }
            case RIGHT -> { moveX = 1; }
            case LEFT -> { moveX = -1; }
        }

        curPos.posX = curPos.posX + moveX;
        curPos.posY = curPos.posY + moveY;
    }


    public int getRotate(Table table) {
        if (checkReachability(table, nextDirection)) {
            return changeDirection();
        }
        return 0;
    }

    protected boolean checkReachability(Table table, @NotNull Direction dir) {
        var checkPos = new PosUnit(curPos);

        switch (dir) {
            case TOP -> { checkPos.posY -= 1; }
            case RIGHT -> { checkPos.posX += 1; }
            case DOWN -> { checkPos.posY += 1; }
            case LEFT -> { checkPos.posX -= 1; }
        }
        if (checkPos.posX == Table.getTableWidth()) checkPos.posX = 0;
        if (checkPos.posX == -1) checkPos.posX = Table.getTableWidth() - 1;
        if (checkPos.posY == Table.getTableHeight()) checkPos.posY = 0;
        if (checkPos.posY == -1) checkPos.posY = Table.getTableHeight() - 1;


        var nextBlock =  table.getGameTableInfo()[checkPos.posY][checkPos.posX];
        if (nextBlock.type == Type.LINE) return false;
        if (nextBlock.type == Type.CORN) return false;
        if (nextBlock.type == Type.EXTRAWALL && !extrawallMove) return false;
        return true;


    }

    private int changeDirection() {
        int rot = 0;
        switch (curDirection) {
            case TOP -> {
                if (nextDirection == Direction.RIGHT) { rot = 90; }
                if (nextDirection == Direction.LEFT) { rot = -90; }
                if (nextDirection == Direction.DOWN) { rot = 180; }
            }

            case RIGHT -> {
                if (nextDirection == Direction.DOWN) { rot = 90; }
                if (nextDirection == Direction.TOP) { rot = -90; }
                if (nextDirection == Direction.LEFT) { rot = 180; }
            }
            case DOWN -> {
                if (nextDirection == Direction.LEFT) { rot = 90; }
                if (nextDirection == Direction.RIGHT) { rot = -90; }
                if (nextDirection == Direction.TOP) { rot = 180; }
            }
            case LEFT -> {
                if (nextDirection == Direction.TOP) { rot = 90; }
                if (nextDirection == Direction.DOWN) { rot = -90; }
                if (nextDirection == Direction.RIGHT) { rot = 180; }
            }
        }
        curDirection = nextDirection;
        return rot;
    }


}


