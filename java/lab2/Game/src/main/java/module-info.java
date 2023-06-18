module game {
    requires javafx.controls;
    requires javafx.fxml;
    requires org.jetbrains.annotations;



/*
    exports game;
    opens game to javafx.fxml;
*/

    exports game.control.gameWindow;
    opens game.control.gameWindow to javafx.fxml;

    exports game.logic.gameWindow;
    opens game.logic.gameWindow to javafx.fxml;

    exports game.control.startWindow;
    opens game.control.startWindow to javafx.fxml;

    exports game.view;
    opens game.view to javafx.fxml;

    exports game.view.startWindow;
    opens game.view.startWindow to javafx.fxml;
    exports game.view.gameWindow;
    opens game.view.gameWindow to javafx.fxml;


}
