/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

import Interpreter.Expression;
import Interpreter.Environment;
import Interpreter.DoubleExpression;
import java.util.ArrayList;

/**
 *
 * @author hako
 */
public class PlusExpression extends Expression {

    public ArrayList<Expression> expr;
    
    public PlusExpression(ArrayList<Expression> expr){
        this.expr = expr;
    }
    
    @Override
    public FValue eval(Environment e) {
        Double sum = 0.0;
        for (Expression exp : expr){
            sum += exp.eval(e).getAsDouble();
        }
        return (new FValue(sum));
    }

    
}
