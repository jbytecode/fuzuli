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

import static org.expr.fuzuli.interpreter.JavaStaticExpression.convertPrimitiveTypeToClass;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.ArrayList;


public class JavaNewExpression extends Expression {

    public JavaNewExpression(ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public Object eval(Environment e) {
        Object ClassName = this.exprs.get(0).eval(e);
        int paramscount = this.exprs.size() - 1;
        Object result;
        
        Class cls = null;
        
        try{
            if(ClassName instanceof Class){
                cls = (Class)ClassName;
            }else{
                cls = Class.forName(String.valueOf(ClassName));
            }
        }catch (Exception clsex){
            try{
                cls = FuzuliClassLoader.loadClass(String.valueOf(ClassName));
            }catch(Exception e2){
                throw new RuntimeException("javanew: Can not find class " + ClassName + ": " + clsex.toString());
            }
        }
        
        Object[] params = new Object[paramscount];
        
        for (int i = 0; i < paramscount; i++) {
            params[i] = this.exprs.get(i + 1).eval(e);
        }

        Constructor constructor = findConstructor(cls, params);
        
        try {
            result = constructor.newInstance(params);
        } catch (Exception ex) {
            throw new RuntimeException("javanew: Can not create an instant of " + ClassName + ": " + ex.toString());
        }

        return (result);
    }
    
    
     public Constructor findConstructor(Class cls, Object[] params) {
        int paramscount = params.length;
        Constructor[] m = cls.getConstructors();
        for (int i = 0; i < m.length; i++) {
            if (m[i].getGenericParameterTypes().length == paramscount) {
                int allEquals = 0;
                for (int j =0 ; j< paramscount; j++){
                    String type1 = convertPrimitiveTypeToClass( m[i].getParameterTypes()[j].getCanonicalName() );
                    String type2 = convertPrimitiveTypeToClass( params[j].getClass().getCanonicalName() );
                    //System.out.println("* "+m[i]+" "+type1+" "+type2);
                    if(type1.equals(type2)){
                        allEquals++;
                    }
                }
                if (allEquals == paramscount){
                    return (m[i]);
                }
            }
        }
        System.out.println("Alternatives:");
        for (int i=0;i<m.length;i++){
            System.out.println(m[i].toString());
        }
        throw new RuntimeException("javanew: Can not find constructor with "+(paramscount) +" parameters in class " + cls.getCanonicalName());
    }
    
  
    
}
