package game.logic.table;

import javafx.scene.paint.Color;
import game.logic.table.infoEnums.*;
public class CellInfo {
    CellInfo(){};
    CellInfo(Type nType, Position nPos, Corner nCorn) {
        type = nType;
        pos = nPos;
        corn = nCorn;
    }
    public Type type = null;
    public Position pos = null;
    public Corner corn = null;

    public Color color = Color.web("0x0DC2EB");
}