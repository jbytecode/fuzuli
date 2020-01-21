package org.expr.plang;

public class DefExpression extends Expression {

	private Expression left, right;
	
	public DefExpression(Expression left, Expression right) {
		this.left = left;
		this.right = right;
	}
	
	@Override
	public Object eval(Environment env) {
		IdentifierExpression ie = (IdentifierExpression) this.left;
		String name = ie.getId();
		Object val = right.eval(env);
		env.setObject(name, val);
		return val;
	}
	
	@Override
	public String toString() {
		IdentifierExpression ie = (IdentifierExpression) this.left;
		String name = ie.getId();
		return "Let(" + name + "," + right.toString() + ")";
	}

}
