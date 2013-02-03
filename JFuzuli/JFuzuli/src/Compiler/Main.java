
package Compiler;

import Interpreter.Expression;
import Interpreter.Parser;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.jar.JarOutputStream;
import java.util.zip.ZipEntry;


public class Main {
    
   
    public byte[] getBytesOfClass (String classurl){
        try{
            String t=this.getClass().getResource(classurl).toString();
            System.out.println(t);
            InputStream is = this.getClass().getResourceAsStream(classurl);
           
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            OutputStreamWriter writer = new OutputStreamWriter(baos);
            while(true){
                int b = is.read();
                if (b == -1 )break;
                writer.write((byte)b);
            }
            writer.flush();
            byte[] bytes =baos.toByteArray();
            bytes[0] = (byte)0xCA;
            bytes[1] = (byte)0xFE;
            bytes[2] = (byte)0xBA;
            bytes[3] = (byte)0xBE;
            return(bytes);
   
        }catch (Exception e){
            System.out.println("Get Bytes of Class: "+e.toString());
        }
        return null;
    }
    
    public byte[] getBytes (Object o){
        try{
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(o);
            oos.flush();
            return(baos.toByteArray());
        }catch (Exception e){
            System.out.println("GetBytes:" + e.toString());
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
       
        //System.out.println("Converting "+filename + " to bytecode");
        objectBytes = getBytes(scheme);
        
        try{
            int dotindex = sourcefile.getName().lastIndexOf(".");
            String distname = sourcefile.getName().substring(0,dotindex)+".jar";
            System.out.println("Creating "+distname);
            JarOutputStream jar = new JarOutputStream(new FileOutputStream(distname));
            
            jar.putNextEntry(new ZipEntry("jbytecode.ser"));
            jar.write(objectBytes);
            jar.closeEntry();
            
            jar.putNextEntry(new ZipEntry("Compiler/"));
            jar.closeEntry();
            
            
            jar.putNextEntry(new ZipEntry("META-INF/"));
            jar.closeEntry();
            
            jar.putNextEntry(new ZipEntry("META-INF/MANIFEST.MF"));
            jar.write("Manifest-Version: 1.0\n".getBytes());
            jar.write("Main-Class: Compiler.SerRunner\n".getBytes());
            jar.write("Class-Path: JFuzuli.jar\n".getBytes());
            jar.closeEntry();
            
            jar.flush();
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
