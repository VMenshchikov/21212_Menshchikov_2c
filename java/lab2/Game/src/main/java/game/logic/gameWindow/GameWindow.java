package game.logic.gameWindow;

import game.logic.gameWindow.units.GhostLogic;
import game.logic.gameWindow.units.PacmanLogic;
import game.logic.gameWindow.units.PosUnit;
import game.logic.gameWindow.units.UnitLogic;
import game.logic.gameWindow.units.brains.*;
import game.logic.table.Table;
import game.logic.table.infoEnums.Direction;
import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.util.Duration;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;


public class GameWindow {
    private int score = 0;
    int numLvl = 1;
    static final int allLvl = 3;
    int[][] poss = {{24, 25, 23, 11, 24, 11, 23, 12, 24, 12},
                    {23, 25, 21, 12, 22, 12, 23, 12, 24, 12},
                    {24, 25, 25, 4, 38, 11, 25, 5, 40, 11}};
    int[] delay = {0, 2000, 5000, 10000};
    Brain[] brains = {new RandomBrain(), new StupidConvergence(), new RandomConvergence(), new RadiusConvergence()};
    String[] colors = {"red", "pink", "yellow", "blue"};
    int lives = 3;
    private int currentEatCount = 0;
    public int getCurrentEatCount() { return currentEatCount; }
    public void setCurrentEatCount(int currentEatCount) { this.currentEatCount = currentEatCount; }

    public static int getAllLvl() { return allLvl; }
    public int getNumLvl() { return numLvl; }
    public void setNumLvl(int numLvl) { this.numLvl = numLvl; }
    public int getLives() { return lives; }
    public void setLives(int lives) { this.lives = lives; }
    public void setScore(int newScore) { score = newScore; }
    public int getScore() { return score; }
    ArrayList<UnitLogic> units = new ArrayList<>();
    private Table table = new Table();


    public ArrayList<UnitLogic> getUnits() { return units; }
    public Table getTable() { return table; }
    //pacman always first
    public void init(int poss[], Brain brains[], String colors[], int delay[]) {
        if (poss.length % 2 != 0) throw new RuntimeException("invalid pos count");
        if (brains.length != (poss.length / 2 - 1)) throw new RuntimeException("invalid brains");
        int i = 0;
        PacmanLogic pacman = new PacmanLogic(poss[i++], poss[i++]);
        units.add(pacman);

        for (; i < poss.length;) {
            GhostLogic ghost = new GhostLogic(poss[i++], poss[i++], brains[(i-2)/2-1], colors[(i-2)/2-1]);
            ghost.setStopped(true);
            TimerTask start = new TimerTask() {
                @Override
                public void run() {
                    ghost.setStopped(false);
                }
            };
            Timer timer = new Timer();
            timer.schedule(start, delay[(i-2)/2-1]);
            units.add(ghost);


            KeyFrame frame = new KeyFrame(Duration.millis(500), event -> {
                if (!ghost.isStopped()) {
                    ghost.chooseNextDirection(units.get(0).getCurPos(), units.get(0).getCurDirection(), table);
                }
            });
            Timeline tl = new Timeline(frame);
            tl.setCycleCount(Animation.INDEFINITE);
            tl.play();
            ghost.setBrainLoop(tl);
        }
    }
    public @Nullable GhostLogic checkDeath() {
        PosUnit pacmanPos = getUnits().get(0).getCurPos();
        Direction pacmanDir = getUnits().get(0).getCurDirection();

        for (int i = 1; i < getUnits().size(); ++i) {
            GhostLogic unit = (GhostLogic)getUnits().get(i);
            //if (!unit.killPacman) return null;
            PosUnit myPos = unit.getCurPos();
            if (pacmanPos.posX == myPos.posX && pacmanPos.posY == myPos.posY) {
                System.out.println("Pacman killed : 1");
                return unit;
            }
            Direction myDirection = unit.getCurDirection();
            if (pacmanPos.posY == myPos.posY) {
                if (pacmanPos.posX == myPos.posX - 1 && pacmanDir == Direction.LEFT && myDirection == Direction.RIGHT) {
                    System.out.println("Pacman killed : LR");
                    return unit;
                }
                if ((pacmanPos.posX == myPos.posX + 1 && pacmanDir == Direction.RIGHT && myDirection == Direction.LEFT)) {
                    System.out.println("Pacman killed : RL");
                    return unit;
                }
            }
            if (pacmanPos.posX == myPos.posX) {
                if (pacmanPos.posY == myPos.posY - 1 && pacmanDir == Direction.TOP && myDirection == Direction.DOWN) {
                    System.out.println("Pacman killed : TD");
                    return unit;
                }
                if ((pacmanPos.posY == myPos.posY + 1 && pacmanDir == Direction.DOWN && myDirection == Direction.TOP)) {
                    System.out.println("Pacman killed : DT");
                    return unit;
                }
            }
        }
        return null;
    }
    public void stopUpdatePos() {
        for (var unit : units) {
            if (unit instanceof GhostLogic) {
                ((GhostLogic)unit).getBrainLoop().stop();
            }
        }
    }

    public void reinit() {
        units.clear();
        init(poss[numLvl - 1], brains, colors, delay);
    }
}
