package game.logic.gameWindow.units;

public class PosUnit {
    PosUnit(){};
    PosUnit(PosUnit a) {
        this.posX = a.posX;
        this.posY = a.posY;
    }

    public int posX = 0;
    public int posY = 0;
}
