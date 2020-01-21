package org.expr.plang;

import java.util.List;
import java.util.ArrayList;

public class ListExpression extends Expression {

	List<Expression> exprs;
	
	public ListExpression(List<Expression> exprs) {
		this.exprs = exprs;
	}
	
	public List<Expression> getExpressionList(){
		return this.exprs;
	}
	
	
	@Override
	public Object eval(Environment env) {
		List<Object> list = new ArrayList<>();
		for (int i = 0; i < exprs.size(); i++) {
			list.add(this.exprs.get(i).eval(env));
		}
		return list;
	}
	
	@Override
	public String toString() {
		StringBuilder s = new StringBuilder();
		s.append("list[");
		for (int i = 0; i < exprs.size(); i++) {
			s.append(this.exprs.get(i).toString());
			s.append(" ");
		}
		s.append("]");
		return s.toString();
	}

    @Override
    public String emitJS() {
        StringBuilder s = new StringBuilder();
        s.append("[");
        for (int i = 0; i < this.exprs.size(); i++){
            s.append(this.exprs.get(i).emitJS());
            if(i < this.exprs.size() - 1){
                s.append(", ");
            }
        }
        s.append("]");
        return s.toString();
    }
        
        
	
}
