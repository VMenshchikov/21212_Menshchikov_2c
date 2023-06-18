package game.logic.gameWindow.units.brains;

import game.logic.gameWindow.units.PosUnit;
import game.logic.table.infoEnums.Direction;
import org.jetbrains.annotations.NotNull;

public class StupidConvergence implements Brain{
    @Override
    public Direction chooseDirection(@NotNull PosUnit myPos, @NotNull PosUnit pacmanPos, Direction pacmanDir) {
        int deltaX = myPos.posX - pacmanPos.posX;
        int deltaY = myPos.posY - pacmanPos.posY;
        boolean horizontal = Math.abs(deltaX) > Math.abs(deltaY);
        if (horizontal) {
            if (deltaX >= 0) {
                return Direction.LEFT;
            } else return Direction.RIGHT;
        } else {
            if (deltaY >= 0) {
                return Direction.TOP;
            } else return Direction.DOWN;
        }
    }
}
