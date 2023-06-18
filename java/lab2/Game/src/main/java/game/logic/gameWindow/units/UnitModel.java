package game.logic.gameWindow.units;

public abstract class UnitModel<F, S> {
    protected F firstModel;
    protected S secondModel;
    public abstract void swapModels();
    public void setFirstModel(F firstModel) { this.firstModel = firstModel; }
    public void setSecondModel(S secondModel) { this.secondModel = secondModel; }

    public F getFirstModel() { return firstModel; }

    public S getSecondModel() { return secondModel; }
}
