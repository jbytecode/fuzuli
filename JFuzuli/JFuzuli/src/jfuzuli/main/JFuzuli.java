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

package jfuzuli.main;

import Interpreter.NumberExpression;
import Interpreter.Environment;
import Interpreter.Expression;
import Interpreter.FValue;
import Interpreter.Parser;
import java.io.File;

/**
 *
 * @author Mehmet Hakan Satman
 */
public class JFuzuli {

    public static void main(String[] args) {
        if (args.length == 1) {
            Parser parser = new Parser(new File(args[0]));
            Expression e = null;
            while (true) {
                try {
                    e = parser.getNextExpression();
                } catch (Exception exc) {
                    System.out.println("Parsing Error: " + exc.getMessage());
                    System.exit(-1);
                }

                if (e == null) {
                    break;
                }

                FValue o = null;
                try {
                    o = e.eval(new Environment(null));
                } catch (Exception exc) {
                    System.out.println("Runtime Error: " + exc.toString());
                }
            }

        }
    }
}
