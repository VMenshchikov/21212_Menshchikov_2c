import interpreter.Interpreter;
import java.io.PrintStream;
import java.beans.Transient;
import java.io.ByteArrayOutputStream;

//import org.junit.jupiter.api.Assertions;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.BeforeEach;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;

public class MyTest {
    // private int count = 0;
    // private String qwe = new String();

    ByteArrayOutputStream OStream;
    //PrintStream stand = System.out;

    @BeforeEach
    public void setStream() {
        OStream = new ByteArrayOutputStream();

        System.setOut(new PrintStream(OStream));
    }

    // @AftherEach

    @Tag("move")
    @Test
    public void left() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(15, 2,
                new File("build/resources/test/testsFiles/left.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("left", OStream.toString());
    }

    @Tag("move")
    @Test
    public void right() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(15, 2,
                new File("build/resources/test/testsFiles/right.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("right", OStream.toString());

    }

    @Tag("move")
    @Test
    public void down() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(2, 15,
                new File("build/resources/test/testsFiles/down.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("down", OStream.toString());

    }

    @Tag("move")
    @Test
    public void up() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(2, 10,
                new File("build/resources/test/testsFiles/up.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("up", OStream.toString());

    }

    @Tag("arifmetics")
    @Test
    public void add() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/add.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("15", OStream.toString());

    }

    @Tag("arifmetics")
    @Test
    public void subtract() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/subtract.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("5", OStream.toString());

    }

    @Tag("arifmetics")
    @Test
    public void multiply() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(21, 1,
                new File("build/resources/test/testsFiles/multiply.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("1024", OStream.toString());

    }

    @Tag("arifmetics")
    @Test
    public void divide() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/devide.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("2", OStream.toString());

    }

    @Tag("arifmetics")
    @Test
    public void modulo() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/modulo.txt"),
                new File("build/resources/test/config.properties"));

        assertEquals("1", OStream.toString());
    }

    @Tag("logic")
    @Test
    public void not() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/not.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("0 1", OStream.toString());
    }

    @Tag("logic")
    @Test
    public void greater() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/greater.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("1 0", OStream.toString());
    }

    @Tag("if")
    @Test
    public void HIf() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 20,
                new File("build/resources/test/testsFiles/HIf.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("01", OStream.toString());
    }

    @Tag("if")
    @Test
    public void VIf() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 20,
                new File("build/resources/test/testsFiles/VIf.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("01", OStream.toString());
    }

    @Tag("stack")
    @Test
    public void dup() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(25, 1,
                new File("build/resources/test/testsFiles/dup.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("99ll\n\n", OStream.toString());
    }

    @Tag("stack")
    @Test
    public void swap() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/swap.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("48", OStream.toString());
    }

    @Tag("stack")
    @Test
    public void pop() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(20, 1,
                new File("build/resources/test/testsFiles/pop.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("21530", OStream.toString());
    }

    @Tag("code")
    @Test
    public void get() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(15, 5,
                new File("build/resources/test/testsFiles/get.txt"),
                new File("build/resources/test/config.properties"));
        assertEquals("5", OStream.toString());
    }

    @Tag("code")
    @Test
    public void put() {
        Interpreter inter = new Interpreter();
        inter.ПожалуйстаИнтерпретируйЭто(15, 5,
                new File("build/resources/test/testsFiles/put.txt"),
                new File("build/resources/test/config.properties"));
       /*  stand.print(OStream);
        stand.flush(); */
        try {
            assertEquals("4", OStream.toString());
        } catch (Error e) {
            System.err.print(e.getMessage());
            System.err.flush();
        }
    }

}