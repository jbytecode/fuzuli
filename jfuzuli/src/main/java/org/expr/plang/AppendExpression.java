package org.expr.plang;

import java.util.ArrayList;
import java.util.List;

public class AppendExpression extends Expression {

	Expression exprList;
        Expression exprElement;
	
	public AppendExpression(Expression exprList, Expression exprElement) {
            this.exprList = exprList;
            this.exprElement = exprElement;
	}
	
	@Override
	public Object eval(Environment env) {
		List list = (List) this.exprList.eval(env);
		List newList = new ArrayList(list);
                newList.add(this.exprElement.eval(env));
                return newList;
	}

    @Override
    public String emitJS() {
        StringBuilder sb = new StringBuilder();
        sb.append(exprList.emitJS());
        sb.append(".concat(");
        sb.append(exprElement.emitJS());
        sb.append(")");
        return sb.toString();
    }
        
        

}
