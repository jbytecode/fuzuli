
package org.expr.fuzuli.interpreter;

import java.io.IOException;
import java.lang.reflect.Method;
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
     
      public Class FindLoadedClass(String clazz) throws ClassNotFoundException {
         return (super.findLoadedClass(clazz));
     }
      
      public static void addURL2(URL u) throws IOException {
            final Class[] parameters = new Class[] { URL.class };
            URLClassLoader sysloader =
                  (URLClassLoader) ClassLoader.getSystemClassLoader();
            Class sysclass = URLClassLoader.class;

            try {
                  Method method = sysclass.getDeclaredMethod("addURL", parameters);
                  method.setAccessible(true);
                  method.invoke(sysloader, new Object[] { u });
            } catch (Throwable t) {
                  t.printStackTrace();
                  throw new IOException("Error, could not add URL to system classloader");
            }

      }
}