package gp;

import org.expr.fuzuli.interpreter.AsterixExpression;
import org.expr.fuzuli.interpreter.ConstantNumberExpression;
import org.expr.fuzuli.interpreter.DivisionExpression;
import org.expr.fuzuli.interpreter.Expression;
import org.expr.fuzuli.interpreter.IdentifierExpression;
import org.expr.fuzuli.interpreter.MinusExpression;
import org.expr.fuzuli.interpreter.PlusExpression;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;

public class ExpressionGenerator {

    public ExpressionGenerator() {

    }

    public Expression createRandomExpression(Class[] exprList, String[] identifierList, int deep) {
        Expression result = null;
        ArrayList<Expression> exprParList = new ArrayList<Expression>();
        Expression e1, e2;

        int rand = (int) (Math.random() * exprList.length);
        Class current = exprList[rand];
        
        System.out.println("Deep: "+deep);
        if (deep >5){
            double num = Math.random();
            result = new ConstantNumberExpression(num);
            return(result);
        }
        
        if (current == ConstantNumberExpression.class) {
            double num = Math.random();
            result = new ConstantNumberExpression(num);
        } else if (current == IdentifierExpression.class && (identifierList.length != 0)) {
            int index = (int) (Math.random() * identifierList.length);
            result = new IdentifierExpression(identifierList[index]);
        } else {
            e1 = createRandomExpression(exprList, identifierList, deep+1);
            e2 = createRandomExpression(exprList, identifierList, deep+1);
            exprParList.add(e1);
            exprParList.add(e2);

            if (current == PlusExpression.class) {
                result = new PlusExpression(exprParList);
            } else if (current == MinusExpression.class) {
                result = new PlusExpression(exprParList);
            } else if (current == AsterixExpression.class){
                result = new AsterixExpression(exprParList);
            } else if (current == DivisionExpression.class){
                result = new DivisionExpression(exprParList);
            }
        }

        return (result);
    }
}
