/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2015 Mehmet Hakan Satman <mhsatman@yahoo.com>
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

import java.net.URLClassLoader;
import java.util.ArrayList;
import java.net.URL;


public class FuzuliClassLoader {
   
    public static URLClassLoader urlClassLoader = null;
    private static ArrayList<URL> jarfiles = new ArrayList<URL>();
    
    public static void prepareClassLoader(){
        URL[] urls = new URL[jarfiles.size()];
        urls = jarfiles.toArray(urls);
        urlClassLoader = new URLClassLoader(urls);
    }
    
    public static void addJarFile(String url){
        try{
            jarfiles.add(new URL(url));
            //System.out.println("Added jars: "+jarfiles.toString());
        }catch (Exception e){
            throw new FuzuliException(e, "Cannot add Jar file "+url);
        }
    }
    
    public static Class loadClass(String className){
        prepareClassLoader();
        Class c = null;
        try {
            c = urlClassLoader.loadClass(className);
        } catch (ClassNotFoundException ex) {
            throw new FuzuliException(ex, "Cannot load class "+className);
        }
        return(c);
    }
    
    
}
