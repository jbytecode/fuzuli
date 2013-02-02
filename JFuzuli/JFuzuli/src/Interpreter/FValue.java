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

/**
 *
 * @author hako
 */
public class FValue {
    
    static FValue ZERO = new FValue(0);
    Object obj = null;
    
    public FValue(int i){
        obj = new Integer(i);
    }
    
    public FValue (double d){
        obj = new Double(d);
    }
    
    public FValue (Object o){
        obj = o;
    }
    
    public Object getObject(){
        return(obj);
    }
    
    public double getAsDouble(){
        if (obj instanceof Number){
            Number n = (Number) obj;
            return (n.doubleValue());
        }else{
            throw new RuntimeException(obj+" is not a number");
        }
    }
}
