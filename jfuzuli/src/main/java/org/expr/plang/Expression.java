package org.expr.plang;

public abstract class Expression {

	public abstract Object eval(Environment env);
        
        public String emitJS(){
            return "JS Emitter is not implemented for " + this.getClass().getCanonicalName() + " -> " + this.toString() ;
        }
	
}
