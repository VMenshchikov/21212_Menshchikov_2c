package interpreter.command;

import interpreter.data.Data;

public class CommandNot implements ICommand{
    @Override
    public void execute(Data data) {
        data.pushStack((data.popStack() == 0l) ? 1l : 0l);
    }
}