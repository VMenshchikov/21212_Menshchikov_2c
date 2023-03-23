package interpreter.command;

import interpreter.data.Data;


public interface ICommand {
    /**
    * Исполняет команду
    * @see Data
    * @param data Data
    */
    public void execute(Data data);
};