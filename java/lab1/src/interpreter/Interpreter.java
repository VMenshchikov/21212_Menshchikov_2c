package interpreter;

import interpreter.command.ICommand;
import interpreter.data.Data;
import my.MyFactory;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;


public class Interpreter {
    private Data data;

    public Interpreter() {
        data = new Data();
    }
    
    public void ПожалуйстаИнтерпретируйЭто(int xSize, int ySize, File code, File config) {
        try {
            Properties conf = new Properties();
            conf.load(new FileInputStream(config));
            MyFactory<ICommand> fact = new MyFactory<ICommand>(conf);
            data.loadData(code, xSize, ySize);
            Character sym;
            while (((sym = data.getNextChar())) != '@') {
                if (sym == ' ') { continue; }
                //System.err.print(sym);
                //System.out.print(" : ");
                //System.err.flush();
                if (sym <= '9' && sym >= '0') {
                    data.pushStack((long)sym - (long)'0'); 
                } else {
                    fact.getObject(Character.toString(sym)).execute(data);
                }
            }
        } catch (IOException | InstantiationException | IllegalAccessException | 
                 IllegalArgumentException | InvocationTargetException |
                 ClassNotFoundException | NoSuchMethodException  a ) {
                    RuntimeException ex = new RuntimeException(a.getMessage());
                    ex.setStackTrace(a.getStackTrace());
                    throw ex;
        }
    }
}
