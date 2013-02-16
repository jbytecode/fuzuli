/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2013 Mehmet Hakan Satman <mhsatman@yahoo.com>
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
package Interpreter;

import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;

public class DynloadExpression extends Expression{

    FuzuliClassLoader classLoader;
    
    public DynloadExpression (ArrayList<Expression> exprs){
        this.exprs = exprs;
        this.classLoader = new FuzuliClassLoader();
    }
    
    @Override
    public Object eval(Environment e) {
        String surl = this.exprs.get(0).eval(e).toString();
        URL url = null;
        try{
            url = new URL(surl);
        }catch (Exception ex){
            throw new FuzuliException(ex, "Error loading jar "+surl);
        }
        classLoader.addJarFile(url);
        return(url); 
    }
    
}

