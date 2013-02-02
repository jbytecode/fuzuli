/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Interpreter;

/**
 *
 * @author hako
 */
public class Token {
    String content;
    TokenType type;
    
    enum TokenType {
        INTEGER,
        DOUBLE,
        PLUS,
        LPARAN,
        RPARAN,
        OBJECT,
        EOP
    }
}

