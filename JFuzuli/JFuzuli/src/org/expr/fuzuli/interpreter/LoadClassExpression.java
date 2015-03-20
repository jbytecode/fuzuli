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

import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.logging.Level;
import java.util.logging.Logger;


public class LoadClassExpression extends Expression{

    public LoadClassExpression(ArrayList<Expression> exprs){
        this.exprs = exprs;
    }
    
    @Override
    public Object eval(Environment e) {
        FuzuliClassLoader loader = new FuzuliClassLoader();
        String jarFileName = exprs.get(0).eval(e).toString();
        String classname = exprs.get(1).eval(e).toString();
        Class result = null; 
        try {
            //loader.addJarFile(new URL(jarFileName));
            FuzuliClassLoader.addURL2(new URL(jarFileName)); 
        } catch (Exception ex) {
            throw new FuzuliException(ex, "Jar file "+jarFileName+" cannot be loaded");
        }
        try {
            //result = Class.forName(classname, true, loader);
            result = loader.FindLoadedClass(classname);
        } catch (ClassNotFoundException ex) {
            throw new FuzuliException(ex, "Class "+classname+" cannot be loaded");
        }
        return(result);
    }
    
}
