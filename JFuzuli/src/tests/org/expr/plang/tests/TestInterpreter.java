package tests.org.expr.plang.tests;

import static org.junit.jupiter.api.Assertions.*;

import java.io.InputStream;
import java.util.List;

import org.expr.plang.Environment;
import org.expr.plang.Interpreter;
import org.junit.jupiter.api.Test;

class TestInterpreter {

	@Test
	void testInterprete1() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("custom-abs.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result1 = (Integer)env.getObject("result1");
		Integer result2 = (Integer)env.getObject("result2");
		Integer result3 = (Integer)env.getObject("result3");
		assertEquals(10, result1.intValue());
		assertEquals(10, result2.intValue());
		assertEquals(0, result3.intValue());
	}
	
	@Test
	void testMap() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("apply.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		List<Integer> result = (List<Integer>) env.getObject("result");
		for (int i = 0; i < result.size(); i++) {
			assertEquals((i + 1) * (i + 1), result.get(i).intValue());
		}
	}
	
	@Test
	void testRecursiveFactorial() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("recursive-factorial.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result1 = (Integer)env.getObject("result1");
		Integer result2 = (Integer)env.getObject("result2");
		assertEquals(120, result1.intValue());
		assertEquals(720, result2.intValue());
	}
	
	
	@Test
	void testFunctionsTakeFunctions() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("functions-take-functions.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		List<Integer> result = (List<Integer>) env.getObject("result");
		for (int i = 0; i < result.size(); i++) {
			assertEquals((i + 1) * (i + 1), result.get(i).intValue());
		}
	}
	
	
	@Test
	void testFunctionsReturnFunctions() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("functions-return-functions.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result = (Integer)env.getObject("result");
		assertEquals(100, result.intValue());
	}

	@Test
	void testListLength() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("list-len.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result = (Integer)env.getObject("result");
		assertEquals(1000, result.intValue());
	}
	
	
	@Test
	void testJavaStatic() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("javastatic.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Number result1 = (Number)env.getObject("result1");
		Number result2 = (Number)env.getObject("result2");
		Long result3 = (Long)env.getObject("result3");
		Double result4 = (Double)env.getObject("result4");
		String result5 = (String)env.getObject("result5");
		assertEquals(6.0, result1);
		assertEquals(10.0, result2);
		assertEquals(1, result3.longValue());
		assertEquals(25.0, result4.doubleValue());
		assertEquals("3", result5);
	}
	
	@Test
	void testTypeCasting() throws Exception {
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
		
		
		assertEquals(java.lang.Byte.class, result1.getClass());
		assertEquals(java.lang.Integer.class, result2.getClass());
		assertEquals(java.lang.Float.class, result3.getClass());
		assertEquals(java.lang.Double.class, result4.getClass());
		assertEquals(java.lang.Short.class, result5.getClass());
		assertEquals(java.lang.Long.class, result6.getClass());
		assertEquals(java.lang.Character.class, result7.getClass());
	}
	
	@Test
	void testComments() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("comments.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Object result1 = env.getObject("result1");
		Object result2 = env.getObject("result2");
		Object result3 = env.getObject("result3");
		assertEquals(10, result1);
		assertEquals(20, result2);
		assertEquals(30, result3);
	}
	
	@Test
	void TestHeadTail() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("headrest.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Object result1 = env.getObject("result1");
		Object result2 = env.getObject("result2");
		assertEquals(1, result1);
		
		List<Integer> list = (List<Integer>)result2;
		assertEquals (2, list.get(0).intValue());
		assertEquals (3, list.get(1).intValue());
		assertEquals (4, list.get(2).intValue());
		assertEquals (5, list.get(3).intValue());
	}
	
	@Test
	void testNthExpression() throws Exception{
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("nth.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Object result1 = env.getObject("result1");
		Object result2 = env.getObject("result2");
		Object result3 = env.getObject("result3");
		
		assertEquals(10, result1);
		assertEquals(20, result2);
		assertEquals(30, result3);
	}
	
	@Test
	void testLambda() throws Exception{
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("lambda.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		List<Integer> result = (List<Integer>) env.getObject("result");
		for (int i = 0; i < result.size(); i++) {
			assertEquals((i + 1) * (i + 1), result.get(i).intValue());
		}
	}
}
