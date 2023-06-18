package game.view;

import game.logic.gameWindow.GameWindow;
import game.logic.table.CellInfo;
import game.logic.table.Table;
import game.logic.table.infoEnums.Position;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Tab;
import javafx.scene.paint.Color;
import javafx.scene.shape.ArcType;
import org.jetbrains.annotations.NotNull;

//import static sun.jvm.hotspot.oops.MethodData.cellSize;

@SuppressWarnings("ClassEscapesDefinedScope")
public class Painter {
    static final int fatnessWalls = 2;
    static void paintCorner(double x, double y, double fatness, double d, double rotate, Color color, @NotNull GraphicsContext gc) {
        gc.setStroke(color);
        gc.setLineWidth(fatness);
        gc.strokeArc(x, y, d, d, rotate * 90, 90, ArcType.OPEN);
    }

    static void paintLine(double x, double y, double w, double h, double fatness, Color color, @NotNull GraphicsContext gc) {
        gc.setStroke(color);
        gc.setLineWidth(fatness);
        gc.strokeLine(x, y, x + w, y + h);
    }

    static void paintEat(double x, double y, double r, Color color, @NotNull GraphicsContext gc) {
        gc.setFill(color);
        gc.fillOval(x, y, r, r);
    }

    public static void refillEat(double x, double y, double s, Color color, @NotNull GraphicsContext gc) {
        gc.setFill(color);
        gc.fillRect(x, y,s - 1,s - 1);
    }

    @SuppressWarnings("ClassEscapesDefinedScope")
    public static void paintTable(CellInfo[][] info, @NotNull Canvas cv, int cellSize){

        final int indentX = 0,
                indentY = 0;
        GraphicsContext gc = cv.getGraphicsContext2D();
        for (int y = 0; y < Table.getTableHeight(); y++) {
            for (int x = 0; x < Table.getTableWidth(); x++) {
                int curX = indentX + x * cellSize,
                    curY = indentY + y * cellSize;
                int errX = 0, errY = 0;
                switch (info[y][x].type) {
                    case EXTRAWALL, LINE -> {
                        errX += (info[y][x].pos == Position.VERTICAL) ? (cellSize / 2) : 0;
                        errY += (info[y][x].pos == Position.HORIZONTAL) ? (cellSize / 2) : 0;
                        int wight = info[y][x].pos == Position.HORIZONTAL ? cellSize : 0,
                                height = info[y][x].pos == Position.VERTICAL ? cellSize : 0;
                        paintLine(curX + errX, curY + errY, wight, height, fatnessWalls,
                                info[y][x].color, gc);
                    }
                    case CORN -> {
                        switch (info[y][x].corn) {
                            case LTOP -> {
                                errX += cellSize / 2;
                                errY += cellSize / 2;
                            }
                            case RTOP -> {
                                errX -= cellSize / 2;
                                errY += cellSize / 2;
                            }
                            case LDOWN -> {
                                errX += cellSize / 2;
                                errY -= cellSize / 2;
                            }
                            case RDOWN -> {
                                errX -= cellSize / 2;
                                errY -= cellSize / 2;
                            }
                        }
                        paintCorner(curX + errX, curY + errY, fatnessWalls, cellSize,
                                info[y][x].corn.ordinal() * 45,
                                info[y][x].color, gc);
                    }
                    case EAT -> {
                        int r = cellSize / 4;
                        errX = cellSize / 2 - r / 2;
                        errY = cellSize / 2 - r / 2;
                        paintEat(curX + errX, curY + errY, cellSize/4, info[y][x].color, gc);
                    }
                    case BIGEAT, BERRY -> {
                        int r = cellSize / 2;
                        errX = cellSize / 2 - r / 2;
                        errY = cellSize / 2 - r / 2;
                        paintEat(curX + errX, curY + errY, cellSize/2, info[y][x].color, gc);
                    }
                    default -> {}
                }
            }
        }

    }

}
