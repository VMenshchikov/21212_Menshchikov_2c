package interpreter;

import interpreter.command.ICommand;
import interpreter.data.Data;
import my.MyFactory;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;

/** 
 * Основной метод интерпретатора Befunge-93
 * Использует 'Data' для определения начальных параметров 
 * @see Data
*/
public class Interpreter {
    private Data data;

    public Interpreter() {
        data = new Data();
    }
    
    /**
     * 
     * @param xSize Размер поля по координате Х
     * @param ySize Размер поля по координате Х
     * @param code Файл с кодом программы
     * @param config properties файл для фабрики
     * @see MyFactory
     */
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
                    a.printStackTrace();
                    throw ex;
        }
    }
}
