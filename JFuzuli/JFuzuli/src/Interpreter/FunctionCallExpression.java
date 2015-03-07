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


public class FunctionCallExpression extends Expression{

    String fname;
    
    public FunctionCallExpression(ArrayList<Expression>expr){
        this.exprs = expr;
    }
    
    
    public Object evalClass(Environment e) {
        String ObjectName = fname.substring(0, fname.indexOf('.'));
        String FunctionName = fname.substring(fname.indexOf('.')+1);
        Environment e1 = e.findEnvironmentOfVariable(ObjectName);
        Environment object_env = (Environment)e1.getVariableInThisEnvironment(ObjectName);
        Environment functEnv = new Environment(object_env);
        
        
        int size;
        
        Object returnval = null, val = null;
        
        FunctionExpression func = object_env.findFunction(FunctionName);
        if(func == null){
            throw new RuntimeException("Fuzuli function '"+FunctionName+ "' is not defined in object "+ObjectName);
        }
        
        size = exprs.size();
        for (int i=0;i<size;i++){
            functEnv.setVariableInThisEnvironment(func.params.get(i), this.exprs.get(i).eval(e));
        }
        
        size=func.body.size();
        for (int i=0;i<size;i++){
            val = func.body.get(i).eval(functEnv);
            //System.out.println("In Function, object is "+val.getObject().getClass().getCanonicalName());
            if(val instanceof ReturnExpression ){
                ReturnExpression re =  (ReturnExpression)(val);
                returnval = re.returnvalue;
                break;
            }
        }
        return(returnval);
        
    }
    
    @Override
    public Object eval(Environment e) {
        if(fname.contains(".")){
            return evalClass(e);
        }
        Environment env = new Environment(e);
        env.variables.clear();
        int size;
        
        Object returnval = null, val = null;
        
        FunctionExpression func = env.findFunction(fname);
        
        if(func == null){
            throw new RuntimeException("Fuzuli function '"+fname+ "' is not defined");
        }
        
        size = exprs.size();
        for (int i=0;i<size;i++){
            env.setVariableInThisEnvironment(func.params.get(i), this.exprs.get(i).eval(env));
        }
        
        size=func.body.size();
        for (int i=0;i<size;i++){
            val = func.body.get(i).eval(env);
            //System.out.println("In Function, object is "+val.getObject().getClass().getCanonicalName());
            if(val instanceof ReturnExpression ){
                ReturnExpression re =  (ReturnExpression)(val);
                returnval = re.returnvalue;
                break;
            }
        }
        return(returnval);
        
    }
    
    public Object EvalWithoutName(FunctionExpression funct, Environment e){
        Environment env = new Environment(e);
        env.variables.clear();
        int size;
        
        Object returnval = null, val = null;
        
        FunctionExpression func = funct;
        
        if(func == null){
            throw new RuntimeException("Fuzuli function '"+fname+ "' is not defined");
        }
        
        size = exprs.size();
        for (int i=0;i<size;i++){
            env.setVariableInThisEnvironment(func.params.get(i), this.exprs.get(i).eval(env));
        }
        
        size=func.body.size();
        for (int i=0;i<size;i++){
            val = func.body.get(i).eval(env);
            //System.out.println("In Function, object is "+val.getObject().getClass().getCanonicalName());
            if(val instanceof ReturnExpression ){
                ReturnExpression re =  (ReturnExpression)(val);
                returnval = re.returnvalue;
                break;
            }
        }
        return(returnval);
        
    }
    
    public static Object doFunctionCall(String name, ArrayList<Object> params, Environment e) {
        Environment env = new Environment(e);
        env.variables.clear();
        int size;
        
        Object returnval = null, val = null;
        
        FunctionExpression func = env.findFunction(name);
        
        if(func == null){
            throw new RuntimeException("Fuzuli function '"+name+ "' is not defined");
        }
        
        size = params.size();
        for (int i=0;i<size;i++){
            e.setVariableInThisEnvironment(func.params.get(i), params.get(i));
        }
        
        size=func.body.size();
        for (int i=0;i<size;i++){
            val = func.body.get(i).eval(env);
            //System.out.println("In Function, object is "+val.getObject().getClass().getCanonicalName());
            if(val instanceof ReturnExpression ){
                ReturnExpression re =  (ReturnExpression)(val);
                returnval = re.returnvalue;
                break;
            }
        }
        return(returnval);
        
    }
    
}
