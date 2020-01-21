/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.expr.plang.tests;

import java.io.InputStream;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import org.expr.plang.Environment;
import org.expr.plang.Interpreter;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class TestJSEmitter {

    public static ScriptEngine runJSProgram(String code) throws Exception {
        ScriptEngineManager manager = new ScriptEngineManager();
        ScriptEngine engine = manager.getEngineByName("ECMAScript");
        engine.eval(code);
        System.out.println("*** Running jscode: " + code);
        return engine;
    }

    @Test
    public void testEmitJS1Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("recursive-factorial.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer result1 = (Integer) engine.get("result1");
        Integer result2 = (Integer) engine.get("result2");
        Assertions.assertEquals(120, result1.intValue());
        Assertions.assertEquals(720, result2.intValue());
    }

    @Test
    public void testEmitJS2Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("append.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("newlist[0]");
        Integer val2 = (Integer) engine.eval("newlist[1]");
        Integer val3 = (Integer) engine.eval("newlist[2]");
        Integer val4 = (Integer) engine.eval("newlist[3]");

        Assertions.assertEquals(1, val1.intValue());
        Assertions.assertEquals(2, val2.intValue());
        Assertions.assertEquals(3, val3.intValue());
        Assertions.assertEquals(10, val4.intValue());
    }

    @Test
    public void testEmitJS3Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("apply.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        for (var i = 0; i < 10; i++) {
            Integer val = (Integer) engine.eval("result[" + i + "]");
            Assertions.assertEquals((i + 1) * (i + 1), val.intValue());
        }

    }

    @Test
    public void testEmitJS4Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("custom-abs.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("result1");
        Integer val2 = (Integer) engine.eval("result2");
        Integer val3 = (Integer) engine.eval("result3");

        Assertions.assertEquals(10, val1.intValue());
        Assertions.assertEquals(10, val2.intValue());
        Assertions.assertEquals(0, val3.intValue());
    }

    @Test
    public void testEmitJS5Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("functions-return-functions.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("result");
        Assertions.assertEquals(100, val1.intValue());
    }

    @Test
    public void testEmitJS6Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("functions-take-functions.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        for (var i = 0; i < 6; i++) {
            Integer val = (Integer) engine.eval("result[" + i + "]");
            Assertions.assertEquals((i + 1) * (i + 1), val.intValue());
        }
    }

    @Test
    public void testEmitJS7Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("headrest.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("result1");
        Assertions.assertEquals(1, val1.intValue());

        for (var i = 0; i < 4; i++) {
            Integer val = (Integer) engine.eval("result2[" + i + "]");
            Assertions.assertEquals(i + 2, val.intValue());
        }

    }

    @Test
    public void testEmitJS8Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("lambda.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        for (var i = 0; i < 10; i++) {
            Integer val = (Integer) engine.eval("result[" + i + "]");
            Assertions.assertEquals((i + 1) * (i + 1), val.intValue());
        }
    }

    @Test
    public void testEmitJS9Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("list-len.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("result");
        Assertions.assertEquals(1000, val1.intValue());

    }

    @Test
    public void testEmitJS10Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("nth.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("result1");
        Integer val2 = (Integer) engine.eval("result2");
        Integer val3 = (Integer) engine.eval("result3");

        Assertions.assertEquals(10, val1.intValue());
        Assertions.assertEquals(20, val2.intValue());
        Assertions.assertEquals(30, val3.intValue());

    }

    @Test
    public void testEmitJS11Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("prepend.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("newlist[0]");
        Integer val2 = (Integer) engine.eval("newlist[1]");
        Integer val3 = (Integer) engine.eval("newlist[2]");
        Integer val4 = (Integer) engine.eval("newlist[3]");

        Assertions.assertEquals(10, val1.intValue());
        Assertions.assertEquals(1, val2.intValue());
        Assertions.assertEquals(2, val3.intValue());
        Assertions.assertEquals(3, val4.intValue());

    }

    @Test
    public void testEmitJS12Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("typecasting.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Integer val1 = (Integer) engine.eval("result1");
        Integer val2 = (Integer) engine.eval("result2");
        Double val3 = (Double) engine.eval("result3");
        Double val4 = (Double) engine.eval("result4");
        Integer val5 = (Integer) engine.eval("result5");
        Integer val6 = (Integer) engine.eval("result6");
        Integer val7 = (Integer) engine.eval("result7");

        Assertions.assertEquals(10, val1.intValue());
        Assertions.assertEquals(10, val2.intValue());
        Assertions.assertEquals(10.01, val3.doubleValue());
        Assertions.assertEquals(10.01, val4.doubleValue());
        Assertions.assertEquals(10, val5.intValue());
        Assertions.assertEquals(10, val6.intValue());
        Assertions.assertEquals(10, val7.intValue());
    }

    @Test
    public void testEmitJS13Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("ifelse.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        String val1 = (String) engine.eval("result1");
        String val2 = (String) engine.eval("result2");
        String val3 = (String) engine.eval("result3");
        String val4 = (String) engine.eval("result4");

        Assertions.assertEquals("Yes", val1);
        Assertions.assertEquals("Yes", val2);
        Assertions.assertEquals("Yes", val3);
        Assertions.assertEquals("No", val4);

    }

    @Test
    public void testEmitJS14Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("math.fzl");
        String fcode = Interpreter.loadCodeFromInputStream(is);
        String jscode = Interpreter.emitJS(fcode);

        ScriptEngine engine = runJSProgram(jscode);

        Double val1 = (Double) engine.eval("result1");
        Integer val2 = (Integer) engine.eval("result2");
        Integer val3 = (Integer) engine.eval("result3");
        Integer val4 = (Integer) engine.eval("result4");

        Assertions.assertTrue(val1 <= 1);
        Assertions.assertTrue(val1 >= 0);
        Assertions.assertEquals(5, val2.intValue());
        Assertions.assertEquals(1, val3.intValue());
        Assertions.assertEquals(1024, val4.intValue());

    }
}
