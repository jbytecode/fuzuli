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

public class FMath {

    public static Double pi(Environment env) {
        return Math.PI;
    }

    public static double abs(FValue o, Environment env) {
        return Math.abs(o.getAsDouble());
    }

    public static double cos(FValue o, Environment env) {
        return Math.cos(o.getAsDouble());
    }

    public static double sin(FValue o, Environment env) {
        return Math.sin(o.getAsDouble());
    }

    public static double tan(FValue o, Environment env) {
        return Math.tan(o.getAsDouble());
    }

    public static double atan(FValue o, Environment env) {
        return Math.atan(o.getAsDouble());
    }

    public static double atan2(FValue o1, FValue o2, Environment env) {
        return Math.atan2(o1.getAsDouble(), o2.getAsDouble());
    }

    public static double exp(FValue o, Environment env) {
        return Math.exp(o.getAsDouble());
    }

    public static double log(FValue o, Environment env) {
        return Math.log(o.getAsDouble());
    }

    public static double log10(FValue o, Environment env) {
        return Math.log10(o.getAsDouble());
    }

    public static double log2(FValue o, Environment env) {
        double d = o.getAsDouble();
        return (Math.log10(d) / Math.log10(d));
    }

    public static double pow(FValue d, FValue p, Environment env) {
        return Math.pow(d.getAsDouble(), p.getAsDouble());
    }

    public static double isinf(FValue o, Environment env) {
        if (Double.isInfinite(o.getAsDouble())) {
            return 1.0;
        } else {
            return 0.0;
        }
    }

    public static double sqrt(FValue d, Environment env) {
        return Math.sqrt(d.getAsDouble());
    }

    public static double ceil(FValue d, Environment env) {
        return Math.ceil(d.getAsDouble());
    }

    public static double round(FValue d, Environment env) {
        return Math.round(d.getAsDouble());
    }

    public static double floor(FValue d, Environment env) {
        return Math.floor(d.getAsDouble());
    }
}
