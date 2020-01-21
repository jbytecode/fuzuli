package org.expr.plang;

import java.util.ArrayList;
import java.util.List;

public class RangeExpression extends Expression {

    private Expression left, right;

    public RangeExpression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
    }

    @Override
    public Object eval(Environment env) {
        Integer val1 = (Integer) left.eval(env);
        Integer val2 = (Integer) right.eval(env);
        List<Integer> list = new ArrayList<>();
        for (int i = val1; i <= val2; i++) {
            list.add(i);
        }
        return list;
    }

    @Override
    public String emitJS() {
        StringBuilder s = new StringBuilder();
        s.append("(");
        s.append("function(){");
        s.append("var arr = [];");
        s.append("for (var i = " + left.emitJS() + "; i <= " + right.emitJS() + "; i++){");
        s.append("arr.push(i);");
        s.append("}");
        s.append("return arr;");
        s.append("}");
        s.append(")()");
        return s.toString();
    }

}
