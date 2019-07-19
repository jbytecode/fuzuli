package org.expr.plang;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class ApplyExpression extends Expression{

	Expression func;
	Expression vals;
	
	public ApplyExpression(Expression func, Expression vals) {
		this.func = func;
		this.vals = vals;
	}
	
	@Override
	public Object eval(Environment env) {
		FunctionExpression funcExpr = (FunctionExpression)func.eval(env);
		Iterable<Object> iterable = (Iterable<Object>)vals.eval(env);
		List<Object> resultList = new ArrayList<Object>();
		iterable.forEach(new Consumer<Object>() {
			@Override
			public void accept(Object t) {
				List<Object> nextParams = List.of(t);
				Object result = funcExpr.CallValue(env, nextParams);
				resultList.add(result);
			}
		});
		return resultList;
	}

}
