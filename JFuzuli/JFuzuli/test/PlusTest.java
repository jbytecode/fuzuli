/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.ArrayList;
import Interpreter.DoubleExpression;
import Interpreter.Environment;
import Interpreter.IntegerExpression;
import Interpreter.PlusExpression;
import Interpreter.Expression;
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
public class PlusTest {
    
    public PlusTest() {
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
    // TODO add test methods here.
    // The methods must be annotated with annotation @Test. For example:
    //
    // @Test
    // public void hello() {}
    
    @Test
    public void testPlusExpression(){
        ArrayList<Expression> ae = new ArrayList<>();                
        ae.add(new DoubleExpression(7.5));
        ae.add(new IntegerExpression(5));
        PlusExpression pe = new PlusExpression(ae);
        Object result = pe.eval(new Environment());
        System.out.println(((Expression)result).getNumericValue());
    }
}