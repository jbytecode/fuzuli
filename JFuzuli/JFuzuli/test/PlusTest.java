/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.ArrayList;
import Interpreter.NumberExpression;
import Interpreter.Environment;
import Interpreter.PlusExpression;
import Interpreter.Expression;
import Interpreter.FValue;
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
        ae.add(new NumberExpression(7.5));
        ae.add(new NumberExpression(5));
        PlusExpression pe = new PlusExpression(ae);
        FValue result = pe.eval(new Environment(null));
        System.out.println(result.getAsDouble());
    }
}