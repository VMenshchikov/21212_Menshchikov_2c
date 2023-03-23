package interpreter.command;

import interpreter.data.Data;

public class CommandDup implements ICommand{
    @Override
    public void execute(Data data) {
        var tmp = data.popStack();
        if (tmp == null) return;
        data.pushStack(tmp);
        data.pushStack(tmp);
    }
}