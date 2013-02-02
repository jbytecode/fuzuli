/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

/**
 *
 * @author hako
 */
public class DoubleExpression extends Expression{
    
    FValue val;
    
    public DoubleExpression(double d){
        val = new FValue(d);
    }
    

    @Override
    public FValue eval(Environment e) {
        return(val);
    }

   
}
