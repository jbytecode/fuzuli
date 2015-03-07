/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

import java.util.ArrayList;
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
public class FunctionCallTest {
    
    public FunctionCallTest() {
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
    
    @Test
    public void functionCallTest(){
        StringBuilder code = new StringBuilder();
        code.append("(function test (params) (return 55))\n\n");
        Parser p = new Parser(code.toString());
        Environment envir = new Environment(null);
        ArrayList<Expression> exprs = p.getExpressionList();
        for (int i=0;i<exprs.size();i++){
            exprs.get(i).eval(envir);
        }
        
        ArrayList<Object> params = new ArrayList<>();
        
        Object result = FunctionCallExpression.doFunctionCall("test", params, envir);
        assertEquals(result, 55.0);
    }
    
}
