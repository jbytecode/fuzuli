
package org.expr.plang;


public class EvalExpression extends Expression {

    Expression expressionExpression;
    
    public EvalExpression(Expression expressionExpression){
        this.expressionExpression = expressionExpression;
    }
    
    @Override
    public Object eval(Environment env) {
        Expression expr = (Expression)this.expressionExpression.eval(env);
        return expr.eval(env);
    }
    
}
