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
import Interpreter.Expression;
import Interpreter.FValue;
import java.net.URLDecoder;
import java.util.ArrayList;
import java.security.*;
import java.util.Arrays;

public class FStrings {

    public static String ltrim(FValue o, Environment env) {
        String s = o.getObject().toString();
        StringBuilder sb = new StringBuilder();
        int i;
        for (i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ' ') {
                break;
            }
        }
        sb.append(s.substring(i + 1));
        return (sb.toString());
    }

    public static String rtrim(FValue o, Environment env) {
        String s = String.valueOf(o.getObject().toString());
        StringBuilder sb = new StringBuilder();
        int i;
        for (i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == ' ') {
                break;
            }
        }
        sb.append(s.substring(0, i));
        return (sb.toString());
    }

    public static String left(FValue o, FValue i, Environment env) {
        String s = String.valueOf(o);
        int index = (int) i.getAsDouble();
        return (s.substring(0, index));
    }

    public static String right(FValue o, FValue i, Environment env) {
        String s = String.valueOf(o);
        int index = (int) i.getAsDouble();
        return (s.substring(s.length() - index));
    }

    public static String strcat(FValue o, Environment env) {
        StringBuilder sb = new StringBuilder();
        ArrayList<Expression> a = (ArrayList<Expression>) o.getObject();
        for (int i = 0; i < a.size(); i++) {
            Expression exp = a.get(i);
            FValue result = exp.eval(env);
            sb.append(result.getObject().toString());
        }
        return sb.toString();
    }

    public static String substr(FValue o, FValue start, FValue end, Environment env) {
        String s = String.valueOf(o);
        int i1 = (int) start.getAsDouble();
        int i2 = (int) end.getAsDouble();
        return (s.substring(i1, i2));
    }

    public static String strreverse(FValue o, Environment env) {
        String s = String.valueOf(o);
        StringBuilder sb = new StringBuilder(s);
        return (sb.reverse().toString());
    }

    public static Double strlen(FValue o, Environment env) {
        String s = String.valueOf(o);
        return (new Double(s.length()));
    }

    public static String ucase(FValue o, Environment env) {
        String s = String.valueOf(o);
        return (s.toUpperCase());
    }

    public static String lcase(FValue o, Environment env) {
        String s = String.valueOf(o);
        return (s.toLowerCase());
    }

    public static Double instr(FValue o, FValue other, Environment env) {
        String s = String.valueOf(o);
        String s1 = String.valueOf(other);
        return (new Double(s.indexOf(s1)));
    }

    public static String chr(FValue o, Environment env) {
        Double d = o.getAsDouble();
        int i = d.intValue();
        char c = (char) i;
        return (String.valueOf(c));
    }

    public static Double ord(FValue o, Environment env) {
        String s = String.valueOf(o);
        char c = s.charAt(0);
        int i = (int) c;
        return (new Double(c));
    }

    public static String md5(FValue o, Environment env) {
        String s = String.valueOf(o);
        StringBuilder sb = new StringBuilder();
        try {
            byte[] bytes = s.getBytes("UTF-8");
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] cyrp = md.digest(bytes);
            for (int i = 0; i < cyrp.length; i++) {
                char c = (char) cyrp[i];
                String part = Integer.toHexString(c);
                if (part.length() == 4) {
                    part = part.substring(2, 4);
                } else if (part.length() < 2) {
                    part = "0" + part;
                }
                sb.append(part);
            }
        } catch (Exception e) {
            throw new RuntimeException("MD5 error: " + e.toString());
        }
        return (sb.toString());
    }

    public static String urldecode(FValue o, Environment env) {
        String s = String.valueOf(o);
        String result;
        try {
            result = URLDecoder.decode(s, "UTF-8");
        } catch (Exception e) {
            throw new RuntimeException("urldecode error: " + e.toString());
        }
        return (result);
    }

    /* For levenstein */
    private static int min3(int p1, int p2, int p3) {
        int m = (int) (Math.min(Math.min(p1, p2), p3));
        return (m);
    }

    public static Double levenshtein(FValue o, FValue a, Environment env) {
        String str1 = String.valueOf(o);
        String str2 = String.valueOf(a);
        int m = str1.length();
        int n = str2.length();
        int d[][] = new int[m][n];

        for (int i = 0; i < m; i++) {
            d[i][0] = i;
        }
        for (int j = 0; j < n; j++) {
            d[0][j] = j;
        }
        for (int j = 1; j < n; j++) {
            for (int i = 1; i < m; i++) {
                if (str1.charAt(i) == str2.charAt(j)) {
                    d[i][j] = d[(i - 1)][(j - 1)];
                } else {
                    d[i][j] = min3(d[(i - 1)][j] + 1, d[i][(j - 1)] + 1,
                            d[(i - 1)][(j - 1)] + 1);
                }
            }
        }
        return (new Double(d[m - 1][n - 1]));

    }

    public static String str_replace(FValue o, FValue find, FValue replace, Environment env) {
        String s = String.valueOf(o);
        String s1 = String.valueOf(find);
        String s2 = String.valueOf(replace);
        return (s.replace(s1, s2));
    }

    public static String str_shuffle(FValue o, Environment env) {
        String str = String.valueOf(o);
        char[] cs = str.toCharArray();
        for (int i = 0; i < str.length(); i++) {
            int index1 = (int) (Math.random() * str.length());
            int index2 = (int) (Math.random() * str.length());
            char c = cs[index1];
            cs[index1] = cs[index2];
            cs[index2] = c;
        }
        return (new String(cs));
    }

    public static Double isdigit(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isDigit(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double isalpha(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isLetter(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double isalnum(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isLetter(str.charAt(0)) || Character.isDigit(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double isupper(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isUpperCase(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double islower(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isLowerCase(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double iscntrl(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isISOControl(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double isgraph(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (str.charAt(0) >= 0x21 && str.charAt(0) <= 0x7E) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double isprint(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (str.charAt(0) > 0x07) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double ispunct(FValue o, Environment env) {
        String str = String.valueOf(o);
        int type = Character.getType(str.charAt(0));
        if (type == Character.CONNECTOR_PUNCTUATION || type == Character.END_PUNCTUATION
                || type == Character.DASH_PUNCTUATION || type == Character.FINAL_QUOTE_PUNCTUATION
                || type == Character.INITIAL_QUOTE_PUNCTUATION || type == Character.OTHER_PUNCTUATION
                || type == Character.START_PUNCTUATION) {
            return (1.0);
        } else {
            return (0.0);
        }
    }

    public static Double isspace(FValue o, Environment env) {
        String str = String.valueOf(o);
        if (Character.isSpaceChar(str.charAt(0))) {
            return (1.0);
        } else {
            return (0.0);
        }
    }
}
