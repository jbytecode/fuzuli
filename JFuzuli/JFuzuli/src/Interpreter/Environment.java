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

import java.util.ArrayList;
import java.util.Dictionary;
import java.util.HashMap;

/**
 *
 * @author hako
 */
public class Environment {

    public HashMap<String, FValue> variables;
    public Environment topEnvironment;
    public Environment subEnvironment;

    public Environment(Environment top) {
        this.topEnvironment = top;
        this.variables = new HashMap<String, FValue>();
    }

    public FValue getVariableInThisEnvironment(String name) {
        return (this.variables.get(name));
    }

    public FValue findVariable(String name) {
        if(variables.containsKey(name)){
            return(variables.get(name));
        }else{
            System.out.println("ooppps findvariable cannot find "+name);
            return null;
        }
    }

    public void setVariable(String name, FValue val) {
        this.variables.put(name, val);
    }
}

