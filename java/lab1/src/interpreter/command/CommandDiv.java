package interpreter.command;

import interpreter.data.Data;

public class CommandDiv implements ICommand{
    @Override
    public void execute(Data data) {
        var tmp = data.popStack();
        data.pushStack(data.popStack() / tmp);
    }
}