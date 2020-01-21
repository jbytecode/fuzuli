package org.expr.plang;

public class IdentifierExpression extends Expression {

	private String id;
	
	public IdentifierExpression(String id) {
		this.id = id;
	}
	
	public String getId() {
		return this.id;
	}
	
	@Override
	public Object eval(Environment env) {
		return env.getObject(this.id);
	}
	
	@Override
	public String toString() {
		return this.id;
	}

}
