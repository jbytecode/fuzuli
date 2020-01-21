package org.expr.plang;

public class IfElseExpression extends Expression {

    private Expression condition, ifTrue, ifNotTrue;

    public IfElseExpression(Expression condition, Expression ifTrue, Expression ifNotTrue) {
        this.condition = condition;
        this.ifTrue = ifTrue;
        this.ifNotTrue = ifNotTrue;
    }

    @Override
    public Object eval(Environment env) {
        Object cond = this.condition.eval(env);
        if (!(cond instanceof java.lang.Boolean)) {
            throw new RuntimeException("ifelse condition should return boolean");
        }
        if ((Boolean) cond) {
            return this.ifTrue.eval(env);
        } else {
            return this.ifNotTrue.eval(env);
        }
    }

    @Override
    public String emitJS() {
        return this.condition.emitJS() + " ? " + this.ifTrue.emitJS() + " : " + this.ifNotTrue.emitJS();
    }

}
