package org.expr.plang;

import java.util.List;

public class HeadExpression extends Expression {

	Expression expr;
	
	public HeadExpression(Expression expr) {
		this.expr = expr;
	}
	
	@Override
	public Object eval(Environment env) {
		List<Object> list = (List<Object>) this.expr.eval(env);
		return list.get(0);
	}

}
