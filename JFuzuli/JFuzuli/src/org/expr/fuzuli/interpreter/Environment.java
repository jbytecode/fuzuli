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
import java.util.HashMap;

public final class Environment implements Serializable {

    public final HashMap<String, Object> variables;
    public Environment topEnvironment;
    public Environment subEnvironment;
    public final HashMap<String, FunctionExpression> functions;
    public final HashMap<String, ClassExpression> classes;

    public Environment(Environment top) {
        this.topEnvironment = top;
        this.variables = new HashMap<String, Object>();
        this.functions = new HashMap<String, FunctionExpression>();
        this.classes   = new HashMap<String, ClassExpression>();
        
        if (top == null) {
            this.addConstants();
            this.addInternalFunctions();
        } else {
            top.subEnvironment = this;
        }
    }

    public Object getVariableInThisEnvironment(String name) {
        return (this.variables.get(name));
    }

    public void setVariableInThisEnvironment(String name, Object val) {
        this.variables.put(name, val);
    }

    public Environment findEnvironmentOfVariable(String name) {
        if (variables.containsKey(name)) {
            return (this);
        } else if (this.topEnvironment != null) {
            return (topEnvironment.findEnvironmentOfVariable(name));
        } else {
            return (null);
        }
    }

    public void setVariable(String name, Object val) {
        Environment env = findEnvironmentOfVariable(name);
        if (env == null) {
            this.variables.put(name, val);
        } else {
            env.setVariableInThisEnvironment(name, val);
        }
    }

    public String toString() {
        StringBuilder buf = new StringBuilder();
        if (this.topEnvironment != null) {
            //buf.append(this.topEnvironment.toString());
        }
        buf.append(this.variables.toString());
        return (buf.toString());
    }

    public void registerFunction(String name, FunctionExpression f) {
        this.functions.put(name, f);
    }

    public FunctionExpression findFunction(String name) {
        if (functions.containsKey(name)) {
            return (functions.get(name));
        } else if (this.topEnvironment != null) {
            return (topEnvironment.findFunction(name));
        } else {
            return (null);
        }
    }

    public void registerClass(String name, ClassExpression clz) {
        this.classes.put(name, clz);
    }

    public ClassExpression findClass(String name) {
        if (classes.containsKey(name)) {
            return (classes.get(name));
        } else if (this.topEnvironment != null) {
            return (topEnvironment.findClass(name));
        } else {
            return (null);
        }
    }
    
    private void addConstants(){
        this.variables.put("NULL", FValue.NULL);
            this.variables.put("true", Boolean.TRUE);
            this.variables.put("false", Boolean.FALSE);
            this.variables.put("NULL", 0);
            this.variables.put("null", null);
            this.variables.put("INTEGER", java.lang.Integer.class.getCanonicalName());
            this.variables.put("DOUBLE", java.lang.Double.class.getCanonicalName());
            this.variables.put("FLOAT", java.lang.Float.class.getCanonicalName());
            this.variables.put("SHORT", java.lang.Short.class.getCanonicalName());
            this.variables.put("LONG", java.lang.Long.class.getCanonicalName());
            this.variables.put("BYTE", java.lang.Byte.class.getCanonicalName());
            this.variables.put("BOOLEAN", java.lang.Boolean.class.getCanonicalName());
            this.variables.put("CHAR", java.lang.Character.class.getCanonicalName());
    }
    
    public void addInternalFunctions(){
        this.functions.put("gc", new FunctionInternalExpression(null,"gc",GcExpression.class));
        this.functions.put("dump", new FunctionInternalExpression(null,"dump",DumpExpression.class));
        this.functions.put("jint", new FunctionInternalExpression(null,"jint",JintExpression.class));
        this.functions.put("dotimes", new FunctionInternalExpression(null,"dotimes",DoTimesExpression.class));
        this.functions.put("length", new FunctionInternalExpression(null,"length",LengthExpression.class));
        this.functions.put("typeof", new FunctionInternalExpression(null,"typeof",TypeOfExpression.class));
        this.functions.put("print", new FunctionInternalExpression(null,"print",PrintExpression.class));
        this.functions.put("println", new FunctionInternalExpression(null,"println",PrintlnExpression.class));
        this.functions.put("and", new FunctionInternalExpression(null,"and",AndExpression.class));
        this.functions.put("or", new FunctionInternalExpression(null,"or",OrExpression.class));
        this.functions.put("nth", new FunctionInternalExpression(null,"nth",NthExpression.class));
        this.functions.put("def", new FunctionInternalExpression(null,"def",DefExpression.class));
        this.functions.put("inc", new FunctionInternalExpression(null,"inc",IncExpression.class));
        this.functions.put("dec", new FunctionInternalExpression(null,"dec",DecExpression.class));
        this.functions.put("list", new FunctionInternalExpression(null,"list",ListExpression.class));
        this.functions.put("require", new FunctionInternalExpression(null,"require",RequireExpression.class));
        this.functions.put("foreach", new FunctionInternalExpression(null,"foreach",ForEachExpression.class));
        this.functions.put("return", new FunctionInternalExpression(null,"return",ReturnExpression.class));
        this.functions.put("timing", new FunctionInternalExpression(null,"timing",TimingExpression.class));
        this.functions.put("javastatic", new FunctionInternalExpression(null,"javastatic",JavaStaticExpression.class));
        this.functions.put("javanew", new FunctionInternalExpression(null,"javanew",JavaNewExpression.class));
        this.functions.put("javacall", new FunctionInternalExpression(null,"javacall",JavaCallExpression.class));
        this.functions.put("explode", new FunctionInternalExpression(null,"explode",ExplodeExpression.class));
        this.functions.put("while", new FunctionInternalExpression(null,"while",WhileExpression.class));
        
    }

}
