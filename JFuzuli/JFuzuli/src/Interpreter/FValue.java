/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

/**
 *
 * @author hako
 */
public class FValue {
    
    Object obj = null;
    
    public FValue(int i){
        obj = new Integer(i);
    }
    
    public FValue (double d){
        obj = new Double(d);
    }
    
    public FValue (Object o){
        obj = o;
    }
    
    public Object getObject(){
        return(obj);
    }
    
    public double getAsDouble(){
        if (obj instanceof Number){
            Number n = (Number) obj;
            return (n.doubleValue());
        }else{
            throw new RuntimeException(obj+" is not a number");
        }
    }
}
