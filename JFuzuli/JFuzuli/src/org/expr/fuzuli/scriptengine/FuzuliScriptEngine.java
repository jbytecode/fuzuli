package org.expr.fuzuli.scriptengine;

import java.io.Reader;
import java.util.ArrayList;
import javax.script.Bindings;
import javax.script.ScriptContext;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineFactory;
import javax.script.ScriptException;
import org.expr.fuzuli.interpreter.Environment;
import org.expr.fuzuli.interpreter.Expression;
import org.expr.fuzuli.interpreter.Parser;

public class FuzuliScriptEngine implements ScriptEngine {

    Environment env = new Environment(null);
    Parser parser = new Parser("\n\n");
    
    @Override
    public Object eval(String code, ScriptContext sc) throws ScriptException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Object eval(Reader reader, ScriptContext sc) throws ScriptException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Object eval(String code) throws ScriptException {
        parser.setSourceCode(code+"\n");
        parser.resetParser();
        Object result = null;
        ArrayList<Expression> exprs = parser.getExpressionList();
        for (Expression ex : exprs){
            result = ex.eval(env);
        }
        return(result);
    }

    @Override
    public Object eval(Reader reader) throws ScriptException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Object eval(String string, Bindings bndngs) throws ScriptException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Object eval(Reader reader, Bindings bndngs) throws ScriptException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void put(String name, Object o) {
        this.env.setVariable(name, o);
    }

    @Override
    public Object get(String name) {
        return(this.env.getVariableInThisEnvironment(name));
    }

    @Override
    public Bindings getBindings(int i) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void setBindings(Bindings bndngs, int i) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Bindings createBindings() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public ScriptContext getContext() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void setContext(ScriptContext sc) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public ScriptEngineFactory getFactory() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
