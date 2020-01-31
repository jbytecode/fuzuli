package org.expr.plang;

import java.util.List;

public class PrintlnExpression extends Expression {

    List<Expression> expr;

    public PrintlnExpression(List<Expression> expr) {
        this.expr = expr;
    }

    @Override
    public Object eval(Environment env) {
        Object result = null;
        for (int i = 0; i < expr.size(); i++) {
            result = this.expr.get(i).eval(env);
            System.out.println(result);
        }
        return result;
    }

    @Override
    public String emitJS() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < expr.size(); i++) {
            sb.append("console.log(" + expr.get(i).emitJS() + ");");
        }
        return sb.toString();
    }

}
