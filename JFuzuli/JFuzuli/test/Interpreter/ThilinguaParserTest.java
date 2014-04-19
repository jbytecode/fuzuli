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
public class ThilinguaParserTest {
    
    public ThilinguaParserTest() {
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
     * Test of getNextExpression method, of class ThilinguaParser.
     */
    @Test
    public void testGetNextExpression() {
        ThilinguaParser parser = new ThilinguaParser("3+2*2\n");
        Environment env = new Environment(null);
        Expression Expr = parser.getNextExpression();
        Object o = Expr.eval(env);
        assertEquals(new Double(78), o);
    }
    
}
