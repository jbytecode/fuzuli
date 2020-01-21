package org.expr.plang;

public class DoubleConstantExpression extends Expression{

	private double doublevalue;
	
	public DoubleConstantExpression(double numeric) {
		this.doublevalue = numeric;
	}
	
	@Override
	public Object eval(Environment env) {
		return this.doublevalue;
	}
	
	@Override
	public String toString() {
		return String.valueOf(this.doublevalue);
	}

}
