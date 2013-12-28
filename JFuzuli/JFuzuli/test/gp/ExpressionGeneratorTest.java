/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gp;

import Interpreter.AsterixExpression;
import Interpreter.ConstantNumberExpression;
import Interpreter.DivisionExpression;
import Interpreter.Environment;
import Interpreter.Expression;
import Interpreter.IdentifierExpression;
import Interpreter.MinusExpression;
import Interpreter.PlusExpression;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author hako
 */
public class ExpressionGeneratorTest {
    
    public ExpressionGeneratorTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of createRandomExpression method, of class ExpressionGenerator.
     */
    @Test
    public void testCreateRandomExpression(){
        System.out.println("createRandomExpression");
        String[] identifierList = new String[]{"x","y"};
        Class[] exprList = new Class[]{
            ConstantNumberExpression.class,
            IdentifierExpression.class,
            PlusExpression.class,
            MinusExpression.class,
            AsterixExpression.class,
            DivisionExpression.class
        };
        ExpressionGenerator eg = new ExpressionGenerator();
        Expression e = eg.createRandomExpression(exprList, identifierList,0);
        System.out.println(e.toString());
        Environment env = new Environment(null);
        env.setVariable("x", 1.0);
        env.setVariable("y", 1.0);
        Object result = e.eval(env);
        System.out.println(result);
        assertEquals(result.getClass(), Double.class);       
        //fail("The test case is a prototype.");
    }
    
}
