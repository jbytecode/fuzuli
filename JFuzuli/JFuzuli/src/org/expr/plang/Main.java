package org.expr.plang;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.List;

public class Main {
	
	public static void main(String[] args) {
		new Main(args);
	}
	
	public void Repl() {
		System.out.println("Plang REPL");
	}
	
	public Main(String[] args) {
		Environment env = new Environment();
		if(args.length == 0) {
			Repl();
		}else {
			Interpreter.interpreteFromFile(args[0], env);
		}
	}
	
}
