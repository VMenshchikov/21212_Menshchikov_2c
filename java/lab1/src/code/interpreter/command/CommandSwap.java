package interpreter.command;

import interpreter.data.Data;

public class CommandSwap implements ICommand{
    @Override
    public void execute(Data data) {
        var tmp1 = data.popStack();
        var tmp2 = data.popStack();
        data.pushStack(tmp1);
        data.pushStack(tmp2);
    }
}