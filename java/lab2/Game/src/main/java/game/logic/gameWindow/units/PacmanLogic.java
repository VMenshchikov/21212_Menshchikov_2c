package game.logic.gameWindow.units;

import game.logic.table.infoEnums.Direction;
import game.view.gameWindow.UnitController;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.util.function.Function;

public class PacmanLogic extends UnitLogic {
    public PacmanLogic(int startX, int startY) {
        model = UnitController.createModel();
        UnitController.setPacman(model);
        curPos.posX = startX;
        curPos.posY = startY;
        spawnPos = new PosUnit(curPos);
    }
}
