package interpreter.command;

import interpreter.data.Data;
import my.MyPair;

public class CommandPut implements ICommand {
    @Override
    public void execute(Data data) {
        MyPair<Long, Long> pos = new MyPair<>();
        char ch = (char)data.popStack().intValue();
        pos.setFirst(data.popStack().longValue());
        pos.setSecond(data.popStack().longValue());
        data.setCode(pos, ch);
    }
}