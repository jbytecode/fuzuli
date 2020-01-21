package org.expr.plang;

import java.util.ArrayList;
import java.util.List;

public class PrependExpression extends Expression {

    Expression exprList;
    Expression exprElement;

    public PrependExpression(Expression exprList, Expression exprElement) {
        this.exprList = exprList;
        this.exprElement = exprElement;
    }

    @Override
    public Object eval(Environment env) {
        List list = (List) this.exprList.eval(env);
        List newList = new ArrayList(list);
        newList.add(0, this.exprElement.eval(env));
        return newList;
    }

    @Override
    public String emitJS() {
        StringBuffer s = new StringBuffer();
        s.append("(");
        s.append("function(){");
        s.append("var newarr = " + exprList.emitJS() + ".slice();");
        s.append("newarr.unshift(" + exprElement.emitJS() + ");");
        s.append("return newarr;");
        s.append("}");
        s.append(")()");
        return s.toString();
    }

}
