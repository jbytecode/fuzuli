package org.expr.plang;

import java.util.ArrayList;
import java.util.List;
import org.expr.plang.exception.EndOfProgramException;

public class Parser {

    List<Token> tokens;
    int currentIndex;

    public Parser(List<Token> tokens) {
        this.tokens = tokens;
        this.currentIndex = 0;
    }

    public Token consumeToken() {
        if (currentIndex < tokens.size()) {
            Token tok = tokens.get(currentIndex);
            currentIndex++;
            return tok;
        } else {
            return new Token("", Token.TOKEN_ENDPROGRAM);
        }
    }

    public Token getPreviousToken() {
        if (currentIndex > 1) {
            return (this.tokens.get(currentIndex - 2));
        } else {
            return (null);
        }
    }

    public ArrayList<Expression> parseAll() {
        ArrayList<Expression> exprs = new ArrayList<>();
        while (true) {
            try {
                Expression expr = getExpression();
                exprs.add(expr);
            } catch (EndOfProgramException eope) {
                break;
            }
        }
        return exprs;
    }

    public ArrayList<Expression> getExpressionList() {
        ArrayList<Expression> exprs = new ArrayList<>();
        while (true) {
            Expression expr = getExpression();
            if (expr == null) {
                break;
            }
            exprs.add(expr);
        }
        return exprs;
    }

