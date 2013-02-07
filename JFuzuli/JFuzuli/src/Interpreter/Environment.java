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

import java.io.Serializable;
import java.util.HashMap;

/**
 *
 * @author hako
 */
public class Environment implements Serializable {

    public HashMap<String, Object> variables;
    public Environment topEnvironment;
    public Environment subEnvironment;
    public HashMap<String, FunctionExpression> functions;

    public Environment(Environment top) {
        this.topEnvironment = top;
        this.variables = new HashMap<String, Object>();
        this.functions = new HashMap<String, FunctionExpression>();
        if (top==null){
            this.variables.put("NULL", FValue.NULL);
            this.variables.put("true", Boolean.TRUE);
            this.variables.put("false", Boolean.FALSE);
            this.variables.put("NULL", 0);
            this.variables.put("null", null);
        }
    }

    public Object getVariableInThisEnvironment(String name) {
        return (this.variables.get(name));
    }
    
    public void setVariableInThisEnvironment(String name, Object val) {
        this.variables.put(name, val);
    }

    public Environment findEnvironmentOfVariable(String name) {
        if(variables.containsKey(name)){
            return(this);
        }else if (this.topEnvironment !=null){
            return(topEnvironment.findEnvironmentOfVariable(name));
        }else{
            return(null);
        }
    }
    
    

    public void setVariable(String name, Object val) {
        Environment env = findEnvironmentOfVariable(name);
        if(env==null){
            this.variables.put(name, val);
        }else{
            env.setVariableInThisEnvironment(name, val);
        }
    }
    
    public String toString(){
        StringBuilder buf = new StringBuilder();
        if (this.topEnvironment!=null){
            buf.append(this.topEnvironment.toString());
        }
        buf.append(this.variables.toString());  
        return(buf.toString());
    }
    
    public void registerFunction(String name, FunctionExpression f){
        this.functions.put(name, f);
    }
    
     public FunctionExpression findFunction(String name) {
        if(functions.containsKey(name)){
            return(functions.get(name));
        }else if (this.topEnvironment !=null){
            return(topEnvironment.findFunction(name));
        }else{
            return(null);
        }
    }
}

