
package org.expr.fuzuli.interpreter;

import java.util.ArrayList;


public class TypeOfExpression extends Expression {

    public TypeOfExpression (ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public Object eval(Environment e) {
        Object val = null;
        try{
            val = this.exprs.get(0).eval(e);
        }catch (Exception ex){
            return (FValue.ZERO);
        }
        String type = val.getClass().getCanonicalName();
        return( type);
    }
    
}
