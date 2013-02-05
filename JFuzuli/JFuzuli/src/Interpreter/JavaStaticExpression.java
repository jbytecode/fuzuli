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


public class JavaStaticExpression extends Expression {

    public JavaStaticExpression(ArrayList<Expression>expr){
        this.exprs = expr;
    }
    
    @Override
    public FValue eval(Environment e) {
        String fullmethod = this.exprs.get(0).eval(e).getObject().toString();
        String classname = fullmethod.substring(0,fullmethod.lastIndexOf("."));
        String methodname = fullmethod.substring(fullmethod.lastIndexOf(".")+1);
        int paramscount = this.exprs.size()-1;
        Object result;
        
        Class cls = null;
        try{
            cls = Class.forName(classname);
        }catch (Exception clsex){
            throw new RuntimeException("Can not find class "+classname+": "+clsex.toString());
        }
        
        Method method = findMethod(cls, methodname,paramscount+1);
        Object[] params = new Object[paramscount+1];
        
        for (int i=0;i<paramscount;i++){
            params[i] = this.exprs.get(i+1).eval(e);
        }
        params[paramscount] = e ; /* Passing the environment for all functions */
        
        try{
            result = method.invoke(cls, params);
        }catch (Exception ex){
            throw new RuntimeException("Can not call static method "+classname+"."+methodname+": "+ex.toString());
        }
        
        return(new FValue(result));
    }
    
    public Method findMethod(Class cls, String methodname, int paramscount){
        Method[] m = cls.getMethods();
        for (int i=0;i<m.length;i++){
            if (m[i].getName().equals(methodname) && m[i].getGenericParameterTypes().length == paramscount){
                return(m[i]);
            }
        }
        throw new RuntimeException("Can not find method "+methodname+" in class "+cls.getCanonicalName());
    }
    
}
