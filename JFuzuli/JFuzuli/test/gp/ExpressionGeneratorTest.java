/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gp;

import org.expr.fuzuli.interpreter.AsterixExpression;
import org.expr.fuzuli.interpreter.ConstantNumberExpression;
import org.expr.fuzuli.interpreter.DivisionExpression;
import org.expr.fuzuli.interpreter.Environment;
import org.expr.fuzuli.interpreter.Expression;
import org.expr.fuzuli.interpreter.IdentifierExpression;
import org.expr.fuzuli.interpreter.MinusExpression;
import org.expr.fuzuli.interpreter.PlusExpression;
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
