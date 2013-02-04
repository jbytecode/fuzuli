
package Interpreter;

import java.util.ArrayList;


public class TypeOfExpression extends Expression {

    public TypeOfExpression (ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public FValue eval(Environment e) {
        FValue val = null;
        try{
            val = this.exprs.get(0).eval(e);
        }catch (Exception ex){
            return (FValue.ZERO);
        }
        String type = val.obj.getClass().getCanonicalName();
        return( new FValue(type));
    }
    
}
