package org.expr.plang;

public class BooleanConstantExpression extends Expression{

	boolean boolvalue;
	
	public BooleanConstantExpression(boolean boolValue) {
		this.boolvalue = boolValue;
	}
	
	@Override
	public Object eval(Environment env) {
		return this.boolvalue;
	}

}
