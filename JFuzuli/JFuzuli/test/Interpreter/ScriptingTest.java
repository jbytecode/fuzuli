/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

import java.util.ArrayList;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import org.expr.fuzuli.interpreter.ConstantNumberExpression;
import org.expr.fuzuli.interpreter.IdentifierExpression;
import org.expr.fuzuli.interpreter.Environment;
import org.expr.fuzuli.scriptengine.FuzuliScriptEngine;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

public class ScriptingTest {
    
    @Test
    public void testHelloWorld(){
        FuzuliScriptEngine engine = new FuzuliScriptEngine();
        assertNotNull(engine);
        Object result = null;
        try{
            result = engine.eval("(* 6 5)");
        }catch (Exception e){
            System.out.println("** "+e.toString());
        }
        assertEquals(result, 30.0);
    }
    
    @Test
    public void testSetVariable(){
        FuzuliScriptEngine engine = new FuzuliScriptEngine();
        assertNotNull(engine);
        Object result = null;
        try{
            engine.put("a", 10.0);
            engine.put("b", 2.3);
            result = engine.eval("(* a b)");
        }catch (Exception e){
            System.out.println("** "+e.toString());
        }
        assertEquals(result, 23.0);
    }
    
    @Test
    public void testGetVariable(){
        FuzuliScriptEngine engine = new FuzuliScriptEngine();
        assertNotNull(engine);
        Object result = null;
        try{
            engine.put("a", new Double(100.0));
            engine.put("b", new Double(2.40));
            engine.eval("(let result (+ a b))");
        }catch (Exception e){
            System.out.println("** "+e.toString());
        }
        result = engine.get("result");
        assertEquals(result, 102.4);
    }
    
    @Test
    public void testPutList(){
        FuzuliScriptEngine engine = new FuzuliScriptEngine();
        assertNotNull(engine);
        Object result = null;
        try{
            ArrayList<Double> arr = new ArrayList<>();
            arr.add(1.0);
            arr.add(2.0);
            arr.add(3.0);
            arr.add(4.0);
            engine.put("mylist", arr);
            engine.eval("(let result (length mylist))");
            result = engine.get("result");
        }catch (Exception e){
            System.out.println("** "+e.toString());
        }
        
        assertEquals(4, result);
    }
}
