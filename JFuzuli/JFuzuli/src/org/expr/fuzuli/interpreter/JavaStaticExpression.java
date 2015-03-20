/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2013 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package org.expr.fuzuli.interpreter;

import java.lang.reflect.Method;
import java.util.ArrayList;

public class JavaStaticExpression extends Expression {

    public JavaStaticExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment e) {
        String fullmethod = this.exprs.get(0).eval(e).toString();
        String classname = fullmethod.substring(0, fullmethod.lastIndexOf("."));
        String methodname = fullmethod.substring(fullmethod.lastIndexOf(".") + 1);
        int paramscount = this.exprs.size() - 1;
        Object result;

        Class cls = null;
        try {
            cls = Class.forName(classname);
        } catch (Exception clsex) {
            throw new RuntimeException("Can not find class " + classname + ": " + clsex.toString());
        }

        Object[] params = new Object[paramscount];
        
        for (int i = 0; i < paramscount; i++) {
            params[i] = this.exprs.get(i + 1).eval(e);
        }

        Method method = findMethod(cls, methodname, params);

        try {
            result = method.invoke(cls, params);
        } catch (Exception ex) {
            throw new RuntimeException("javastatic: Can not call static method " + classname + "." + methodname + ": " + ex.toString());
        }

        return (result);
    }

    public Method findMethod(Class cls, String methodname, Object[] params) {
        int paramscount = params.length;
        Method[] m = cls.getMethods();
        for (int i = 0; i < m.length; i++) {
            if (m[i].getName().equals(methodname) && m[i].getGenericParameterTypes().length == paramscount) {
                int allEquals = 0;
                for (int j =0 ; j< paramscount; j++){
                    String type1 = convertPrimitiveTypeToClass( m[i].getParameterTypes()[j].getCanonicalName() );
                    String type2 = convertPrimitiveTypeToClass( params[j].getClass().getCanonicalName() );
                    if(type1.equals(type2)){
                        allEquals++;
                    }
                }
                if (allEquals == paramscount){
                    return (m[i]);
                }
            }
        }
        throw new RuntimeException("javastatic: Can not find method " + methodname +" with "+(paramscount) +" parameters in class " + cls.getCanonicalName());
    }
    
    public static String convertPrimitiveTypeToClass (String type){
        if (type.equals("int")){
            return (Integer.class.getCanonicalName());
        }else if (type.equals("long")){
            return(Long.class.getCanonicalName());
        }else if (type.equals("float")){
            return(Float.class.getCanonicalName());
        }else if (type.equals("double")){
            return(Double.class.getCanonicalName());
        }else if (type.equals("byte")){
            return(Byte.class.getCanonicalName());
        }else if (type.equals("short")){
            return(Short.class.getCanonicalName());
        }else if  (type.equals("boolean")){
            return(Boolean.class.getCanonicalName());
        }else if (type.equals("char")){
            return(Character.class.getCanonicalName());
        }else{
            return(type);
        }
    }
    
    
}
