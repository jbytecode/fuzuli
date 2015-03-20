
package org.expr.fuzuli.compiler;

import java.io.ObjectInputStream;


public class SerRunner {
    
    public SerRunner(){
        try{
            ObjectInputStream ois = new ObjectInputStream(this.getClass().getResourceAsStream("/jbytecode.ser"));
            FuzuliScheme fs = (FuzuliScheme)ois.readObject();
            fs.run();
        }catch(Exception e){
            System.out.println(e.toString());
        }
    }
    
    public static void main(String[] args){
        new SerRunner();
    }
}
