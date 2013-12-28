/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Interpreter;

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
public class ExpressionTest {
    
    public ExpressionTest() {
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
     * Test of eval method, of class PlusExpression.
     */
    @Test
    public void testConstantNumberExpression() {
        System.out.println("ConstantNumberExpression");
        Environment e = new Environment(null);
        ConstantNumberExpression c1 = new ConstantNumberExpression(3.1415);
        Object result = c1.eval(e);
        assertEquals(result, new Double(3.1415));
    }
    
    @Test
    public void testIdentifierExpression() {
        System.out.println("IdentifierNumberExpression");
        Environment e = new Environment(null);
        ConstantNumberExpression c1 = new ConstantNumberExpression(3.1415);
        e.setVariable("x", c1.eval(e));
        IdentifierExpression i = new IdentifierExpression("x");
        Object result = i.eval(e);
        assertEquals(result, new Double(3.1415));
    }
}
