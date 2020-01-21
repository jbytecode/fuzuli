package org.expr.plang;

public class AssertExpression extends Expression {

	Expression expr;
	
	public AssertExpression(Expression expr) {
		this.expr = expr;
	}

	@Override
	public Object eval(Environment env) {
		Boolean objBool = (Boolean)this.expr.eval(env);
		if(objBool) {
			return true;
		}else {
			throw new RuntimeException("Assertation error: " + this.expr.toString() + " is not true.");
		}
	}
	
	
}
