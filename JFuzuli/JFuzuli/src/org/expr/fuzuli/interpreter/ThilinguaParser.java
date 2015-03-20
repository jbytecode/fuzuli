package org.expr.fuzuli.interpreter;

import java.io.File;
import java.io.InputStream;
import java.util.ArrayList;

public class ThilinguaParser extends Parser {

    public ThilinguaParser(String code) {
        super(code);
    }

    public ThilinguaParser(File file) {
        super(file);
    }

    public ThilinguaParser(InputStream is) {
        super(is);
    }

    public Expression getAssignmentExpression() {
        return (null);
    }

    @Override
    public Expression getNextExpression() {
        Expression expr = null;
        Token tok, tok1;

        tok = getNextToken();
        //System.out.println("Doing "+tok.content+" type is "+tok.type);
        if (tok.type == Token.TokenType.LPARAN){
            expr = getNextExpression();
            
        }else if (tok.type == Token.TokenType.RPARAN){
            return(expr);
        }else if (tok.type == Token.TokenType.INTEGER || tok.type == Token.TokenType.DOUBLE || tok.type == Token.TokenType.LONG) {
            NumberExpression n = new NumberExpression(FValue.getAsDouble(tok.content));
            Expression op = getNextExpression();
            if (op == null) {
                return (n);
            }
            Expression other = getNextExpression();
            op.exprs.add(n);
            op.exprs.add(other);
            System.out.println(op);
            return (op);
        } else if (tok.type == Token.TokenType.ASTERIX) {
            return (new AsterixExpression(new ArrayList<Expression>()));
        } else if (tok.type == Token.TokenType.DIVISION) {
            return (new DivisionExpression(new ArrayList<Expression>()));
        } else if (tok.type == Token.TokenType.PLUS) {
            return (new PlusExpression(new ArrayList<Expression>()));
        } else if (tok.type == Token.TokenType.MINUS) {
            return (new MinusExpression(new ArrayList<Expression>()));
        } else if (tok.type == Token.TokenType.EOP) {

        }

        return (expr);
    }

}
