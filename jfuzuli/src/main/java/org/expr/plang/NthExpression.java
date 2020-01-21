package org.expr.plang;

import java.util.Iterator;
import java.util.List;

public class NthExpression extends Expression {

	Expression expr;
	Expression nexpr;
	
	public NthExpression(Expression expr, Expression n) {
		this.expr = expr;
		this.nexpr = n;
	}
	
	
	@Override
	public Object eval(Environment env) {
		Iterable<Object> it= (Iterable<Object>)this.expr.eval(env);
		Iterator<Object> iterator = it.iterator();
		Number number = (Number) nexpr.eval(env);
		Object result = null;
		int index = number.intValue();
		for(int i = 0; i < Integer.MAX_VALUE; i++) {
			result = iterator.next();
			if(i == index) {
				break;
			}
		}
		return result;
		
	}

}
