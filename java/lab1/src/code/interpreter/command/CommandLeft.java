package interpreter.command;

import interpreter.data.Data;
import interpreter.data.eDirection;

public class CommandLeft implements ICommand{
    @Override
    public void execute(Data data) {
        data.setDirections(eDirection.LEFT);
    }
}