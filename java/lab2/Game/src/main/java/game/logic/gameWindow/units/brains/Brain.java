package game.logic.gameWindow.units.brains;

import game.logic.gameWindow.units.PosUnit;
import game.logic.table.infoEnums.Direction;

import java.util.Random;
import java.util.Timer;

public interface  Brain {
    Random rand = new Random(System.currentTimeMillis());
    Direction chooseDirection(PosUnit myPos, PosUnit pacmanPos, Direction pacmanDir);
}
