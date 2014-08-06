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
import Interpreter.FValue;
import java.util.ArrayList;

public class FMath {

    public static Double pi(Environment env) {
        return Math.PI; 
    }

    public static double abs(Object o, Environment env) {
        return Math.abs(FValue.getAsDouble(o));
    }

    public static double cos(Object o, Environment env) {
        return Math.cos(FValue.getAsDouble(o));
    }

    public static double sin(Object o, Environment env) {
        return Math.sin(FValue.getAsDouble(o));
    }

    public static double tan(Object o, Environment env) {
        return Math.tan(FValue.getAsDouble(o));
    }

    public static double atan(Object o, Environment env) {
        return Math.atan(FValue.getAsDouble(o));
    }

    public static double atan2(Object o1, Object o2, Environment env) {
        return Math.atan2(FValue.getAsDouble(o1), FValue.getAsDouble(o2));
    }

    public static double exp(Object o, Environment env) {
        return Math.exp(FValue.getAsDouble(o));
    }

    public static double log(Object o, Environment env) {
        return Math.log(FValue.getAsDouble(o));
    }

    public static double log10(Object o, Environment env) {
        return Math.log10(FValue.getAsDouble(o));
    }

    public static double log2(Object o, Environment env) {
        double d = FValue.getAsDouble(o);
        return (Math.log10(d) / Math.log10(d));
    }

    public static double pow(Object d, Object p, Environment env) {
        return Math.pow(FValue.getAsDouble(d), FValue.getAsDouble(p));
    }

    public static double isinf(Object o, Environment env) {
        if (Double.isInfinite(FValue.getAsDouble(o))) {
            return 1.0;
        } else {
            return 0.0;
        }
    }

    public static double sqrt(Object d, Environment env) {
        return Math.sqrt(FValue.getAsDouble(d));
    }

    public static double ceil(Object d, Environment env) {
        return Math.ceil(FValue.getAsDouble(d));
    }

    public static double round(Object d, Environment env) {
        return Math.round(FValue.getAsDouble(d));
    }

    public static double floor(Object d, Environment env) {
        return Math.floor(FValue.getAsDouble(d));
    }

    public static double euclidean(Object l1, Object l2, Environment env) {
        ArrayList list1 = (ArrayList) l1;
        ArrayList list2 = (ArrayList) l2;
        double euc = 0.0;
        for (int i = 0; i < list1.size(); i++) {
            euc += Math.pow(FValue.getAsDouble(list1.get(i)) - FValue.getAsDouble(list2.get(i)), 2.0);
        }
        return (Math.sqrt(euc));
    }
}
