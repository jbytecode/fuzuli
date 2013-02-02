/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

/**
 *
 * @author hako
 */
public class Parser {

    String sourcecode;
    int charIndex;

    public Parser(String code) {
        this.sourcecode = code;
    }

    public Parser(File file) {
        StringBuffer code = new StringBuffer();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            char[] chars = new char[1024];
            int result;
            while (true) {
                result = reader.read(chars);
                if (result == -1) {
                    break;
                }
                code.append(chars);
                for (int i = 0; i < chars.length; i++) {
                    chars[i] = '\0';
                }
            }
            this.sourcecode = code.toString();
        } catch (Exception e) {
            System.out.println("Error reading file:" + file.toString());
            e.printStackTrace();
        }
    }

    public void resetParser() {
        charIndex = 0;
    }

    public char consume() {
        char current = this.sourcecode.charAt(charIndex);
        charIndex++;
        if (charIndex == sourcecode.length()) {
            return ('\0');
        }
        return (current);
    }

    public void putBackChar() {
        charIndex--;
    }
    
    public char looknext(){
        if ((charIndex + 1) != sourcecode.length()){
            return(this.sourcecode.charAt(charIndex+1));
        }else{
            return('\0');
        }
    }

    public Token getNextToken() {
        StringBuffer buf = new StringBuffer();
        Token tok = new Token();
        char current;
        current = consume();
        if (current == '\0') {
            tok.type = Token.TokenType.EOP;
            tok.content = "";
            return(tok);
        }else if (current == ' ' || current == '\t'){
            return(getNextToken());
        }else if (current == '(') {
            tok.content = "(";
            tok.type = Token.TokenType.LPARAN;
            return (tok);
        } else if (current == ')') {
            tok.content = ")";
            tok.type = Token.TokenType.RPARAN;
            return(tok);
        } else if (Character.isDigit(current)) {
            buf.append(current);
            while (true) {
                current = consume();
                if (Character.isDigit(current) || current == '.' || current == 'E') {
                    if (current == '.') {
                        tok.type = Token.TokenType.DOUBLE;
                    }
                    buf.append(current);
                } else {
                    putBackChar();
                    break;
                }
            }
            tok.content = buf.toString();
            tok.type = Token.TokenType.DOUBLE;
            return (tok);
        }else if (current == '+'){
            tok.content = "+";
            tok.type = Token.TokenType.PLUS;
            return(tok);
        }

        return (new Token());
    }

    public Expression getNextExpression() {
        Token tok;
        ArrayList<Expression> exprs = new ArrayList<Expression>();
        tok = getNextToken();
        if (tok.type == Token.TokenType.LPARAN){
            return getNextExpression();
        }else if (tok.type == Token.TokenType.RPARAN){
            return (null);
        }else if (tok.type == Token.TokenType.DOUBLE){
            DoubleExpression dexpr = new DoubleExpression(Double.parseDouble(tok.content));
            return(dexpr);
        }else if (tok.type == Token.TokenType.PLUS){
            while(true){
                Expression e = getNextExpression();
                if (e == null){
                     return (new PlusExpression(exprs));
                }
                exprs.add(e);
            }
        }
        System.out.println("Exiting getNextExpression");
        return(null);
    }
}
