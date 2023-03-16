package interpreter.command;

import java.util.Random;

import interpreter.data.Data;
import interpreter.data.eDirection;

public class CommandRandom implements ICommand{
    @Override
    public void execute(Data data) {
        int a = new Random().nextInt() % 4;
        data.setDirections(eDirection.values()[a]);
    }
}