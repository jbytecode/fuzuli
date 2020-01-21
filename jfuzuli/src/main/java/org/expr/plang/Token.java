package org.expr.plang;

public class Token {
	public final static int TOKEN_INTEGER = 1;
	public final static int TOKEN_DOUBLE = 2;
	public final static int TOKEN_IDENTIFIER = 3;
	public final static int TOKEN_LPARANT = 4;
	public final static int TOKEN_RPARANT = 5;
	public final static int TOKEN_PLUS = 6;
	public final static int TOKEN_MINUS = 7;
	public final static int TOKEN_STRING = 8;
	public final static int TOKEN_ENDPROGRAM = 9;
	public final static int TOKEN_EQUAL = 10;
	public final static int TOKEN_ASTERIX = 11;
	public final static int TOKEN_LESS = 12;
	public final static int TOKEN_GREATER = 13;
	public final static int TOKEN_TWOPOINTS = 14;
	public final static int TOKEN_SHARP = 15;
	
	
	public String content;
	public int tokentype;
	
	public Token(String content, int tokentype) {
		this.content = content;
		this.tokentype = tokentype;
	}
	
	@Override
	public String toString() {
		return "[" + this.content + "(" + this.tokentype + ")]";
	}
}
