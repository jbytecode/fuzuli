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

package Core;

import Interpreter.Environment;
import java.io.FileWriter;
import java.io.IOException;

public class FFileWriter {

    public static FileWriter filewriter_new (String filename, Environment env) throws IOException{
        FileWriter writer = new FileWriter(filename);
        return(writer); 
    }
    
    public static void filewriter_write (FileWriter writer, String s, Environment env) throws IOException{
        writer.write(s);
    }
    
    public static void filewriter_flush (FileWriter writer, Environment env) throws IOException{
        writer.flush(); 
    }
    
    public static void filewriter_close (FileWriter writer, Environment env) throws IOException{
        writer.close();
    }
    
}
