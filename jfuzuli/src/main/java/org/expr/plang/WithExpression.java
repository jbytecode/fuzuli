package org.expr.plang;

public class WithExpression extends Expression {

    private Expression left, right;

    public WithExpression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
    }

    @Override
    public Object eval(Environment env) {
        throw new UnsupportedOperationException("With");
    }

    @Override
    public String toString() {
        IdentifierExpression ie = (IdentifierExpression) this.left;
        String name = ie.getId();
        return "With(" + name + "," + right.toString() + ")";
    }

    @Override
    public String emitJS() {
        IdentifierExpression ie = (IdentifierExpression) this.left;
        String name = ie.getId();
        return name + "." + this.right.emitJS();
    }

}
