
package Interpreter;

import java.net.URL;
import java.net.URLClassLoader;

public class FuzuliClassLoader extends URLClassLoader {
    
     public FuzuliClassLoader() {
        super(new URL[]{}, ClassLoader.getSystemClassLoader());
    }
     
     public void addJarFile(URL file) {
        super.addURL(file); 
    } 
     
     public Class LoadClass(String clazz) throws ClassNotFoundException {
         return (super.loadClass(clazz));
     }
}