package org.expr.plang;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class Interpreter {

    public final static Object interpreteFromString(String code, Environment env) {
        Lexer lexer = new Lexer(code);
        Parser parser = new Parser(lexer.consomeAllTokens());
        List<Expression> exprs = parser.parseAll();
        final ObjectEncapsulator result = new ObjectEncapsulator(null);
        exprs.forEach(new Consumer<Expression>() {
            @Override
            public void accept(Expression expr) {
                result.setObject(expr.eval(env));
            }
        });
        return result.getObject();
    }
    
    public final static String emitJS(String code){
        Lexer lexer = new Lexer(code);
        Parser parser = new Parser(lexer.consomeAllTokens());
        List<Expression> exprs = parser.parseAll();
        final StringBuilder jscode = new StringBuilder();
        exprs.forEach(e -> jscode.append(e.emitJS()));
        return jscode.toString();
    }

    public final static String loadCodeFromFile(String file) {
        StringBuilder s = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(new File(file)));
            while (true) {
                String line = reader.readLine();
                if (line == null) {
                    break;
                }
                s.append(line);
                s.append("\n");
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException("Error reading file " + file + ": " + e.toString());
        }
        return s.toString();
    }

    public final static String loadCodeFromInputStream(InputStream is) {
        StringBuilder s = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            while (true) {
                String line = reader.readLine();
                if (line == null) {
                    break;
                }
                s.append(line);
                s.append("\n");
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException("Error reading inputstream " + is.toString() + ": " + e.toString());
        }
        return s.toString();
    }

    public final static Object interpreteFromFile(String file, Environment env) {
        Lexer lexer = new Lexer(loadCodeFromFile(file));
        Parser parser = new Parser(lexer.consomeAllTokens());
        List<Expression> exprs = parser.parseAll();
        final ObjectEncapsulator result = new ObjectEncapsulator(null);
        exprs.forEach(new Consumer<Expression>() {
            @Override
            public void accept(Expression expr) {
                result.setObject(expr.eval(env));
            }
        });
        return result.getObject();
    }

    public final static Object interpreteFromInputStream(InputStream is, Environment env) {
        Lexer lexer = new Lexer(loadCodeFromInputStream(is));
        Parser parser = new Parser(lexer.consomeAllTokens());
        List<Expression> exprs = parser.parseAll();
        final ObjectEncapsulator result = new ObjectEncapsulator(null);
        exprs.forEach(new Consumer<Expression>() {
            @Override
            public void accept(Expression expr) {
                result.setObject(expr.eval(env));
            }
        });
        return result.getObject();
    }

}
