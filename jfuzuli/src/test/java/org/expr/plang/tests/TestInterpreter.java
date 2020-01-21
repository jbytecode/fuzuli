package org.expr.plang.tests;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.List;

import org.expr.plang.Environment;
import org.expr.plang.Interpreter;
import org.junit.jupiter.api.Test;
import org.expr.plang.AssertExpression;
import org.junit.jupiter.api.Assertions;

public class TestInterpreter {

    public TestInterpreter() {

    }

    @Test
    public void testInterprete1Test() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("custom-abs.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Integer result1 = (Integer) env.getObject("result1");
        Integer result2 = (Integer) env.getObject("result2");
        Integer result3 = (Integer) env.getObject("result3");
        Assertions.assertEquals(10, result1.intValue());
        Assertions.assertEquals(10, result2.intValue());
        Assertions.assertEquals(0, result3.intValue());
    }

    @Test
    public void testMap() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("apply.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        List<Integer> result = (List<Integer>) env.getObject("result");
        for (int i = 0; i < result.size(); i++) {
            Assertions.assertEquals((i + 1) * (i + 1), result.get(i).intValue());
        }
    }

    @Test
    public void testRecursiveFactorial() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("recursive-factorial.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Integer result1 = (Integer) env.getObject("result1");
        Integer result2 = (Integer) env.getObject("result2");
        Assertions.assertEquals(120, result1.intValue());
        Assertions.assertEquals(720, result2.intValue());
    }

    @Test
    public void testFunctionsTakeFunctions() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("functions-take-functions.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        List<Integer> result = (List<Integer>) env.getObject("result");
        for (int i = 0; i < result.size(); i++) {
            Assertions.assertEquals((i + 1) * (i + 1), result.get(i).intValue());
        }
    }

    @Test
    public void testFunctionsReturnFunctions() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("functions-return-functions.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Integer result = (Integer) env.getObject("result");
        Assertions.assertEquals(100, result.intValue());
    }

    @Test
    public void testListLength() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("list-len.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Integer result = (Integer) env.getObject("result");
        Assertions.assertEquals(1000, result.intValue());
    }

    @Test
    public void testJavaStatic() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("javastatic.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Number result1 = (Number) env.getObject("result1");
        Number result2 = (Number) env.getObject("result2");
        Long result3 = (Long) env.getObject("result3");
        Double result4 = (Double) env.getObject("result4");
        //String result5 = (String) env.getObject("result5");
        Assertions.assertEquals(6.0, result1);
        Assertions.assertEquals(10.0, result2);
        Assertions.assertEquals(1, result3.longValue());
        Assertions.assertEquals(25.0, result4.doubleValue());
        //Assertions.assertEquals("3", result5);
    }

    @Test
    public void testTypeCasting() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("typecasting.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result1");
        Object result2 = env.getObject("result2");
        Object result3 = env.getObject("result3");
        Object result4 = env.getObject("result4");
        Object result5 = env.getObject("result5");
        Object result6 = env.getObject("result6");
        Object result7 = env.getObject("result7");

        Assertions.assertEquals(java.lang.Byte.class, result1.getClass());
        Assertions.assertEquals(java.lang.Integer.class, result2.getClass());
        Assertions.assertEquals(java.lang.Float.class, result3.getClass());
        Assertions.assertEquals(java.lang.Double.class, result4.getClass());
        Assertions.assertEquals(java.lang.Short.class, result5.getClass());
        Assertions.assertEquals(java.lang.Long.class, result6.getClass());
        Assertions.assertEquals(java.lang.Character.class, result7.getClass());
    }

    @Test
    public void testComments() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("comments.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result1");
        Object result2 = env.getObject("result2");
        Object result3 = env.getObject("result3");
        Assertions.assertEquals(10, result1);
        Assertions.assertEquals(20, result2);
        Assertions.assertEquals(30, result3);
    }

    @Test
    public void TestHeadTail() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("headrest.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result1");
        Object result2 = env.getObject("result2");
        Assertions.assertEquals(1, result1);

        List<Integer> list = (List<Integer>) result2;
        Assertions.assertEquals(2, list.get(0).intValue());
        Assertions.assertEquals(3, list.get(1).intValue());
        Assertions.assertEquals(4, list.get(2).intValue());
        Assertions.assertEquals(5, list.get(3).intValue());
    }

    @Test
    public void testNthExpression() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("nth.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result1");
        Object result2 = env.getObject("result2");
        Object result3 = env.getObject("result3");

        Assertions.assertEquals(10, result1);
        Assertions.assertEquals(20, result2);
        Assertions.assertEquals(30, result3);
    }

    @Test
    public void testLambda() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("lambda.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        List<Integer> result = (List<Integer>) env.getObject("result");
        for (int i = 0; i < result.size(); i++) {
            Assertions.assertEquals((i + 1) * (i + 1), result.get(i).intValue());
        }
    }

    @Test
    public void TestAppend() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("append.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result");

        List<Integer> list = (List<Integer>) result1;
        Assertions.assertEquals(1, list.get(0).intValue());
        Assertions.assertEquals(2, list.get(1).intValue());
        Assertions.assertEquals(3, list.get(2).intValue());
        Assertions.assertEquals(10, list.get(3).intValue());
    }

    @Test
    public void TestPrepend() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("prepend.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result");

        List<Integer> list = (List<Integer>) result1;
        Assertions.assertEquals(10, list.get(0).intValue());
        Assertions.assertEquals(1, list.get(1).intValue());
        Assertions.assertEquals(2, list.get(2).intValue());
        Assertions.assertEquals(3, list.get(3).intValue());
    }

    @Test
    public void TestEvalExpression() throws Exception {
        Environment env = new Environment();
        InputStream is = this.getClass().getResourceAsStream("eval-expression.fzl");
        Interpreter.interpreteFromInputStream(is, env);
        Object result1 = env.getObject("result");
        Assertions.assertEquals(20, result1);
    }
}
