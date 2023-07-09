package game.view.gameWindow;

import game.logic.table.infoEnums.Direction;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;

public class GameView {
    ViewController controller;
    public void setController(ViewController controller) { this.controller = controller; }

    @FXML
    private Button backButton;

    @FXML
    private Canvas gameTable;
    public Canvas getGameTable() { return gameTable; }
    @FXML
    private StackPane gameStackPane;

    public StackPane getGameStackPane() { return gameStackPane; }

    @FXML
    private Text livesNumText;
    public Text getLivesNumText() { return livesNumText; }

    @FXML
    private Text scoreTextNum;
    public Text getScoreTextNum() { return scoreTextNum; }

    @FXML
    void initialize() {
        gameTable.getGraphicsContext2D().setStroke(Color.web("0xD08000"));
        gameTable.getGraphicsContext2D().strokeRect(0.5, 0.5,
                gameTable.getWidth() - 1, gameTable.getHeight() - 1);

        gameStackPane.setClip(new Rectangle(0,0, gameStackPane.getPrefWidth() , gameStackPane.getPrefHeight()));

        setEvents();
    }

    private void loadStart() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                    "/game/view/startWindow/Start.fxml"));
            Stage stage = (Stage) backButton.getScene().getWindow();
            stage.setScene(new Scene(fxmlLoader.load()));
        } catch(IOException | IllegalStateException ex) {
            throw new RuntimeException(ex.getMessage());
        }
    }


    public void endGame() {
        loadStart();
        controller.stopGame();
    }
    private void setEvents() {
        backButton.setOnMouseClicked(event -> {
            endGame();
        });
        backButton.setOnKeyPressed(event -> {
            Direction newDirection =
                    switch (event.getCode()) {
                        case W:
                        case UP:
                            yield  Direction.TOP;
                        case A:
                        case LEFT:
                            yield Direction.LEFT;
                        case S:
                        case DOWN:
                            yield  Direction.DOWN;
                        case D:
                        case RIGHT:
                            yield  Direction.RIGHT;
                        default:
                            yield null;

                    };
            if (newDirection != null) {
                controller.getController().getGame().getUnits().get(0).setNextDirection(newDirection);
            }
        });
    }
}
