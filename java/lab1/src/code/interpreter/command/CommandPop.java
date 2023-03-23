package interpreter.command;

import interpreter.data.Data;

public class CommandPop implements ICommand{
    @Override
    public void execute(Data data) {
        data.popStack();
    }
}