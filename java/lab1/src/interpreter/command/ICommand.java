package interpreter.command;

import interpreter.data.Data;

public interface ICommand {
    public void execute(Data data);
};