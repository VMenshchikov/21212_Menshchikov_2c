package interpreter.command;

import interpreter.data.Data;

public class CommandGreater implements ICommand{
    @Override
    public void execute(Data data) {
        var value2 = data.popStack();
        data.pushStack((data.popStack() > value2) ? 1l : 0l);
    }
}