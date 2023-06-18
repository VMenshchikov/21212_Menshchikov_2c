package game.view.gameWindow;

import game.logic.gameWindow.units.UnitModel;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;


public class UnitModelView extends UnitModel<ImageView, Image> {
    @Override
    public void swapModels() {
        var tmp = firstModel.getImage();
        firstModel.setImage(secondModel);
        secondModel = tmp;
    }
}
