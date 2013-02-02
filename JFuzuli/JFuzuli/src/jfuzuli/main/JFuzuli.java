package jfuzuli.main;

import Interpreter.DoubleExpression;
import Interpreter.Environment;
import Interpreter.Expression;
import Interpreter.FValue;
import Interpreter.Parser;
import java.io.File;

/**
 *
 * @author Mehmet Hakan Satman
 */

public class JFuzuli {

    public static void main(String[] args) {
        if (args.length == 1){
            Parser parser = new Parser(new File(args[0]));
            Expression e = parser.getNextExpression();
            FValue o = e.eval(new Environment());
            System.out.println(o.getAsDouble());
        }
    }
}
