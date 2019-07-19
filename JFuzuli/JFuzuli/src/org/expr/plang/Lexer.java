package org.expr.plang;

import java.util.ArrayList;
import java.util.List;

public class Lexer {

	String sourceCode;
	int currentIndex;
	
	public Lexer(String sourceCode) {
		this.sourceCode = sourceCode + " ";
		this.reset();
	}
	
	public void reset() {
		this.currentIndex = 0;
	}
	
	public char consumeChar() {
		if(currentIndex < sourceCode.length()) {
			char result = this.sourceCode.charAt(currentIndex);
			this.currentIndex++;
			return result;
		}else {
			return (char)-1;
		}
	}
	
	public void putBackChar() {
		this.currentIndex--;
		if(this.currentIndex < 0) {
			this.currentIndex = 0;
		}
	}
	
	public boolean isDigit(char c) {
		return Character.isDigit(c);
	}
	
	public boolean isLetter(char c) {
		return Character.isLetter(c);
	}
	
	public boolean isBlank(char c) {
		return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
	}
	
	public Token consumeNumber() {
		StringBuilder s = new StringBuilder();
		while(true) {
			char c = consumeChar();
			if(isDigit(c) || c == '.' || c == '-' || c == '+' || c == 'e' || c == 'E') {
				s.append(c);
			}else {
				putBackChar();
				break;
			}
		}
		if(s.indexOf(".") > 0) {
			return new Token(s.toString(), Token.TOKEN_DOUBLE);
		}else {
			return new Token(s.toString(), Token.TOKEN_INTEGER);
		}
	}
	
	public Token consumeIdentifier() {
		StringBuilder s = new StringBuilder ();
		while(true) {
			char c = consumeChar();
			if(isDigit(c) || isLetter(c) || c == '_') {
				s.append(c);
			}else {
				putBackChar();
				break;
			}
		}
		return new Token (s.toString(), Token.TOKEN_IDENTIFIER);
	}
	
	public Token consumeString() {
		StringBuilder s = new StringBuilder();
		char firstChar = consumeChar();
		while(true) {
			char currentChar = consumeChar();
			if(currentChar == firstChar) {
				break;
			}
			s.append(currentChar);
		}
		return new Token(s.toString(), Token.TOKEN_STRING);
	}
	
	public Token consumeToken() {
		char currentChar = consumeChar();
		if(currentChar == (char)-1) {
			return new Token ("", Token.TOKEN_ENDPROGRAM);
		}else if (isBlank(currentChar)) {
			return consumeToken();
		} else if(isDigit(currentChar)) {
			putBackChar();
			return consumeNumber();
		}else if(isLetter(currentChar)) {
			putBackChar();
			return consumeIdentifier();
		}else if(currentChar == '\'') {
			putBackChar();
			return consumeString();
		}else if (currentChar == '('){
			return new Token("(", Token.TOKEN_LPARANT);
		}else if (currentChar == ')'){
			return new Token(")", Token.TOKEN_RPARANT);
		}else if (currentChar == '+'){
			return new Token("+", Token.TOKEN_PLUS);
		}else if (currentChar == '-'){
			return new Token("+", Token.TOKEN_MINUS);
		}else if (currentChar == '='){
			return new Token("=", Token.TOKEN_EQUAL);
		}else if (currentChar == '*'){
			return new Token("*", Token.TOKEN_ASTERIX);
		}else if(currentChar == '<'){
			return new Token("<", Token.TOKEN_LESS);
		}else if(currentChar == '>'){
			return new Token(">", Token.TOKEN_GREATER);
		}else if(currentChar == '='){
			return new Token(">", Token.TOKEN_EQUAL);
		}else if(currentChar == ':'){
			return new Token(":", Token.TOKEN_TWOPOINTS);
		}else {
			throw new RuntimeException("Cannot consume token for " + currentChar);
		}
	}
	
	
	public List<Token> consomeAllTokens(){
		this.reset();
		List<Token> tokens = new ArrayList<>();
		while(true) {
			Token tok = this.consumeToken();
			if(tok.tokentype == Token.TOKEN_ENDPROGRAM) {
				break;
			}
			tokens.add(tok);
		}
		return tokens;
	}
}
