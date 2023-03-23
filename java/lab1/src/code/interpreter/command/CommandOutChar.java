package interpreter.command;

import interpreter.data.Data;

public class CommandOutChar implements ICommand{
    @Override
    public void execute(Data data) {
        System.out.print((char)data.popStack().intValue());
        System.out.flush();
    }
}