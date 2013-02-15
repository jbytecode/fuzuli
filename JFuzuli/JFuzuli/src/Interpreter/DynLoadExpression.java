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
import java.util.logging.Level;
import java.util.logging.Logger;

public class DynLoadExpression extends Expression {

    public DynLoadExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment e) {
        String str = this.exprs.get(0).eval(e).toString();
        String cls = this.exprs.get(1).eval(e).toString();
        URL u = null;
        Class c = null;
        try {
            u = new URL(str);
        } catch (Exception ee) {
            throw new FuzuliException(ee, "DynLoad can not load library "+str);
        }
        URLClassLoader l = URLClassLoader.newInstance(new URL[]{u});
        try {
            c = l.loadClass(cls);
        } catch (ClassNotFoundException ex) {
            throw new FuzuliException(ex, "Dynload can not load class "+cls+" from library "+str);
        }
        return (c);
    }
}
