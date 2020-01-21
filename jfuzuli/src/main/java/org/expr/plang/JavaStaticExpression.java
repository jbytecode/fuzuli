package org.expr.plang;

import java.lang.reflect.Method;
import java.util.List;

public class JavaStaticExpression extends Expression {

    Expression nameExpr;
    Expression params;

    public JavaStaticExpression(Expression nameExpr, Expression params) {
        this.nameExpr = nameExpr;
        this.params = params;
    }

    Method findMethod(Method[] methods, String name, int paramcount) {
        for (int i = 0; i < methods.length; i++) {
            Method method = methods[i];
            if (method.getName().equals(name) && method.getParameterCount() == paramcount) {
                return method;
            }
        }
        return null;
    }

    @Override
    public Object eval(Environment env) {
        String name = (String) nameExpr.eval(env);
        int lastPoint = name.lastIndexOf(".");
        String className = name.substring(0, lastPoint);
        String methodName = name.substring(lastPoint + 1);

        List<Object> paramObjs = (List<Object>) params.eval(env);
        Object[] paramObjsArray = new Object[paramObjs.size()];
        for (int i = 0; i < paramObjsArray.length; i++) {
            paramObjsArray[i] = paramObjs.get(i);
        }
        Object result = null;

        try {
            Class clz = Class.forName(className);
            Method[] methods = clz.getDeclaredMethods();
            Method currentMethod = findMethod(methods, methodName, paramObjs.size());
            result = currentMethod.invoke(this, paramObjs.toArray());
        } catch (Exception e) {
            throw new RuntimeException(e.toString());
        }
        return result;
    }

}
