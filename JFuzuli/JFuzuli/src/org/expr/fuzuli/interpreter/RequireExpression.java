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
package org.expr.fuzuli.interpreter;

import java.io.File;
import java.util.ArrayList;

public class RequireExpression extends Expression {

    public RequireExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment env) {
        String filename = String.valueOf(this.exprs.get(0).eval(env));
        Parser parser;
        if (filename.indexOf("/") != -1 || filename.indexOf("\\") != -1) {
            parser = new Parser(new File(filename));
        } else {
            parser = new Parser(this.getClass().getResourceAsStream("/nfl/" + filename));
        }
        Expression e = null;
        while (true) {
            try {
                e = parser.getNextExpression();
            } catch (Exception exc) {
                System.out.println("Parsing Error (" + filename + "): " + "Line Number: "+ parser.lineNumber+ ", "+exc.getMessage());
                exc.printStackTrace();
                System.exit(-1);
            }

            if (e == null) {
                break;
            }

            Object o = null;
            try {
                o = e.eval(env);
            } catch (Exception exc) {
                System.out.println("Runtime Error: " + exc.toString());
                exc.printStackTrace();
                System.exit(-1);
            }
        }
        return (FValue.ZERO);
    }
}
