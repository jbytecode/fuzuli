package org.expr.plang;

public class EqualExpression extends Expression {

    private Expression left, right;

    public EqualExpression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
    }

    @Override
    public Object eval(Environment env) {
        Number n1 = (Number) left.eval(env);
        Number n2 = (Number) right.eval(env);
        int compare = Double.compare(n1.doubleValue(), n2.doubleValue());
        return compare == 0;
    }

    @Override
    public String toString() {
        return "(= " + this.left.toString() + " " + this.right.toString() + ")";
    }

    @Override
    public String emitJS() {
        return left.emitJS() + " == " + right.emitJS();
    }
}
