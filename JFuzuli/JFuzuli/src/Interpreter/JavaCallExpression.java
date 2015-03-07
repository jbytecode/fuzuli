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

package Interpreter;

import java.lang.reflect.Method;
import java.util.ArrayList;

public class JavaCallExpression extends Expression{

    public JavaCallExpression (ArrayList<Expression> exprs){
        this.exprs = exprs;
    }
    
    @Override
    public Object eval(Environment e) {
        Object obj = this.exprs.get(0).eval(e);
        String methodname = this.exprs.get(1).eval(e).toString();
        int paramscount = this.exprs.size()-2;
        Object result;
        
        Object[] params = new Object[paramscount];
        for (int i=0;i<params.length;i++){
            params[i] = this.exprs.get(i+2).eval(e);
        }
        
        Method m = findMethod(obj, methodname, params);
        
        try{ 
            result = m.invoke(obj, params);
        }catch (Exception ex){
            throw new RuntimeException("javacall: Method "+methodname+" can not be called: "+ex.toString());
        }
        return(result);
    }
    
    public Method findMethod(Object o, String methodname, Object[] params) {
        int paramscount = params.length;
        Method[] m = o.getClass().getMethods();
        Method lucky = null;
        for (int i = 0; i < m.length; i++) {
            if (m[i].getName().equals(methodname) && m[i].getGenericParameterTypes().length == paramscount) {
                int allEquals = 0;
                lucky = m[i];
                for (int j =0 ; j< paramscount; j++){
                    if(areRelated(m[i].getParameterTypes()[j].getSuperclass(), getObjectClass(params[j]))){
                        allEquals++;
                    }
                    
                }
                if (allEquals == paramscount){
                    return (m[i]);
                }
            }
        }
        //System.out.println("* Selected "+lucky+ " as lucky" );
        return lucky;
        //throw new RuntimeException("javacall: Can not find method " + methodname +" with "+(paramscount) +" parameters in class " + o.getClass().getCanonicalName());
    }
    
    public static boolean areRelated(Class c1, Class c2){
        if(c1==null || c2==null){
            return true;
        }
        try{
            c1.asSubclass(c2);
        }catch (Exception e1){
            
            try{
                c2.asSubclass(c1);
            }catch (Exception e2){
                return(false);
            }
        }
        return(true);
    }
    
    
    public static Class getObjectClass(Object o){
        if (o == null){
            return null;
        }else{
            return o.getClass();
        }
    }
}