    public Expression getExpression() {
        Token currentToken = consumeToken();
        Expression left = null;
        Expression right = null;
        if (currentToken.tokentype != Token.TOKEN_IDENTIFIER) {
            switch (currentToken.tokentype) {
                case Token.TOKEN_LPARANT:
                    return getExpression();
                case Token.TOKEN_ENDPROGRAM:
                    throw new EndOfProgramException();
                case Token.TOKEN_RPARANT:
                    return null;
                case Token.TOKEN_PLUS:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new PlusExpression(left, right);
                case Token.TOKEN_MINUS:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new MinusExpression(left, right);
                case Token.TOKEN_ASTERIX:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new ProductExpression(left, right);
                case Token.TOKEN_INTEGER:
                    return new IntegerConstantExpression(Integer.parseInt(currentToken.content));
                case Token.TOKEN_DOUBLE:
                    return new DoubleConstantExpression(Double.parseDouble(currentToken.content));
                case Token.TOKEN_STRING:
                    return new StringConstantExpression(currentToken.content);
                case Token.TOKEN_LESS:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new LessThanExpression(left, right);
                case Token.TOKEN_GREATER:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new GreaterThanExpression(left, right);
                case Token.TOKEN_EQUAL:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new EqualExpression(left, right);
                case Token.TOKEN_TWOPOINTS:
                    left = getExpression();
                    right = getExpression();
                    consumeToken();
                    return new RangeExpression(left, right);
            }
        } else if (currentToken.tokentype == Token.TOKEN_IDENTIFIER) {
            if (currentToken.content.equals("true")) {
                return new BooleanConstantExpression(true);
            } else if (currentToken.content.equals("false")) {
                return new BooleanConstantExpression(false);
            } else if (currentToken.content.equals("def")) {
                left = getExpression();
                right = getExpression();
                consumeToken();
                return new DefExpression(left, right);
            } else if (currentToken.content.equals("ifelse")) {
                Expression condition = getExpression();
                Expression ifTrue = getExpression();
                Expression ifNotTrue = getExpression();
                consumeToken();
                return new IfElseExpression(condition, ifTrue, ifNotTrue);
            } else if (currentToken.content.equals("cond")) {
                List<Expression> exprs = getExpressionList();
                return new CondExpression(exprs);
            } else if (currentToken.content.equals("list")) {
                List<Expression> exprs = getExpressionList();
                return new ListExpression(exprs);
            } else if (currentToken.content.equals("println")) {
                List<Expression> exprs = getExpressionList();
                return new PrintlnExpression(exprs);
            } else if (currentToken.content.equals("function")) {
                Expression params = getExpression();
                Expression body = getExpression();
                consumeToken();
                return new FunctionExpression(params, body);
            } else if (currentToken.content.equals("head")) {
                Expression param = getExpression();
                consumeToken();
                return new HeadExpression(param);
            } else if (currentToken.content.equals("rest")) {
                Expression param = getExpression();
                consumeToken();
                return new RestExpression(param);
            } else if (currentToken.content.equals("len")) {
                Expression param = getExpression();
                consumeToken();
                return new LenExpression(param);
            } else if (currentToken.content.equals("append")) {
                Expression paramList = getExpression();
                Expression paramElement = getExpression();
                consumeToken();
                return new AppendExpression(paramList, paramElement);
            } else if (currentToken.content.equals("prepend")) {
                Expression paramList = getExpression();
                Expression paramElement = getExpression();
                consumeToken();
                return new PrependExpression(paramList, paramElement);
            } else if (currentToken.content.equals("assert")) {
                Expression param = getExpression();
                consumeToken();
                return new AssertExpression(param);
            } else if (currentToken.content.equals("apply")) {
                Expression func = getExpression();
                Expression list = getExpression();
                consumeToken();
                return new ApplyExpression(func, list);
            } else if (currentToken.content.equals("javastatic")) {
                Expression name = getExpression();
                Expression params = getExpression();
                consumeToken();
                return new JavaStaticExpression(name, params);
            } else if (currentToken.content.equals("with")) {
                left = getExpression();
                right = getExpression();
                consumeToken();
                return new WithExpression(left, right);
            } else if (currentToken.content.equals("let")) {
                left = getExpression();
                right = getExpression();
                consumeToken();
                return new LetExpression(left, right);
            } else if (currentToken.content.equals("byte")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.ByteCastExpression(param);
            } else if (currentToken.content.equals("int")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.IntegerCastExpression(param);
            } else if (currentToken.content.equals("float")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.FloatCastExpression(param);
            } else if (currentToken.content.equals("double")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.DoubleCastExpression(param);
            } else if (currentToken.content.equals("short")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.ShortCastExpression(param);
            } else if (currentToken.content.equals("long")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.LongCastExpression(param);
            } else if (currentToken.content.equals("char")) {
                Expression param = getExpression();
                consumeToken();
                return TypeCastExpression.CharCastExpression(param);
            } else if (currentToken.content.equals("nth")) {
                Expression list = getExpression();
                Expression n = getExpression();
                consumeToken();
                return new NthExpression(list, n);
            } else if (currentToken.content.equals("expression")) {
                Expression param = getExpression();
                consumeToken();
                return new ExpressionExpression(param);
            } else if (currentToken.content.equals("eval")) {
                Expression param = getExpression();
                consumeToken();
                return new EvalExpression(param);
            } else if (currentToken.content.equals("random")) {
                consumeToken();
                return MathExpression.RandomExpression();
            } else if (currentToken.content.equals("sqrt")) {
                Expression param = getExpression();
                consumeToken();
                return MathExpression.SqrtExpression(param);
            } else if (currentToken.content.equals("log")) {
                Expression param = getExpression();
                consumeToken();
                return MathExpression.LogExpression(param);
            } else if (currentToken.content.equals("exp")) {
                Expression param = getExpression();
                consumeToken();
                return MathExpression.ExpExpression(param);
            } else if (currentToken.content.equals("pow")) {
                Expression base = getExpression();
                Expression power = getExpression();
                consumeToken();
                return MathExpression.PowExpression(base, power);
            } else {
                Token prev = getPreviousToken();
                if (prev.content.equals("(")) {
                    List<Expression> params = getExpressionList();
                    // consumeToken();
                    return new FunctionCallExpression(currentToken.content, params);
                }
                return new IdentifierExpression(currentToken.content);
            }
        } else {
            throw new RuntimeException("I dont understand: " + currentToken.content);
            //return getExpression();
        }
        return null;
    }
}
