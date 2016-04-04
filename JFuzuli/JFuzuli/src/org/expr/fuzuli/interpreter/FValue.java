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

import java.io.Serializable;

/**
 *
 * @author hako
 */
public class FValue implements Serializable {
    
    static Object ZERO = 0.0;
    static Object NaN = Double.NaN;
    static Object NULL = "NULL";
    static Object NOTSET = "NOTSET";
    
    Object obj = null;
    
   
    
    
    public static double getAsDouble(Object obj){
        if (obj instanceof Number){
            return(((Number)obj).doubleValue());
        }else {
            try{
                return (Double.parseDouble(String.valueOf(obj)));
            }catch (Exception e){
                throw new RuntimeException(obj+" can not convert to number");    
            }
        }
    }
    
    public static boolean Equals (Object f1, Object f2){
        
        if(f1 instanceof Number && f2 instanceof Number){
            Number n1 = (Number)f1;
            Number n2 = (Number)f2;
            return (n1.doubleValue() == n2.doubleValue());
        }else if (f1 instanceof String && f2  instanceof String){
            String s1 = (String)f1;
            String s2 = (String)f2;
            return (s1.equals(s2.toString()));
        } else if (f1 instanceof Boolean && f2 instanceof Boolean){
            Boolean b1 = (Boolean) f1;
            Boolean b2 = (Boolean) f2;
            return (b1.booleanValue() == b2.booleanValue());
        }else {
            return ( String.valueOf(f2).equals(String.valueOf(f1)));
        }
    }

    public String toString(){
        return(this.obj.toString());
    }
    
}
