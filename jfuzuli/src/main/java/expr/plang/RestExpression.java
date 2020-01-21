package org.expr.plang;

import java.util.List;
import java.util.ArrayList;

public class RestExpression extends Expression {

	Expression expr;
	
	public RestExpression(Expression expr) {
		this.expr = expr;
	}
	
	@Override
	public Object eval(Environment env) {
		List<Object> list = (List<Object>) this.expr.eval(env);
		List<Object> result = new ArrayList<>();
		result.addAll(list);
		result.remove(0);
		return result;
	}

}
