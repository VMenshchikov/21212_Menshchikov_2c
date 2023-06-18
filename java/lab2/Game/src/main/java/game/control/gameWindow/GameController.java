package game.control.gameWindow;

import game.logic.gameWindow.GameWindow;
import game.logic.gameWindow.units.GhostLogic;
import game.logic.gameWindow.units.PosUnit;
import game.logic.gameWindow.units.UnitLogic;
import game.logic.table.CellInfo;
import game.logic.table.infoEnums.Type;
import game.view.gameWindow.ViewController;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.util.Duration;

import java.util.Timer;
import java.util.TimerTask;


public class GameController {
    String name;
    static private final Duration frameTime = Duration.millis(200);
    Timeline anim;
    Timeline lifeCheck;
    Timeline scoreUpdate;
    private GameWindow game;
    private ViewController view;
    public GameWindow getGame() { return game; }
    public GameController(String name) {
        this.name = name;
        game = new GameWindow();
        view = new ViewController();
        view.setController(this);
    }

    public ViewController getView() { return view; }

    public String getName() { return name; }

    public void startLvl(){
        loadLvl();
        start();
    }
    private void loadLvl() {
        String lvlName = "lvl" + game.getNumLvl() + ".txt";
        String lvl = "/lvls/" + lvlName;
        game.getTable().loadLvl(lvl);
        view.paintTable(game.getTable());
    }
    public void stopLoops() {
        anim.stop();
        lifeCheck.stop();
        scoreUpdate.stop();
    }

    void backStartWindow() {
        view.stopGame();
    }

    private void eatLoop() {
        KeyFrame score = new KeyFrame(frameTime, event -> {
            UnitLogic pacman = game.getUnits().get(0);
            PosUnit pacmanPos = pacman.getCurPos();
            CellInfo currentCell = game.getTable().getGameTableInfo()[pacmanPos.posY][pacmanPos.posX];
            if (currentCell.type == Type.EAT) {
                currentCell.type = Type.EMPTY;
                game.setScore(game.getScore() + 10);
                view.updateScore(game.getScore());
                view.deleteEat(pacmanPos.posX, pacmanPos.posY);
               var eat = game.getCurrentEatCount() + 1;
                game.setCurrentEatCount(eat);
                if (game.getTable().getStartEatCount() == game.getCurrentEatCount()) {
                    game.setCurrentEatCount(0);
                    stopLoops();
                    game.stopUpdatePos();
                    double secAnim = 3;
                    view.endGame(frameTime, game.getUnits().get(0), secAnim);

                    if (game.getNumLvl() < game.getAllLvl()) {
                        KeyFrame delayLoadLvl = new KeyFrame(Duration.seconds(4), e -> {
                            game.setNumLvl(game.getNumLvl() + 1);
                            view.removeUnits();
                            view.clearLvl();
                            startLvl();
                            anim.play();
                        });
                        Timeline timer = new Timeline(delayLoadLvl);
                        timer.setCycleCount(1);
                        timer.play();
                    }
                }
            } else if (currentCell.type == Type.BIGEAT && !pacman.isRage()) {
                view.deleteEat(pacmanPos.posX, pacmanPos.posY);
                for(var unit : game.getUnits()) {
                    unit.setRage(true);
                    unit.getModel().swapModels();
                    Timer timer = new Timer();
                    timer.schedule(new TimerTask() {
                        @Override
                        public void run() {
                            if (unit.isRage()){
                                unit.getModel().swapModels();
                            }
                            unit.setRage(false);
                        }
                    }, 15000);
                }
            } else  if (currentCell.type == Type.BERRY) {
                currentCell.type = Type.EMPTY;
                game.setScore(game.getScore() + 1000);
                view.updateScore(game.getScore());
                view.deleteEat(pacmanPos.posX, pacmanPos.posY);
            }
        });
        scoreUpdate = new Timeline(score);
        scoreUpdate.setCycleCount(Animation.INDEFINITE);
        scoreUpdate.play();
    }

    private void lifeLoop() {
        KeyFrame check = new KeyFrame(frameTime, event -> {
            var killed = game.checkDeath();
            if (killed != null) {
                if (!killed.isRage()) {
                    game.stopUpdatePos();
                    game.setLives(game.getLives() - 1);
                    view.updateLives(game.getLives());
                    view.death(game.getUnits().get(0));

                    stopLoops();
                    if (game.getLives() != 0) {
                        KeyFrame frame = new KeyFrame(Duration.seconds(5), e -> {
                            start();
                        });
                        Timeline timer = new Timeline(frame);
                        timer.setCycleCount(1);
                        timer.play();
                    } else {
                        backStartWindow();
                    }

                } else {
                    view.respawn(killed);
                    killed.setStopped(true);
                    killed.setRage(false);
                }
            }
        });

        lifeCheck = new Timeline(check);
        lifeCheck.setCycleCount(Animation.INDEFINITE);
        lifeCheck.play();

    }

    private void animated() {
        KeyFrame move = view.animated(frameTime, game.getUnits(), game.getTable());
        anim = new Timeline(move);
        anim.setCycleCount(Animation.INDEFINITE);
        anim.play();
    }


    void start() {
        game.reinit();
        if(view.unitsIsContains()) {
            view.removeUnits();
            stopLoops();
        }
        view.addUnits(game.getUnits());
        eatLoop();
        lifeLoop();
        animated();
    }

}


