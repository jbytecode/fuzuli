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
import java.util.ArrayList;
import java.util.Dictionary;
import java.util.HashMap;

/**
 *
 * @author hako
 */
public class Environment implements Serializable {

    public HashMap<String, FValue> variables;
    public Environment topEnvironment;
    public Environment subEnvironment;

    public Environment(Environment top) {
        this.topEnvironment = top;
        this.variables = new HashMap<String, FValue>();
        if (top==null){
            this.variables.put("NULL", FValue.NULL);
        }
    }

    public FValue getVariableInThisEnvironment(String name) {
        return (this.variables.get(name));
    }

    public FValue findVariable(String name) {
        if(variables.containsKey(name)){
            return(variables.get(name));
        }else if (this.topEnvironment !=null && this.topEnvironment.variables.containsKey(name)){
            return(topEnvironment.variables.get(name));
        }else{
            return(FValue.NULL);
        }
    }

    public void setVariable(String name, FValue val) {
        this.variables.put(name, val);
    }
    
    public String toString(){
        StringBuffer buf = new StringBuffer();
        if (this.topEnvironment!=null){
            buf.append(this.topEnvironment.toString());
        }
        buf.append(this.variables.toString());  
        return(buf.toString());
    }
}

