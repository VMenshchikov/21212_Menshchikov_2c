package interpreter.command;

import java.io.IOException;
import java.lang.RuntimeException;
import java.io.InputStreamReader;
 

import interpreter.data.Data;

public class CommandInputChar implements ICommand{
    @Override
    public void execute(Data data) {
        try(InputStreamReader a = new InputStreamReader(System.in)) {
        data.pushStack(a.read());
        } catch (IOException a) {
            throw new RuntimeException(a.getMessage());
        }
    }
}