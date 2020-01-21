package org.expr.plang;

import java.util.List;

public class LenExpression extends Expression {

	Expression expr;
	
	public LenExpression(Expression expr) {
		this.expr = expr;
	}
	
	@Override
	public Object eval(Environment env) {
		List list = (List) this.expr.eval(env);
		return list.size();
	}

}
