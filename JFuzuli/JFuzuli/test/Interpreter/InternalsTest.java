package Interpreter;

import javax.script.ScriptException;
import org.expr.fuzuli.interpreter.Environment;
import org.expr.fuzuli.interpreter.Parser;
import org.expr.fuzuli.scriptengine.FuzuliScriptEngine;
import org.junit.*;
import static org.junit.Assert.*;

public class InternalsTest {
    
    Environment envir;
    Parser parser;
    FuzuliScriptEngine engine;
    
    @Before
    public void init() {
        engine = new FuzuliScriptEngine();
    }
    
    @Test
    public void forTest() throws ScriptException {
        String code = "(def i INTEGER)(def a INTEGER)(def toplam INTEGER)\n"
                + "(def h INTEGER)(def j INTEGER)\n"
                + "\n"
                + "\n"
                + "(let a 100)\n"
                + "\n"
                + "# One For. \n"
                + "(for (let i 0) (< i 10) (inc i)\n"
                + "        (inc a)\n"
                + ")";
        engine.eval(code);
        assertEquals(110.0, engine.get("a"));
        
        code = "# Two nested for's\n"
                + "(let toplam 0.0)\n"
                + "(for (let i 0) (< i 10) (inc i)\n"
                + "        (for (let j 0) (< j 10) (inc j)\n"
                + "                (inc toplam)\n"
                + "        )\n"
                + ")";
        
        engine.eval(code);
        assertEquals(100.0, engine.get("toplam"));
        
        code = "# Three nested for's\n"
                + "(let toplam 0.0)\n"
                + "(for (let i 0) (< i 10) (inc i)\n"
                + "        (for (let j 0) (< j 10) (inc j)\n"
                + "                (for (let h 0) (< h 10) (inc h)\n"
                + "                        (inc toplam)\n"
                + "                )\n"
                + "        )\n"
                + ")";
        
        engine.eval(code);
        assertEquals(1000.0, engine.get("toplam"));
        
        code = "# for without block expression\n"
                + "(let i 0)\n"
                + "(for (let a 0) (< a 10) (inc a)\n"
                + "    (inc i)\n"
                + ")";
        
        engine.eval(code);
        assertEquals(10.0, engine.get("i"));
        
    }
    
    @Test
    public void foreachTest() throws ScriptException {
        String code = "(let summ 0)\n"
                + "(foreach i in (: 0 10)\n"
                + "    (let summ (+ summ i))\n"
                + ")\n"
                + "(let other (/ (* 10 11) 2))\n";
        
        engine.eval(code);
        assertEquals(engine.get("other"), engine.get("summ"));
    }
    
    @Test
    public void dotimesTest() throws ScriptException {
        String code = "(def summ INTEGER)\n"
                + "(let summ 0)\n"
                + "(dotimes i 10\n"
                + "    (let summ (+ summ i))\n"
                + ")\n"
                + "\n"
                + "\n"
                + "(let summ2 (/ (* 9 10) 2))\n";
        
        engine.eval(code);
        assertEquals(engine.get("summ2"), engine.get("summ"));
    }
    
    @Test
    public void fibonacciTest() throws ScriptException {
        String code = "(function fibonacci (params x)\n"
                + "    (block\n"
                + "    (if (<= x 2)\n"
                + "        (return 1)\n"
                + "        (return (+ (fibonacci (- x 1)) (fibonacci (- x 2))))\n"
                + "    )\n"
                + "    )\n"
                + ")";
        engine.eval(code);
        assertEquals(2.0, engine.eval("(fibonacci 3)"));
        assertEquals(3.0, engine.eval("(fibonacci 4)"));
        assertEquals(5.0, engine.eval("(fibonacci 5)"));
        assertEquals(8.0, engine.eval("(fibonacci 6)"));
        assertEquals(13.0, engine.eval("(fibonacci 7)"));
        assertEquals(21.0, engine.eval("(fibonacci 8)"));
        assertEquals(34.0, engine.eval("(fibonacci 9)"));
    }
    
