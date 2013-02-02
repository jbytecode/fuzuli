package Interpreter;



public class IntegerExpression extends Expression {

    FValue value;

    public IntegerExpression(Integer intObject) {
        value = new FValue(intObject);
    }
    
    
    @Override
    public FValue eval(Environment e) {
        return(this.value);
    }

    
}
