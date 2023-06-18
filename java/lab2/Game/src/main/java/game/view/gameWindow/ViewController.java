package game.view.gameWindow;

import game.control.gameWindow.GameController;
import game.logic.gameWindow.units.GhostLogic;
import game.logic.gameWindow.units.UnitLogic;
import game.logic.table.Table;
import game.view.Painter;
import javafx.animation.*;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class ViewController {
    GameView window;
    GameController controller;

    public void stopGame() {
        controller.stopLoops();
        controller.getGame().stopUpdatePos();
        window.endGame();
                controller.getName();
    }

    public GameController getController() { return controller; }

    static private final int cellSize = 20;

    public void setController(GameController controller) {
        this.controller = controller;
    }

    public void initialize(@NotNull Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(GameController.class.getResource("/game/view/gameWindow/Game.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("MyPerfectPacMan!");
        stage.setScene(scene);
        stage.show();

        window = fxmlLoader.getController();
        window.getLivesNumText().setText(Integer.toString(controller.getGame().getLives()));
        window.setController(this);
        controller.startLvl();
    }

    public void paintTable(@NotNull Table table) {
        Painter.paintTable(table.getGameTableInfo(), window.getGameTable(), cellSize);
    }

    public void updateScore(int score) {
        window.getScoreTextNum().setText(Integer.toString(score));
    }

    public void updateLives(int lives) {
        window.getLivesNumText().setText(Integer.toString(lives));
    }
    public void deleteEat(int xEat, int yEat) {
        Painter.refillEat(xEat * cellSize + 1, yEat * cellSize + 1,
                cellSize - 2, Color.web("0x010a3c"),
                window.getGameTable().getGraphicsContext2D());
    }
    public void removeUnits() {
        window.getGameStackPane().getChildren().remove(1, 6);
    }
    public boolean unitsIsContains() {
        return window.getGameStackPane().getChildren().size() == 6;
    }
    public void clearLvl() {
        window.getGameTable().getGraphicsContext2D().clearRect(2, 2,
                window.getGameTable().getWidth() - 4,
                window.getGameTable().getHeight() - 4);
    }
    public void respawn(@NotNull GhostLogic killed) {
        var tmp = deathAnim(killed);
        killed.setCurPos(killed.getSpawnPos());
        tmp.setOnFinished(e -> {
            killed.getModel().swapModels();;
            var mod = (ImageView)killed.getModel().getFirstModel();
            mod.setRotate(0);
            mod.setTranslateX(killed.getCurPos().posX * cellSize);
            mod.setTranslateY(killed.getCurPos().posY * cellSize);
            TimerTask move = new TimerTask() {
                @Override
                public void run() {
                    killed.setStopped(false);
                }
            };
            Timer timer = new Timer();
            timer.schedule(move, 5000);
        });
        tmp.play();
    }

    public void death(UnitLogic unit) {
        var tmp = deathAnim(unit);
        tmp.play();
    }

    private @NotNull ParallelTransition deathAnim(@NotNull UnitLogic unit) {
        Duration fallTime = Duration.seconds(4);
        var image = (ImageView)unit.getModel().getFirstModel();
        RotateTransition rt = new RotateTransition(fallTime.divide(5));
        rt.setNode(image);
        rt.setCycleCount(5);
        rt.setByAngle(360);

        TranslateTransition ttDown = new TranslateTransition(fallTime.multiply(0.7));
        ttDown.setNode(image);
        ttDown.setByY(Table.getTableHeight() * cellSize + 20);
        ttDown.setInterpolator(Interpolator.EASE_IN);

        TranslateTransition ttUp = new TranslateTransition(fallTime.multiply(0.3));
        ttUp.setNode(image);
        ttUp.setByY(-cellSize * 3);
        ttUp.setInterpolator(Interpolator.EASE_OUT);

        SequentialTransition sq = new SequentialTransition(ttUp, ttDown);

        ParallelTransition pt = new ParallelTransition();
        pt.getChildren().addAll(rt, sq);

        return pt;
    }

    public void endGame(@NotNull Duration frameTime, @NotNull UnitLogic pacman, double secAnim) {
        RotateTransition rt = new RotateTransition(frameTime.multiply(2), (ImageView)pacman.getModel().getFirstModel());
        rt.setCycleCount(5);
        rt.setByAngle(360);
        rt.play();
    }

    public KeyFrame animated(Duration frameTime, ArrayList<UnitLogic> units, Table table) {

        KeyFrame move = new KeyFrame(frameTime.multiply(1), event -> {


            RotateTransition rt;
            TranslateTransition tt;
            ParallelTransition pt;

            pt = new ParallelTransition();
            for (var unit : units) {
                var image = (ImageView)unit.getModel().getFirstModel();
                if (unit.isStopped()) continue;
                rt = new RotateTransition();
                rt.setDuration(frameTime);
                rt.setNode(image);
                rt.setByAngle(unit.getRotate(table));
                pt.getChildren().add(rt);

                unit.move(table);

                tt = new TranslateTransition();
                tt.setNode(image);
                tt.setToX(unit.getCurPos().posX * cellSize);
                tt.setToY(unit.getCurPos().posY * cellSize);
                tt.setDuration(frameTime);

                if (unit.getCurPos().posX == Table.getTableWidth()) { //jump right to left
                    unit.getCurPos().posX = 0;
                    jumpXAnimation(pt, tt, unit, -cellSize, frameTime);
                } else if (unit.getCurPos().posX == -1) { //jump left to right
                    unit.getCurPos().posX = Table.getTableWidth() - 1;
                    jumpXAnimation(pt, tt, unit, cellSize, frameTime);
                } else if (unit.getCurPos().posY == Table.getTableHeight()) { //jump down to top
                    unit.getCurPos().posY = 0;
                    jumpYAnimation(pt, tt, unit, -cellSize, frameTime);
                } else if (unit.getCurPos().posY == -1) { //jump top to down
                    System.out.flush();
                    unit.getCurPos().posY = Table.getTableHeight() - 1;
                    jumpYAnimation(pt, tt, unit, cellSize, frameTime);
                    System.out.flush();
                } else { //simple move
                    pt.getChildren().add(tt);
                }
            }
            pt.play();
        });
        return move;
    }

    void jumpXAnimation(@NotNull ParallelTransition pt, @NotNull TranslateTransition tt,
                        @NotNull UnitLogic unit, int shift, @NotNull Duration frameTime) {
        var image = (ImageView)unit.getModel().getFirstModel();

        tt.setDuration(frameTime.divide(2));
        tt.setOnFinished( e -> {
            image.setTranslateX(unit.getCurPos().posX * cellSize + shift);
        });

        TranslateTransition tt2 = new TranslateTransition();
        tt2.setNode(image);
        tt2.setDuration(frameTime.divide(2));
        tt2.setToX(unit.getCurPos().posX * cellSize);

        var sq = new SequentialTransition();
        sq.getChildren().addAll(tt, tt2);
        pt.getChildren().add(sq);
    }
    void jumpYAnimation(@NotNull ParallelTransition pt, @NotNull TranslateTransition tt,
                        @NotNull UnitLogic unit, int shift, @NotNull Duration frameTime) {
        var image = (ImageView)unit.getModel().getFirstModel();

        tt.setDuration(frameTime.divide(2));
        tt.setOnFinished( e -> {
            image.setTranslateY(unit.getCurPos().posY * cellSize + shift);
        });

        TranslateTransition tt2 = new TranslateTransition();
        tt2.setNode(image);
        tt2.setDuration(frameTime.divide(2));
        tt2.setToY(unit.getCurPos().posY * cellSize);

        var sq = new SequentialTransition();
        sq.getChildren().addAll(tt, tt2);
        pt.getChildren().add(sq);
    }

    public void addUnits(@NotNull ArrayList<UnitLogic> units) {
        for (var unit : units) {
            var image = (ImageView)unit.getModel().getFirstModel();
            StackPane.setAlignment(image, Pos.TOP_LEFT);
            window.getGameStackPane().getChildren().add(image);
            image.setTranslateX(cellSize * (unit.getCurPos().posX));
            image.setTranslateY(cellSize * (unit.getCurPos().posY));
        }
    }
}
