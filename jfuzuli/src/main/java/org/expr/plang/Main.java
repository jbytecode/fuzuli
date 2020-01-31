package org.expr.plang;

public class Main {

    public static void main(String[] args) {
        new Main(args);
    }

    public void Help() {
        System.out.println("Fuzuli, A Lispy language that transpiles to JavaScript");
        System.out.println("Usage: ");
        System.out.println("[Runnable] input.fzl");
    }

    public Main(String[] args) {
        Environment env = new Environment();
        if (args.length == 0) {
            Help();
        } else if (args.length == 1) {
            String filename = args[0];
            String code = Interpreter.loadCodeFromFile(filename);
            String jscode = Interpreter.emitJS(code);
            System.out.println(jscode);
        }
    }

}
