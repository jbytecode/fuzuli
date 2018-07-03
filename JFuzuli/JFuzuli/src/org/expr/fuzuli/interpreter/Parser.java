/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2013 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package org.expr.fuzuli.interpreter;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

/**
 *
 * @author hako
 */
public class Parser {

    String sourcecode;
    int charIndex;
    int tokenIndex;
    ArrayList<Token> tokens;
    int lineNumber = 0;

    public Parser(String code) {
        this.sourcecode = code;
        resetParser();
    }

    public String getSourceCode() {
        return (this.sourcecode);
    }

    public void setSourceCode(String s) {
        this.sourcecode = s;
    }

    private void read(BufferedReader reader) throws Exception {
        StringBuilder code = new StringBuilder();

        char[] chars = new char[1024];
        int result;
        while (true) {
            result = reader.read(chars);
            if (result == -1) {
                break;
            }
            code.append(chars, 0, result);
            for (int i = 0; i < chars.length; i++) {
                chars[i] = '\0';
            }
        }
        code.append("\n");
        this.sourcecode = code.toString();
    }

    private void read2(File file) throws Exception {
        FileInputStream fis = new FileInputStream(file);
        int len = (int) file.length();
        byte[] data = new byte[len + 1];
        fis.read(data);
        fis.close();
        data[len] = '\n';
        this.sourcecode = new String(data, "UTF-8");
        data = null;
    }

    public Parser(File file) {
        try {
            this.read2(file);
        } catch (Exception e) {
            System.out.println("Error reading file:" + file.toString());
            e.printStackTrace();
        }
        resetParser();
    }

