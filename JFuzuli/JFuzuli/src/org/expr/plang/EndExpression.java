package org.expr.plang;

public class EndExpression extends Expression{

	public EndExpression() {
		
	}
	
	@Override
	public Object eval(Environment env) {
		return "End of Expression";
	}

}
