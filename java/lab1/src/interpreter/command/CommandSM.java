package interpreter.command;

import interpreter.data.Data;

public class CommandSM implements ICommand{
    @Override
    public void execute(Data data) {
        char tmp;
        while((tmp = data.getNextChar()) != '"') {
            data.pushStack((int)tmp);
        }
    }
}