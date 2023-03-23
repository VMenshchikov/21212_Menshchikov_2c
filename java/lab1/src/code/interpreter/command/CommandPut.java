package interpreter.command;

import interpreter.data.Data;
import my.MyPair;

public class CommandPut implements ICommand {
    @Override
    public void execute(Data data) {
        MyPair<Long, Long> pos = new MyPair<>();
        pos.setSecond((Long)data.popStack().longValue());
        pos.setFirst(data.popStack().longValue());
        char ch = (char)(data.popStack().intValue() + '0');

        data.setCode(pos, ch);
    }
}