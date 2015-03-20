
package org.expr.fuzuli.compiler;

import org.expr.fuzuli.interpreter.Environment;
import org.expr.fuzuli.interpreter.Expression;
import java.io.Serializable;
import java.util.ArrayList;


public class FuzuliScheme implements Serializable {
    
    public ArrayList<Expression> expr;
    public Environment globalEnvir;
    
    public void reset(){
        expr = new ArrayList<Expression>();
        globalEnvir = new Environment(null);
    }
    
    public FuzuliScheme(){
        
    }
    
    public FuzuliScheme ( String[] args){
    
    }
    
    public void run(){
        for (int i=0;i<expr.size();i++){
            expr.get(i).eval(globalEnvir);
        }
    }
    
    public static void main(String[] args){
        new FuzuliScheme(args);
    }
}
