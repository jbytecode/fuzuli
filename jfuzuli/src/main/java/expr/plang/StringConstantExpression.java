package org.expr.plang;

public class StringConstantExpression extends Expression {

	private String content;
	
	public StringConstantExpression(String str) {
		this.content = str;
	}
	
	@Override
	public Object eval(Environment env) {
		return this.content;
	}
	
	@Override
	public String toString() {
		return this.content;
	}
	
	public String getContent() {
		return this.content;
	}

}