    public Parser(InputStream is) {
        StringBuilder code = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            this.read(reader);
        } catch (Exception e) {
            System.out.println("Error reading stream:" + is.toString());
            e.printStackTrace();
        }
        resetParser();
    }

    public void resetParser() {
        charIndex = 0;
        tokenIndex = 0;
        tokens = new ArrayList<Token>();
        lineNumber = 0;
        readAllTokens();
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

    public char looknext() {
        if ((charIndex + 1) != sourcecode.length()) {
            return (this.sourcecode.charAt(charIndex + 1));
        } else {
            return ('\0');
        }
    }

    public void readAllTokens() {
        while (true) {
            Token tok = parseNextToken();
            this.tokens.add(tok);
            if (tok.type == Token.TokenType.EOP) {
                break;
            }
        }
    }

    public Token parseNextToken() {
        StringBuilder buf = new StringBuilder();
        Token tok = new Token();
        char current;
        current = consume();
        if (current == '\0') {
            tok.type = Token.TokenType.EOP;
            tok.content = "End of Program";
            return (tok);
        } else if (current == ' ' || current == '\t' || current == '\n' || current == '\r' || Character.isSpaceChar(current)) {
            if (current == '\n') {
                lineNumber++;
            }
            return (parseNextToken());
        } else if (current == '#') {
            while (true) {
                current = consume();
                if (current == '\n') {
                    lineNumber++;
                    break;
                }
            }
            return (parseNextToken());
        } else if (current == '(') {
            tok.content = "(";
            tok.type = Token.TokenType.LPARAN;
            return (tok);
        } else if (current == ')') {
            tok.content = ")";
            tok.type = Token.TokenType.RPARAN;
            return (tok);
        } else if (Character.isDigit(current)) {
            if (current == '0') {
                char next = consume();
                if (next == 'x') {
                    while (true) {
                        current = consume();
                        if (Character.isDigit(current) || (current >= 'a' && current <= 'f') || (current >= 'A' && current <= 'F')) {
                            buf.append(current);
                        } else {
                            break;
                        }
                    }
                    putBackChar();
                    tok.content = String.valueOf(Long.parseLong(buf.toString(), 16));
                    tok.type = Token.TokenType.LONG;
                    return (tok);
                } else {
                    putBackChar();
                }
            }
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
            if (!tok.content.contains(".")) {
                tok.type = Token.TokenType.LONG;
            }
            return (tok);
        } else if (current == '+') {
            char next = consume();
            if (next == '+') {
                tok.content = "++";
                tok.type = Token.TokenType.PLUSPLUS;
                return (tok);
            }
            putBackChar();
            tok.content = "+";
            tok.type = Token.TokenType.PLUS;
            return (tok);
        } else if (current == '-') {
            char next = consume();
            if (Character.isDigit(next)) {
                putBackChar();
                Token t = this.parseNextToken();
                buf.append("-");
                buf.append(t.content);
                tok.content = buf.toString();
                tok.type = Token.TokenType.DOUBLE;
                return (tok);
            } else if (next == '-') {
                tok.content = "--";
                tok.type = Token.TokenType.MINUSMINUS;
                return (tok);
            }
            putBackChar();
            tok.content = "-";
            tok.type = Token.TokenType.MINUS;
            return (tok);
        } else if (current == '/') {
            char next = consume();
            if (next == '/') {
                while (true) {
                    char c = consume();
                    if (c == '\n') {
                        return (parseNextToken());
                    }
                }
            } else if (next == '*') {
                while (true) {
                    char c1 = consume();
                    char c2 = consume();
                    if (c1 == '*' && c2 == '/') {
                        return (parseNextToken());
                    }
                    putBackChar();
                }
            }
            putBackChar();
            tok.content = "/";
            tok.type = Token.TokenType.DIVISION;
            return (tok);
        } else if (current == '*') {
            tok.content = "*";
            tok.type = Token.TokenType.ASTERIX;
            return (tok);
        } else if (current == '=') {
            tok.content = "=";
            tok.type = Token.TokenType.EQUALS;
            return (tok);
        } else if (current == '<') {
            char next = consume();
            if (next == '<') {
                tok.content = "<<";
                tok.type = Token.TokenType.BITSHIFTLEFT;
                return (tok);
            } else if (next == '=') {
                tok.content = "<=";
                tok.type = Token.TokenType.LESSOREQUAL;
                return (tok);
            } else if (next == '?') {
                StringBuilder sb = new StringBuilder();
                while (looknext() != '\n') {
                    sb.append(consume());
                }
                consume();
                if (sb.substring(0, 10).equals("javascript")) {
                    StringBuilder jscode = new StringBuilder();
                    while (true) {
                        if (jscode.length() > 2) {
                            if (jscode.toString().endsWith("?>")) {
                                break;
                            }
                        }
                        jscode.append(consume());
                        //System.out.println(jscode);
                    }
                    String jsfinalcode = jscode.substring(0, jscode.length() - 2);
                    tok.content = jsfinalcode;
                    tok.type = Token.TokenType.JSCODE;
                    return (tok);
                }
            } else {
                putBackChar();
            }
            tok.content = "<";
            tok.type = Token.TokenType.LESS;
            return (tok);
        } else if (current == '>') {
            char next = consume();
            if (next == '>') {
                tok.content = ">>";
                tok.type = Token.TokenType.BITSHIFTRIGHT;
                return (tok);
            } else if (next == '=') {
                tok.content = ">=";
                tok.type = Token.TokenType.BIGGEROREQUAL;
                return (tok);
            } else {
                putBackChar();
            }
            tok.content = ">";
            tok.type = Token.TokenType.BIGGER;
            return (tok);
        } else if (current == '&') {
            tok.content = "&";
            tok.type = Token.TokenType.BITAND;
            return (tok);
        } else if (current == '|') {
            tok.content = "|";
            tok.type = Token.TokenType.BITOR;
            return (tok);
        } else if (current == '~') {
            tok.content = "~";
            tok.type = Token.TokenType.BITNOT;
            return (tok);
        } else if (current == '^') {
            tok.content = "^";
            tok.type = Token.TokenType.BITXOR;
            return (tok);
        } else if (current == ':') {
            tok.content = ":";
            tok.type = Token.TokenType.COLON;
            return (tok);
        } else if (current == '!') {
            buf.append(current);
            current = consume();
            if (current == '=') {
                buf.append(current);
                tok.content = buf.toString();
                tok.type = Token.TokenType.NOTEQUAL;
                return (tok);
            } else {
                putBackChar();
            }
            tok.content = "!";
            tok.type = Token.TokenType.EXCLAMATION;
            return (tok);
        } else if (Character.isLetter(current)) {
            buf.append(current);
            while (true) {
                current = consume();
                if (!Character.isLetter(current) && !Character.isDigit(current) && current != '_' && current != '.') {
                    putBackChar();
                    break;
                }
                buf.append(current);
            }
            tok.content = buf.toString();
            tok.type = Token.TokenType.IDENTIFIER;
            return (tok);
        } else if (current == '"') {
            while (true) {
                current = consume();
                if (current == '\\') {
                    current = consume();
                    if (current == 'n') {
                        buf.append("\n");
                    } else {
                        buf.append(current);
                    }
                } else if (current == '"') {
                    break;
                } else {
                    buf.append(current);
                }
            }
            tok.type = Token.TokenType.STRING;
            tok.content = buf.toString();
            return (tok);
        } else if (current == '\'') {
            tok.content = "'";
            tok.type = Token.TokenType.SINGLEQUOTE;
            return (tok);
        }

        throw new RuntimeException("Unknow character: '" + current + "'");
    }

    public ArrayList<Expression> getExpressionList() {
        ArrayList<Expression> exprs = new ArrayList<Expression>();
        Expression e;
        while (true) {
            e = getNextExpression();
            if (e == null) {
                break;
            }
            exprs.add(e);
        }
        return (exprs);
    }

    public Token getNextToken() {
        Token tok = this.tokens.get(tokenIndex);
        tokenIndex++;
        return (tok);
    }

    public Token getPreviousToken() {
        if (tokenIndex > 1) {
            return (this.tokens.get(tokenIndex - 2));
        } else {
            return (null);
        }
    }

    public Expression getNextExpression() {
        Token tok;
        ConstantDoubleNumberExpression dexpr;
        ConstantIntegerNumberExpression iexpr;
        ArrayList<Expression> exprs = null;
        tok = getNextToken();
        if (tok.type != Token.TokenType.IDENTIFIER) {
            switch (tok.type) {
                case EOP:
                    return (null);
                case LPARAN:
                    return getNextExpression();
                case RPARAN:
                    return (null);
                case DOUBLE:
                    dexpr = new ConstantDoubleNumberExpression(Double.parseDouble(tok.content));
                    return (dexpr);
                case LONG:
                    iexpr = new ConstantIntegerNumberExpression(Long.parseLong(tok.content));
                    return (iexpr);
                case PLUS:
                    exprs = getExpressionList();
                    return (new PlusExpression(exprs));
                case MINUS:
                    exprs = getExpressionList();
                    return (new MinusExpression(exprs));
                case DIVISION:
                    exprs = getExpressionList();
                    return (new DivisionExpression(exprs));
                case ASTERIX:
                    exprs = getExpressionList();
                    return (new AsterixExpression(exprs));
                case EQUALS:
                    exprs = getExpressionList();
                    return (new EqualsExpression(exprs));
                case NOTEQUAL:
                    exprs = getExpressionList();
                    return (new NotEqualsExpression(exprs));
                case LESS:
                    exprs = getExpressionList();
                    return (new LessExpression(exprs));
                case BIGGER:
                    exprs = getExpressionList();
                    return (new BiggerExpression(exprs));
                case BIGGEROREQUAL:
                    exprs = getExpressionList();
                    return (new BiggerOrEqualExpression(exprs));
                case LESSOREQUAL:
                    exprs = getExpressionList();
                    return (new LessOrEqualExpression(exprs));
                case EXCLAMATION:
                    exprs = getExpressionList();
                    return (new BitNotExpression(exprs));
                case BITAND:
                    exprs = getExpressionList();
                    return (new BitAndExpression(exprs));
                case BITOR:
                    exprs = getExpressionList();
                    return (new BitOrExpression(exprs));
                case BITNOT:
                    exprs = getExpressionList();
                    return (new BitNotExpression(exprs));
                case BITXOR:
                    exprs = getExpressionList();
                    return (new BitXorExpression(exprs));
                case BITSHIFTLEFT:
                    exprs = getExpressionList();
                    return (new BitShiftLeftExpression(exprs));
                case BITSHIFTRIGHT:
                    exprs = getExpressionList();
                    return (new BitShiftRightExpression(exprs));
                case COLON:
                    exprs = getExpressionList();
                    return (new ColonExpression(exprs));
                case PLUSPLUS:
                    exprs = getExpressionList();
                    return (new IncExpression(exprs));
                case MINUSMINUS:
                    exprs = getExpressionList();
                    return (new DecExpression(exprs));
                case JSCODE:
                    ArrayList<Expression> arrlist = new ArrayList<Expression>();
                    arrlist.add(new StringExpression(tok.content));
                    return (new JavascriptExpression(arrlist));
                case STRING:
                    return (new StringExpression(tok.content));
                case SINGLEQUOTE:
                    getNextToken(); // This is opening paranthesis.
                    exprs = getExpressionList();
                    return (new ListExpression(exprs));
                default:
                //NOP
            }

        } else if (tok.type == Token.TokenType.IDENTIFIER) {
            switch (tok.content) {
                case "print":
                    exprs = getExpressionList();
                    return (new PrintExpression(exprs));
                case "println":
                    exprs = getExpressionList();
                    return (new PrintlnExpression(exprs));
                case "and":
                    exprs = getExpressionList();
                    return (new AndExpression(exprs));
                case "or":
                    exprs = getExpressionList();
                    return (new OrExpression(exprs));
                case "let":
                    exprs = getExpressionList();
                    return (new LetExpression(exprs));
                case "if":
                    exprs = getExpressionList();
                    return (new IfExpression(exprs));
                case "switch":
                    exprs = getExpressionList();
                    return (new SwitchExpression(exprs));
                case "case":
                    exprs = getExpressionList();
                    return (new CaseExpression(exprs));
                case "block":
                    exprs = getExpressionList();
                    return (new BlockExpression(exprs));
                case "setepsilon":
                    exprs = getExpressionList();
                    return (new SetEpsilonExpression(exprs));
                case "typeof":
                    exprs = getExpressionList();
                    return (new TypeOfExpression(exprs));
                case "for":
                    exprs = getExpressionList();
                    return (new ForExpression(exprs));
                    
                case "foreach":
                    exprs = getExpressionList();
                    return (new ForEachExpression(exprs));
                case "while":
                    exprs = getExpressionList();
                    return (new WhileExpression(exprs));
                case "break":
                    exprs = getExpressionList();
                    return (new BreakExpression(exprs));
                case "def":
                    exprs = getExpressionList();
                    return (new DefExpression(exprs));
                case "inc":
                    exprs = getExpressionList();
                    return (new IncExpression(exprs));
                case "dec":
                    exprs = getExpressionList();
                    return (new DecExpression(exprs));
                case "list":
                    exprs = getExpressionList();
                    return (new ListExpression(exprs));
                case "nth":
                    exprs = getExpressionList();
                    return (new NthExpression(exprs));
                case "length":
                    exprs = getExpressionList();
                    return (new LengthExpression(exprs));
                case "set":
                    exprs = getExpressionList();
                    return (new SetExpression(exprs));
                case "remove":
                    exprs = getExpressionList();
                    return (new RemoveExpression(exprs));
                case "find":
                    exprs = getExpressionList();
                    return (new FindExpression(exprs));
                case "append":
                    exprs = getExpressionList();
                    return (new AppendExpression(exprs));
                case "prepend":
                    exprs = getExpressionList();
                    return (new PrependExpression(exprs));
                case "fill":
                    exprs = getExpressionList();
                    return (new FillExpression(exprs));
                case "setprecision":
                    exprs = getExpressionList();
                    return (new SetPrecisionExpression(exprs));
                case "function":
                    exprs = getExpressionList();
                    return (new FunctionExpression(exprs));
                case "params":
                    exprs = getExpressionList();
                    return (new ParamsExpression(exprs));
                case "return":
                    exprs = getExpressionList();
                    return (new ReturnExpression(exprs));
                case "timing":
                    exprs = getExpressionList();
                    return (new TimingExpression(exprs));
                case "require":
                    exprs = getExpressionList();
                    return (new RequireExpression(exprs));
                case "dynload":
                    exprs = getExpressionList();
                    return (new DynLoadExpression(exprs));
                case "internal":
                    exprs = getExpressionList();
                    return (new InternalExpression(exprs));
                case "javastatic":
                    exprs = getExpressionList();
                    return (new JavaStaticExpression(exprs));
                case "javanew":
                    exprs = getExpressionList();
                    return (new JavaNewExpression(exprs));
                case "javacall":
                    exprs = getExpressionList();
                    return (new JavaCallExpression(exprs));
                case "explode":
                    exprs = getExpressionList();
                    return (new ExplodeExpression(exprs));
                case "eval":
                    exprs = getExpressionList();
                    return (new EvalExpression(exprs));
                case "expression":
                    exprs = getExpressionList();
                    return (new ExpressionExpression(exprs));
                case "trycatch":
                    exprs = getExpressionList();
                    return (new TryCatchExpression(exprs));
                case "dotimes":
                    exprs = getExpressionList();
                    return (new DoTimesExpression(exprs));
                case "gc":
                    exprs = getExpressionList();
                    return (new GcExpression(exprs));
                case "dump":
                    exprs = getExpressionList();
                    return (new DumpExpression(exprs));
                case "jint":
                    exprs = getExpressionList();
                    return (new JintExpression(exprs));
                case "loadjar":
                    exprs = getExpressionList();
                    return (new LoadJarExpression(exprs));
                case "class":
                    exprs = getExpressionList();
                    return(new ClassExpression(exprs));
                case "new":
                    exprs = getExpressionList();
                    return(new NewExpression(exprs));
                case "apply":
                    exprs = getExpressionList();
                    return(new ApplyExpression(exprs));
                default:
                    String fname = tok.content;
                    if (this.getPreviousToken().type == Token.TokenType.LPARAN) {
                        exprs = getExpressionList();
                        //System.out.println("Function call to "+fname+" with "+exprs.toString());
                        FunctionCallExpression fce = new FunctionCallExpression(exprs);
                        fce.fname = fname;
                        return (fce);
                    } else {
                        return (new IdentifierExpression(tok.content));
                    }
            }
        }
        throw new RuntimeException("Can not understand '" + tok.content + "'");
    }
}
