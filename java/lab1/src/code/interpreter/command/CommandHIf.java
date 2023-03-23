package interpreter.command;

import interpreter.data.Data;
import interpreter.data.eDirection;

public class CommandHIf implements ICommand{
    @Override
    public void execute(Data data) {
        data.setDirections((data.popStack() != 0) ? eDirection.LEFT : eDirection.RIGHT);
    }
}