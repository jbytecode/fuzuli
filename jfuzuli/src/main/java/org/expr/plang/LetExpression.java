package org.expr.plang;

public class LetExpression extends Expression {

    private Expression left, right;

    public LetExpression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
    }

    @Override
    public Object eval(Environment env) {
        throw new UnsupportedOperationException("Let");
    }

    @Override
    public String toString() {
        IdentifierExpression ie = (IdentifierExpression) this.left;
        String name = ie.getId();
        return "Let(" + name + "," + right.toString() + ")";
    }

    @Override
    public String emitJS() {
        String name = left.emitJS();
        return name + " = " + this.right.emitJS() + ";";
    }

}
