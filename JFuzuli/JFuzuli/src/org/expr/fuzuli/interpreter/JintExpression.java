
package org.expr.fuzuli.interpreter;

import java.util.ArrayList;

public class JintExpression extends Expression {

    public JintExpression(ArrayList<Expression> exprs){
        this.exprs = exprs;
    }
    
    @Override
    public Object eval(Environment e) {
        Number n = (Number)this.exprs.get(0).eval(e);
        return n.intValue(); 
    }
    
}
