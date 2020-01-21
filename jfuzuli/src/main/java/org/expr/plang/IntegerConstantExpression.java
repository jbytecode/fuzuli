package org.expr.plang;

public class IntegerConstantExpression extends Expression{

	private int intvalue;
	
	public IntegerConstantExpression(int numeric) {
		this.intvalue = numeric;
	}
	
	@Override
	public Object eval(Environment env) {
		return this.intvalue;
	}
	
	@Override
	public String toString() {
		return String.valueOf(this.intvalue);
	}

}
