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
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;

public class FProperties {

    public static Properties properties(Environment env){
        Properties props = new Properties();
        return(props); 
    }
    
    public static void properties_load(Properties props, String file, Environment env) throws FileNotFoundException, IOException{
        FileReader reader = new FileReader(file);
        props.load(reader); 
    }
    
    public static void properties_save(Properties props, String file, Environment env) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(file);
        props.store(fos, "Saved by Fuzuli");
    }
    
    public static void properties_set(Properties props, String key, String value, Environment env){
        props.setProperty(key, value);
    }
    
    public static String properties_get(Properties props, String key, Environment env){
        return(props.getProperty(key));
    }
    
    public static Object properties_keys (Properties props, Environment env){
        return(props.keySet());
    }
    
    public static Object properties_values (Properties props, Environment env){
        return(props.values());
    }
    
    public static void properties_clear (Properties props, Environment env){
        props.clear();
    }
    
    public static int properties_size (Properties props, Environment env){
        return(props.size()); 
    }
    
}
