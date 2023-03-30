module game.startWindow {
    requires javafx.controls;
    requires javafx.fxml;


    opens game.startWindow to javafx.fxml;
    exports game.startWindow;
}