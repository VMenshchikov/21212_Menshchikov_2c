package game.view.gameWindow;

import game.logic.gameWindow.units.UnitModel;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class UnitController {
     final static int size = 25;
    static public UnitModel<ImageView, Image> createModel(){
        return new UnitModelView();
    }
    static public void setFirstGhost(UnitModel model, String color) {
        var tmp = new ImageView(new Image("/game/view/gameWindow/ghost_" + color + ".gif"));
        tmp.setFitWidth(size);
        tmp.setFitHeight(size);
        tmp.setRotate(0);
        model.setFirstModel(tmp);
    }
    static public void setSecondGhost(UnitModel model) {
        model.setSecondModel(new Image("/game/view/gameWindow/ghost_rage.gif"));
    }

    static public void setPacman(UnitModel model) {
        var tmp = new ImageView(new Image("/game/view/gameWindow/pacman2.gif"));
        tmp.setFitWidth(size);
        tmp.setFitHeight(size);
        tmp.setRotate(270);
        model.setFirstModel(tmp);
        model.setSecondModel(tmp.getImage());
    }
}
