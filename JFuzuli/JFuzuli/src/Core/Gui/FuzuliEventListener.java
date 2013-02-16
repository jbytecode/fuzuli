
package Core.Gui;

import Interpreter.Environment;
import java.awt.Event;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import Interpreter.FunctionCallExpression;
import Interpreter.FunctionExpression;
import java.util.ArrayList;
import java.util.EventObject;

public class FuzuliEventListener implements 
        ActionListener {

    FunctionExpression func = null;
    FunctionCallExpression fcall = null;
    Environment envir;
    ArrayList params;
    
    public FuzuliEventListener(FunctionExpression func, Environment env){
        this.envir = env;
        this.func = func;
        params = new ArrayList();
    }
    
    public void FunctionCall(EventObject evt){
        params.clear();
        params.add(evt);
        fcall = new FunctionCallExpression(params);
        fcall.EvalWithoutName(func, envir);
    }
    
    @Override
    public void actionPerformed(ActionEvent ae) {
        FunctionCall(ae);
    }
    
}
