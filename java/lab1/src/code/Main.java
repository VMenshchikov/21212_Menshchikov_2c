import interpreter.Interpreter;

import java.io.File;

public class Main {
    public static void main(String[] argv) {

        java.util.Scanner s = new java.util.Scanner(System.in);
        long l = s.nextLong();



        File code = new File(argv[2]);
        File cfg = new File(argv[3]);
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(Integer.parseInt(argv[0]), 
                                        Integer.parseInt(argv[1]), code, cfg);
    }
}
