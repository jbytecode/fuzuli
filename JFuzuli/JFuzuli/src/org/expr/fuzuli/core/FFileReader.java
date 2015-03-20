/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2014 Mehmet Hakan Satman <mhsatman@yahoo.com>
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
package org.expr.fuzuli.core;

import org.expr.fuzuli.interpreter.Environment;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class FFileReader {

    public static FileReader filereader_new(String file, Environment env) throws FileNotFoundException {
        FileReader reader = new FileReader(file);
        return (reader);
    }

    public static String filereader_read(FileReader reader, double length, Environment env) throws IOException {
        char[] c = new char[(int) length];
        int result = -1;
        result = reader.read(c);
        if (result < length) {
            if (result >= 1) {
                char[] newc = new char[result];
                System.arraycopy(c, 0, newc, 0, result);
                return (new String(newc));
            } else {
                return ("");
            }
        }
        return (new String(c));
    }

    public static String filereader_readline(FileReader reader, Environment env) throws IOException {
        StringBuilder builder = new StringBuilder();
        int result = 0;
        char[] c = new char[1];
        while (true) {
            result = reader.read(c);
            if (result == -1 || c[0] == '\n') {
                break;
            } else {
                builder.append(c);
            }
        }
        return (builder.toString());
    }

    public static void filereader_close(FileReader reader, Environment env) throws IOException {
        reader.close();
    }

}
