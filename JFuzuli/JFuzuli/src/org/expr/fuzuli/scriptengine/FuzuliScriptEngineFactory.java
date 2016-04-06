/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.expr.fuzuli.scriptengine;

import java.util.LinkedList;
import java.util.List;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineFactory;
import javax.script.ScriptEngineManager;

/**
 *
 * @author hako
 */
public class FuzuliScriptEngineFactory implements ScriptEngineFactory {

    private String engineName = "Fuzuli";
    private String version = "0.1";
    private FuzuliScriptEngine fuzuliScriptEngine;
    
    static{
        System.out.println("Registering");
        ScriptEngineManager manager = new ScriptEngineManager();
        manager.registerEngineName("fuzuli", new FuzuliScriptEngineFactory());
    }
    
    @Override
    public String getEngineName() {
        return(this.engineName);
    }

    @Override
    public String getEngineVersion() {
        return(version);
    }

    @Override
    public List<String> getExtensions() {
        LinkedList<String> ext = new LinkedList<>();
        ext.add("fzl");
        ext.add("nfl");
        return(ext);
    }

    @Override
    public List<String> getMimeTypes() {
        LinkedList<String> mimes = new LinkedList<>();
        mimes.add("text/fuzuli");
        return(mimes);
    }

    @Override
    public List<String> getNames() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public String getLanguageName() {
        return(this.engineName);
    }

    @Override
    public String getLanguageVersion() {
        return(this.version);
    }

    @Override
    public Object getParameter(String string) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public String getMethodCallSyntax(String string, String string1, String... strings) {
        return("(funcname param1 params2 ... paramn)");
    }

    @Override
    public String getOutputStatement(String string) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public String getProgram(String... strings) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public ScriptEngine getScriptEngine() {
        if(this.fuzuliScriptEngine == null){
            this.fuzuliScriptEngine = new FuzuliScriptEngine();
        }
        return(this.fuzuliScriptEngine);
    }
    
}
