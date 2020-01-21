
package org.expr.plang;


public class ExpressionExpression extends Expression {

    private Expression body;
    
    public ExpressionExpression(Expression body){
        this.body = body;
    }

    public Expression getBody() {
        return body;
    }

    public void setBody(Expression body) {
        this.body = body;
    }
    
    
    
    @Override
    public Object eval(Environment env) {
        return this.body;
    }
    
}
