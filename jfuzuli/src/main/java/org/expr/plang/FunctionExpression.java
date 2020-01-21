package org.expr.plang;

import java.util.List;
import java.util.function.BiConsumer;

public class FunctionExpression extends Expression {

	Expression params;
	Expression body;
	Environment functionEnvironment;
	
	public FunctionExpression(Expression params, Expression body) {
		this.params = params;
		this.body = body;
		this.functionEnvironment = new Environment();
	}
	
	@Override
	public Object eval(Environment env) {
		return this;
	}

	@Override
	public String toString() {
		return "Function of " + params.toString() + " with body " + body.toString();
	}
	
	public Object Call(Environment env, List<Expression> values) {
		functionEnvironment.objects.putAll(env.objects);
		
		ListExpression gparams = (ListExpression)params;
		for (int i = 0; i < gparams.getExpressionList().size(); i++) {
			IdentifierExpression ide = (IdentifierExpression)gparams.getExpressionList().get(i);
			functionEnvironment.setObject(ide.getId(), values.get(i).eval(env));
		}
		if (body instanceof FunctionExpression) {
			((FunctionExpression)body).functionEnvironment.getObjectMappings().putAll(functionEnvironment.getObjectMappings());
		}
		return body.eval(functionEnvironment);
	}
	
	public Object CallValue(Environment env, List<Object> values) {
		functionEnvironment.objects.putAll(env.objects);
		
		ListExpression gparams = (ListExpression)params;
		for (int i = 0; i < gparams.getExpressionList().size(); i++) {
			IdentifierExpression ide = (IdentifierExpression)gparams.getExpressionList().get(i);
			functionEnvironment.setObject(ide.getId(), values.get(i));
		}
		return body.eval(functionEnvironment);
	}
	
	
}
