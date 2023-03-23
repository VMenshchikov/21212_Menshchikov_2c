package interpreter.command;

import interpreter.data.Data;

public class CommandMult implements ICommand{
    @Override
    public void execute(Data data) {
        data.pushStack(data.popStack() * data.popStack());
    }
}