    @Test
    public void integrationTest() throws ScriptException {
        String code = "(require \"math.nfl\")\n"
                + "(let pi 3.141592)\n"
                + "\n"
                + "(function integrate (params func a b)\n"
                + "    (let epsilon 0.0001)\n"
                + "    (let integral 0.0)\n"
                + "    (for (let x a) (< x b) (let x (+ x epsilon))\n"
                + "        (let val (eval func))\n"
                + "        (let integral (+ integral (* val epsilon)))\n"
                + "    )\n"
                + "    (return integral)\n"
                + ")\n"
                + "\n"
                + "\n"
                + "(let func (expression  (* (/ 1 (sqrt (* 2 pi))) (exp (* -0.5 (pow x 2) )))))\n"
                + "(let result (integrate func -1 1))\n";
        
        engine.eval(code);
        assertEquals(1.0, engine.eval("(<= (- result 0.68) 0.01)"));
    }
    
    @Test
    public void arithmaticTest() throws ScriptException {
        String code;
        
        assertEquals(1.0, engine.eval("(= (< 1 4) 1)"));
        assertEquals(1.0, engine.eval("(= 100 100)"));
        assertEquals(1.0, engine.eval("(= (< 1 4) 1)"));
        assertEquals(1.0, engine.eval("(= 100 100)"));
        assertEquals(1.0, engine.eval("(!= 11100 100)"));
        assertEquals(1.0, engine.eval("(= (& 72 184) 8)"));
        assertEquals(1.0, engine.eval("(= (| 72 184) 248)"));
        assertEquals(1.0, engine.eval("(= (<< 4 1) 8)"));
        assertEquals(1.0, engine.eval("(= ( ~ 4) -5)"));
        assertEquals(1.0, engine.eval("(= (& 72 184) 8)"));
        assertEquals(1.0, engine.eval("(= (& 72 184) 8)"));
        
        code = "(let a 0.1234567)\n"
                + "(let b 0.1234568)\n"
                + "(setepsilon 0.0000001)\n";
        engine.eval(code);
        assertEquals(1.0, engine.eval("(!= a b)"));
        
        code = "(let a \"astring\")\n"
                + "(let b \"astring\")\n";
        engine.eval(code);
        assertEquals(1.0, engine.eval("(= (!= a b) 0)"));
    }
    
