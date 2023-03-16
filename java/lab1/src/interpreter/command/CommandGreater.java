package interpreter.command;

import interpreter.data.Data;

public class CommandGreater implements ICommand{
    @Override
    public void execute(Data data) {
        var tmp = data.popStack();
        data.pushStack((data.popStack() > tmp) ? 1 : 0);
    }
}