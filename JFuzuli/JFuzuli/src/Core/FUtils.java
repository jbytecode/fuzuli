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
package Core;

import Interpreter.Environment;
import java.util.ArrayList;
import java.util.Collections;

public class FUtils {

    public static ArrayList sorta(ArrayList obj, Environment env) {
        ArrayList al = (ArrayList) obj.clone();
        Collections.sort(al);
        return (al);
    }

    public static ArrayList sortd(ArrayList obj, Environment env) {
        ArrayList al = (ArrayList) obj.clone();
        Collections.sort(al, Collections.reverseOrder());
        return (al);
    }

    public static ArrayList shuffle(ArrayList obj, Environment env) {
        ArrayList al = (ArrayList) obj.clone();
        Collections.shuffle(al);
        return (al);
    }

    public static boolean detectClass(String className) {
        Class c = null;
        try {
            c = Class.forName(className);
        } catch (Exception e) {

        }
        if (c == null) {
            return (false);
        }
        return (true);
    }
}
