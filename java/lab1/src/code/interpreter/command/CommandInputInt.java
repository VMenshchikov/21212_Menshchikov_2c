package interpreter.command;

import java.util.Scanner;
import interpreter.data.Data;

public class CommandInputInt implements ICommand{
    @Override
    public void execute(Data data) {
        try(Scanner sc = new Scanner(System.in)){
            data.pushStack(sc.nextLong());
        } 
    }
}