
package Compiler;

import Interpreter.Expression;
import Interpreter.Parser;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.util.jar.JarOutputStream;
import java.util.zip.ZipEntry;


public class Main {
    
    public byte[] getBytes (Object o){
        try{
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(o);
            oos.flush();
            return baos.toByteArray();
        }catch (Exception e){
            System.out.println(e.toString());
        }
        return null;
    }
    
    public Main(String[] args){
        String filename = args[0];
        byte[] objectBytes;
        System.out.println("Compiling "+filename);

        File sourcefile = new File(filename);
        Parser parser = new Parser(sourcefile);
        FuzuliScheme scheme = new FuzuliScheme();
        
        parser.resetParser();
        scheme.reset();
        
        while(true){
            Expression exp = parser.getNextExpression();
            if (exp==null)break;
            scheme.expr.add(exp);
        }
       
        System.out.println("Converting "+filename + " to bytecode");
        objectBytes = getBytes(scheme);
        
        try{
            System.out.println("Creating dist.jar");
            JarOutputStream jar = new JarOutputStream(new FileOutputStream("dist.jar"));
            jar.putNextEntry(new ZipEntry("jbytecode.ser"));
            jar.write(objectBytes);
            jar.closeEntry();
            jar.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
    
    public static void main (String[] args){
        String newname;
        System.out.println("Fuzuli bytecode compiler 1.0");
        if(args.length < 1){
            System.out.println("Usage: ");
            System.out.println("java -jar JFuzuli.jar Compiler.Main fzlfile");
            System.exit(0);
        }
        new Main(args);
    }
}
