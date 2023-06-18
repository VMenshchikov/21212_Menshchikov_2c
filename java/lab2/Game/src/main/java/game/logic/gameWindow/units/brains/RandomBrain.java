package game.logic.gameWindow.units.brains;

import game.logic.gameWindow.units.PosUnit;
import game.logic.table.infoEnums.Direction;
import org.jetbrains.annotations.NotNull;

public class RandomBrain implements Brain{

    @Override
    public Direction chooseDirection(@NotNull PosUnit myPos, @NotNull PosUnit pacmanPos, @NotNull Direction pacmanDir) {
        return Direction.values()[rand.nextInt(Direction.values().length)];
    }
}
