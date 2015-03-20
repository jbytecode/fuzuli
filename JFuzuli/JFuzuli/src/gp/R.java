package gp;

import org.expr.fuzuli.interpreter.Environment;
import org.expr.fuzuli.interpreter.Expression;
import org.expr.fuzuli.interpreter.Parser;

public class R {
    
    Environment globalEnvironment = null;
    
    public R() {

    }

    public Object run(String code) {
        if(globalEnvironment == null){
            globalEnvironment = new Environment(null);
        }
        Parser parser = new Parser(code+"\n");
        Expression e = null;
        Object o = null;
        
        while (true) {
            try {
                e = parser.getNextExpression();
            } catch (Exception exc) {
                System.out.println("Parsing Error: " + exc.getMessage());
                exc.printStackTrace();
                return(null);
            }

            if (e == null) {
                break;
            }

            
            try {
                o = e.eval(globalEnvironment);
            } catch (Exception exc) {
                System.out.println("Runtime Error: " + exc.toString());
                exc.printStackTrace();
                return(null);
            }
        }
        return(o);
    }
    
    public void setVariable(String name, Object value){
        this.globalEnvironment.setVariable(name, value);
    }
    
    public Object getVariable(String name){
        return(this.globalEnvironment.getVariableInThisEnvironment(name));
    }
    
}
