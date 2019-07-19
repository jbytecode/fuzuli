package org.expr.plang.tests;

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
		assertEquals(10, result1);
		assertEquals(10, result2);
		assertEquals(0, result3);
	}
	
	@Test
	void testMap() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("apply.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		List<Integer> result = (List<Integer>) env.getObject("result");
		for (int i = 0; i < result.size(); i++) {
			assertEquals((i + 1) * (i + 1), result.get(i));
		}
	}
	
	@Test
	void testRecursiveFactorial() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("recursive-factorial.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result1 = (Integer)env.getObject("result1");
		Integer result2 = (Integer)env.getObject("result2");
		assertEquals(120, result1);
		assertEquals(720, result2);
	}
	
	
	@Test
	void testFunctionsTakeFunctions() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("functions-take-functions.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		List<Integer> result = (List<Integer>) env.getObject("result");
		for (int i = 0; i < result.size(); i++) {
			assertEquals((i + 1) * (i + 1), result.get(i));
		}
	}
	
	
	@Test
	void testFunctionsReturnFunctions() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("functions-return-functions.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result = (Integer)env.getObject("result");
		assertEquals(100, result);
	}

	@Test
	void testListLength() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("list-len.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Integer result = (Integer)env.getObject("result");
		assertEquals(1000, result);
	}
	
	
	@Test
	void testJavaStatic() throws Exception {
		Environment env = new Environment();
		InputStream is = this.getClass().getResourceAsStream("javastatic.fzl");
		Interpreter.interpreteFromInputStream(is, env);
		Number result1 = (Number)env.getObject("result1");
		Number result2 = (Number)env.getObject("result2");
		Long result3 = (Long)env.getObject("result3");
		assertEquals(6.0, result1);
		assertEquals(10.0, result2);
		assertEquals(1, result3);
	}
}