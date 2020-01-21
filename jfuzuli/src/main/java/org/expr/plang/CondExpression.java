package org.expr.plang;

import java.util.List;

public class CondExpression extends Expression {

    private List<Expression> exprs;

    public CondExpression(List<Expression> exprs) {
        this.exprs = exprs;
    }

    @Override
    public Object eval(Environment env) {
        Object boolresult = null;
        for (int i = 0; i < this.exprs.size(); i++) {
            ListExpression ge = (ListExpression) this.exprs.get(i);
            Expression cond = ge.getExpressionList().get(0);
            Object result = cond.eval(env);
            if (((Boolean) result).booleanValue()) {
                return ge.getExpressionList().get(1).eval(env);
            }
        }
        return null;
    }

    @Override
    public String toString() {
        StringBuffer s = new StringBuffer();
        for (int i = 0; i < this.exprs.size(); i++) {
            s.append(this.exprs.get(i).toString());
        }
        return s.toString();
    }

    @Override
    public String emitJS() {
        StringBuilder s = new StringBuilder();
        for (int i = 0; i < this.exprs.size(); i++) {
            ListExpression ge = (ListExpression) this.exprs.get(i);
            Expression cond = ge.getExpressionList().get(0);
            Expression then = ge.getExpressionList().get(1);
            s.append(cond.emitJS());
            s.append(" ? ");
            s.append(then.emitJS());
            s.append(" : ");
            if(i == this.exprs.size() - 1){
                s.append("null");
                break;
            }            
        }
        return s.toString();
    }

}
