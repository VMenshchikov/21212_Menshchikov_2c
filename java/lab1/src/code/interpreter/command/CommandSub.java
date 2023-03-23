package interpreter.command;

import interpreter.data.Data;

public class CommandSub implements ICommand{
    @Override
    public void execute(Data data) {
        var tmp = data.popStack();
        data.pushStack(data.popStack() - tmp);
    }
}