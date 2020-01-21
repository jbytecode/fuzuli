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

    @Override
    public String emitJS() {
        StringBuilder s = new StringBuilder();
        s.append(name);
        s.append("(");
        for (int i = 0; i < this.params.size(); i++){
            s.append(this.params.get(i).emitJS());
            if(i < this.params.size() - 1){
                s.append(", ");
            }
        }
        s.append(")");
        return s.toString();
    }
        
        
	
	
}