    @Test
    public void ListTest() throws ScriptException {
        String code = "(let myList (list 1 2 3 4 5 6 7 8 9 10))\n"
                + "(let result 0)\n"
                + "(if (= (length myList) 10) (inc result))\n"
                + "(set myList 9 888)\n"
                + "(if (= (nth myList 9) 888) (inc result))\n";
        engine.eval(code);
        assertEquals(2.0, engine.get("result"));
        
        code = "(let b (list 1 2 3 4 5))\n"
                + "(let sum (+ (nth b 0) (nth b 1) (nth b 2) (nth b 3) (nth b 4)))";
        engine.eval(code);
        assertEquals(15.0, engine.get("sum"));
        
        code = "(let a (list 1 2 3 4 5 6 7 8 10))\n"
                + "(let b (nth a 0))";
        engine.eval(code);
        assertEquals(1.0, engine.eval("(= b 1)"));
        
        code = "(let mylist (list \"A\" \"B\" \"C\" \"D\" \"E\" \"F\"))\n"
                + "(let newlist (remove mylist 2))";
        engine.eval(code);
        assertEquals("D", engine.eval("(nth newlist 2)"));
        
        code = "(let mylist (list \"A\" \"B\" \"C\"))\n"
                + "(let f (find mylist \"C\"))";
        engine.eval(code);
        assertEquals(2.0, engine.get("f"));
        
        code = "(let mylist (list \"A\" \"B\"))\n"
                + "(append mylist \"C\")";
        engine.eval(code);
        assertEquals(1.0, engine.eval("(= (nth mylist 2) \"C\")"));
        
        code = "(let mylist (list \"B\" \"C\"))\n"
                + "(prepend mylist \"A\")";
        engine.eval(code);
        assertEquals("A", engine.eval("(nth mylist 0)"));
        
        code = "(let mylist (: 0 100))\n"
                + "(fill mylist 0)\n"
                + "(let sum 0.0)\n"
                + "(for (let i 0)(< i (length mylist)) (++i)\n"
                + "    (let sum (nth mylist i))\n"
                + ")";
        engine.eval(code);
        assertEquals(0.0, engine.get("sum"));
        
        code = "(require \"lang.nfl\")\n"
                + "(let mylist (list 10 100))\n"
                + "(let f (first mylist))";
        engine.eval(code);
        assertEquals(10.0, engine.get("f"));
        
        code = "(let mylist (list 1 2 3 4))\n"
                + "(let l (last mylist))";
        engine.eval(code);
        assertEquals(4.0, engine.get("l"));
        
        code = "(let mylist (: 1 1000))\n"
                + "(let l (last mylist))";
        engine.eval(code);
        assertEquals((long) 1000, engine.get("l"));
        
        code = "(let a '(1 2 3 4 5))";
        engine.eval(code);
        assertEquals(1.0, engine.eval("(= (- (last a) (first a)) 4)"));
    }
    
    @Test
    public void IncTest() throws ScriptException {
        String code = "(let i 10)\n"
                + "(inc i)";
        engine.eval(code);
        assertEquals(11.0, engine.get("i"));
        
        engine.eval("(++i)");
        assertEquals(12.0, engine.get("i"));
        
        engine.eval("(--i)");
        assertEquals(11.0, engine.get("i"));
        
        engine.eval("(dec i)");
        assertEquals(10.0, engine.get("i"));
    }
    
    @Test
    public void BreakTest() throws ScriptException {
        String code = "(let toplam 0.0)\n"
                + "\n"
                + "(for (let i 0) (< i 10) (let i (+ i 1))\n"
                + "        (for (let j 0) (< j 10) (let j (+ j 1))\n"
                + "                (for (let h 0) (< h 10) (let h (+ h 1))\n"
                + "                        #(print i \" \" j \" \" h \"\\n\")\n"
                + "                        (let toplam (+ toplam 1.0))\n"
                + "                        (if (= toplam 100) (break))\n"
                + "                )\n"
                + "                (if (= toplam 100) (break))\n"
                + "        )\n"
                + "        (if (= toplam 100) (break))\n"
                + ")";
        engine.eval(code);
        assertEquals(100.0, engine.get("toplam"));
    }
    
    @Test
    public void ArgcTest() throws ScriptException {
        if (engine.get("argc") != null) {
            assertEquals(1.0, engine.eval("(> argc 0)"));
        }
    }
    
    @Test
    public void BlockTest() throws ScriptException {
        String code = "(let x 4)\n"
                + "\n"
                + "(block\n"
                + "    (let a 10)\n"
                + "    (let x 50)\n"
                + ")";
        engine.eval(code);
        assertEquals(1.0, engine.eval("(= (typeof a) NULL)"));
        assertEquals(1.0, engine.eval("(= x 50)"));
    }
    
    @Test
    public void HexTest() throws ScriptException {
        engine.eval("(let a 0xffff)");
        assertEquals(65535.0, engine.get("a"));
    }
    
    @Test
    public void WhileTest() throws ScriptException {
        String code = "(let i 1)\n"
                + "(while (< 1 2)\n"
                + "                (let i (+ i 1))\n"
                + "                (if (= i 100) (break))\n"
                + ")";
        engine.eval(code);
        assertEquals(100.0, engine.get("i"));
    }
    
    
}
