package game.logic.gameWindow.units.brains;

import game.logic.gameWindow.units.PosUnit;
import game.logic.table.infoEnums.Direction;
import org.jetbrains.annotations.NotNull;

public class RadiusConvergence implements Brain{
    @Override
    public Direction chooseDirection(@NotNull PosUnit myPos, @NotNull PosUnit pacmanPos, @NotNull Direction pacmanDir) {
        int deltaX = myPos.posX - pacmanPos.posX;
        int deltaY = myPos.posY - pacmanPos.posY;

        switch (pacmanDir) {
            case DOWN -> deltaY-= 5;
            case TOP -> deltaY+= 5;
            case RIGHT -> deltaX-= 5;
            case LEFT -> deltaX+= 5;
        }

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
