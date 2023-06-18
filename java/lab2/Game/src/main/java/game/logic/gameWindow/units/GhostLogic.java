package game.logic.gameWindow.units;

import game.logic.gameWindow.units.brains.Brain;
import game.logic.table.Table;
import game.logic.table.infoEnums.Direction;
import game.view.gameWindow.UnitController;
import javafx.animation.Timeline;

import java.util.Random;


public class GhostLogic extends UnitLogic {
    Brain brain;
    Timeline brainLoop;

    public Timeline getBrainLoop() { return brainLoop; }

    public void setBrainLoop(Timeline brainLoop) { this.brainLoop = brainLoop; }

    Random rand = new Random(System.currentTimeMillis());


    public GhostLogic(int startX, int startY, Brain brain, String color) {
        model = UnitController.createModel();
        UnitController.setFirstGhost(model, color);
        UnitController.setSecondGhost(model);
        curPos.posX = startX;
        curPos.posY = startY;
        spawnPos = new PosUnit(curPos);
        extrawallMove = true;
        killPacman = true;
        this.brain = brain;
    }

    public void chooseNextDirection(PosUnit pacmanPos, Direction pacmanDir, Table table) {
        nextDirection = brain.chooseDirection(curPos, pacmanPos, pacmanDir);

        if (!rage && ((curDirection == Direction.DOWN && nextDirection == Direction.TOP) ||
                      (curDirection == Direction.TOP && nextDirection == Direction.DOWN) ||
                      (curDirection == Direction.LEFT && nextDirection == Direction.RIGHT) ||
                      (curDirection == Direction.RIGHT && nextDirection == Direction.LEFT))) {
            nextDirection = curDirection;
        }
        if (rage) {
            switch (nextDirection) {
                case RIGHT -> nextDirection = Direction.LEFT;
                case LEFT -> nextDirection = Direction.RIGHT;
                case TOP -> nextDirection = Direction.DOWN;
                case DOWN -> nextDirection = Direction.TOP;
            }
        }
        if (!checkReachability(table, curDirection) && !checkReachability(table, nextDirection)) {
            boolean change = rand.nextBoolean();
            switch (nextDirection) {
                case RIGHT, LEFT -> nextDirection = change ? Direction.TOP : Direction.DOWN;
                case TOP, DOWN -> nextDirection = change ? Direction.LEFT : Direction.RIGHT;
            }
        }

    }

}
