package interpreter.command;

import interpreter.data.Data;

public class CommandBridge implements ICommand{
    @Override
    public void execute(Data data) {
        data.skipCh();
    }
}