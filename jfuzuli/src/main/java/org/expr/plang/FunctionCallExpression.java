package org.expr.plang;

import java.util.List;

public class FunctionCallExpression extends Expression{

	String name;
	List<Expression> params;
	
	public FunctionCallExpression(String name, List<Expression> params) {
		this.name = name;
		this.params = params;
	}
	
	
	@Override
	public Object eval(Environment env) {
		FunctionExpression fexp = (FunctionExpression)env.getObject(name);
		return fexp.Call(env, params);
	}
	
	
}
