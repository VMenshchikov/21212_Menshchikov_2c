package interpreter.command;

import java.util.Scanner;
import java.lang.Thread;
import interpreter.data.Data;
import java.util.InputMismatchException;

public class CommandInputInt implements ICommand{
    @Override
    public void execute(Data data) {
        try(Scanner sc = new Scanner(System.in)){
            data.pushStack(sc.nextLong());
        } 
    }
}