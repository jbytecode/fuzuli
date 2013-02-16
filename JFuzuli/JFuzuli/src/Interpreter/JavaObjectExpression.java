
package Interpreter;

import java.util.ArrayList;


public class JavaObjectExpression extends Expression {

    Object o;
    
    public JavaObjectExpression(ArrayList<Expression> exprs){
        this.exprs = exprs;
    }
    
    public JavaObjectExpression(Object o){
        this.o = o;
    }
    
    @Override
    public Object eval(Environment e) {
        return(this.o);
    }
    
}
