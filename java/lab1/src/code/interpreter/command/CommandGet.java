package interpreter.command;

import interpreter.data.Data;
import my.MyPair;

public class CommandGet implements ICommand{
    @Override
    public void execute(Data data) {
        MyPair<Integer, Integer> pos = new MyPair<Integer, Integer>();
        pos.setSecond(data.popStack().intValue());
        pos.setFirst(data.popStack().intValue());
        data.pushStack(data.getCode(pos) - '0');
    }
}