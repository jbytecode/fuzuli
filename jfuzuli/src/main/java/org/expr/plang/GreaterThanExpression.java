package org.expr.plang;

public class GreaterThanExpression extends Expression {

	private Expression left, right;
	
	public GreaterThanExpression (Expression left, Expression right) {
		this.left = left;
		this.right = right;
	}
	
	@Override
	public Object eval(Environment env) {
		Number n1 = (Number)left.eval(env);
		Number n2 = (Number)right.eval(env);
		int compare =  Double.compare(n1.doubleValue(), n2.doubleValue());
		return compare == 1;
	}

    @Override
    public String emitJS() {
        return left.emitJS() + " > " + right.emitJS();
    }
        
        

}
