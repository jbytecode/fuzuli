
package Interpreter;

import java.util.ArrayList;


public class IncExpression extends Expression {

    public IncExpression(ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public FValue eval(Environment e) {
        System.out.println("Env: "+e.toString());
        System.out.println(this);
        FValue result = this.exprs.get(0).eval(e);
        System.out.println("Inc: "+result.getAsDouble());
        result.obj = result.getAsDouble()+1;
        return(result);
    }
    
    
}
