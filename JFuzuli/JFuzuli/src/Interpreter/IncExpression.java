
package Interpreter;

import java.util.ArrayList;


public class IncExpression extends Expression {

    public IncExpression(ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public FValue eval(Environment e) {
        FValue result = this.exprs.get(0).eval(e);
        result.obj = result.getAsDouble()+1;
        return(result);
    }
    
    
}
