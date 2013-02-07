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
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;

public class FIO {

    private static HashMap<Thread, Random> randomizers = new HashMap<Thread, Random>();
    
    public static String readline(Environment env) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            String line = reader.readLine();
            return (line);
        } catch (Exception e) {
            throw new RuntimeException("Can not read from console: " + e.toString());
        }

    }

    public static Double exit(Double d, Environment env) {
        System.exit(d.intValue());
        return (0.0);
    }

    public static Object fopen(String name, String type, Environment env) throws FileNotFoundException {
        if (type.equals("w")) {
            return (new DataOutputStream(new FileOutputStream(name))); 
        } else if (type.equals("r")) {
            return (new DataInputStream(new FileInputStream(name))); 
        } else {
            throw new RuntimeException("Unknown file open operation " + type);
        }
    }

    public static Object fwrite(DataOutputStream os, Object obj, Environment env) throws IOException {
        if (obj instanceof String) {
            String s = (String) (obj);
            os.writeUTF(s);
        } else if (obj instanceof Number) {
            os.writeDouble((Double)obj);
        } else if (obj instanceof ArrayList) {
            ArrayList al = (ArrayList)obj;
            for (int i=0;i<al.size();i++){
                fwrite(os, al.get(i), env);
            }
        }else{
            throw new RuntimeException("Can not write object "+obj+" to file");
        }
        return (0.0);
    }

    public static Object fclose(Object o, Environment env) throws IOException {
        if (o instanceof InputStream) {
            InputStream is = (InputStream) o;
            is.close();
        } else if (o instanceof OutputStream) {
            OutputStream os = (OutputStream) o;
            os.close();
        } else {
            throw new RuntimeException("fclose can not close object: ");
        }
        return (0.0);

    }
    
    public static Object fread(DataInputStream dis, Object o, Environment env) throws IOException {
        if(o instanceof Double){
            return(dis.readDouble());
        }else if (o instanceof String){
            return(dis.readUTF());
        }else{
            throw new RuntimeException("fread can not read from "+dis);
        }
    }
    
    public static Object unlink (String name, Environment env){
        File f = new File(name);
        return f.delete();
    }
    
    public static Object randomize (Number num, Environment env){
        Random r = FIO.getCurrentRandomizer();
        r.setSeed(num.longValue());
        return(0.0);
    }
    
    private static Random getCurrentRandomizer(){
        Thread th = Thread.currentThread();
        if (FIO.randomizers.containsKey(th)){
            Random r = FIO.randomizers.get(th);
            return (r);
        }else{
            Random r = new Random();
            FIO.randomizers.put(th, r);
            return(r);
        }
    }
    
    public static double rnd (Environment env){
        Random r = FIO.getCurrentRandomizer();
        return(r.nextDouble());
    }
    
    public static String getenv (String var, Environment env){
        return(System.getProperty(var));
    }
    
    public static Object setenv (String var, Object value, Object cpar, Environment env){
        System.setProperty(var, String.valueOf(value));
        return(value);
    }
}
