
package Interpreter;

import java.util.ArrayList;


public class TypeOfExpression extends Expression {

    public TypeOfExpression (ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public FValue eval(Environment e) {
        FValue val = this.exprs.get(0).eval(e);
        String type = val.obj.getClass().getCanonicalName();
        if(val.obj.equals("NULL")){
            type = "NULL";
        }
        return( new FValue(type));
    }
    
}
