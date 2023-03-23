package interpreter.command;

import interpreter.data.Data;

public class CommandOutInt implements ICommand{
    @Override
    public void execute(Data data) {
        System.out.print(data.popStack());
        System.out.flush();
    }
}