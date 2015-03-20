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
import java.util.ArrayList;
import java.util.HashMap;

public class FHashMap {

    public static HashMap<Object,Object> map_new (Environment env){
        HashMap<Object, Object> hashmap = new HashMap<Object, Object>();
        return(hashmap);
    }
    
    public static void map_put (Object map, Object key, Object value, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        hashmap.put(key,value);
    }
    
    public static Object map_get (Object map, Object key, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        return(hashmap.get(key));
    }
    
    public static void map_clear (Object map, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        hashmap.clear();
    }
    
    public static Object map_remove (Object map, Object key, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        return(hashmap.remove(key));
    }
    
    public static int map_size (Object map, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        return(hashmap.size());
    }
    
    public static boolean map_empty (Object map, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        return(hashmap.isEmpty());
    }
    
    public static boolean map_contains_key (Object map, Object key, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        return(hashmap.containsKey(key));
    }
    
    public static boolean map_contains_value (Object map, Object value, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        return(hashmap.containsValue(value));
    }
    
    public static Object map_get_keys (Object map, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        ArrayList<Object> arr = new ArrayList<Object>(hashmap.keySet());
        return(arr);
    }
    
    public static Object map_get_values (Object map, Environment env){
        HashMap<Object, Object> hashmap = (HashMap<Object, Object>)map;
        ArrayList<Object> arr = new ArrayList<Object>(hashmap.values());
        return(arr);
    }
    
    
}
