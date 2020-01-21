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

    @Override
    public String emitJS() {
        ListExpression lparams = (ListExpression)this.params;
        StringBuilder s = new StringBuilder();
        s.append("function(");
        for (int i = 0; i < lparams.exprs.size(); i++){
            IdentifierExpression id = (IdentifierExpression) lparams.exprs.get(i);
            s.append(id.getId());
            if(i < lparams.exprs.size() - 1){
                s.append(", ");
            }
        }
        s.append(") {");
        s.append("var fres = " + this.body.emitJS());
        s.append(";");
        s.append("return fres;");
        s.append("}");
        
        return s.toString();
    }
        
        
	
	
}
