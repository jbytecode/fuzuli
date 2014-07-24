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
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.TimeZone;

public class FDate {

    public static ArrayList<Object> datetime (Environment env){
        Calendar can = Calendar.getInstance();
        ArrayList<Object> arr = new ArrayList<>();
        arr.add(can.get(Calendar.YEAR));
        arr.add(can.get(Calendar.MONTH));
        arr.add(can.get(Calendar.DAY_OF_MONTH));
        arr.add(can.get(Calendar.HOUR_OF_DAY));
        arr.add(can.get(Calendar.MINUTE));
        arr.add(can.get(Calendar.SECOND));
        arr.add(can.get(Calendar.MILLISECOND));
        return(arr);
    }
    
   public static Object timezone_get (Environment env){
       Calendar can = Calendar.getInstance();
       TimeZone zone = can.getTimeZone();
       return(zone.getID());
   }
   
   public static Object timezone_list (Environment env){
       String[] list = TimeZone.getAvailableIDs();
       ArrayList<String> arrs = new ArrayList<String>(list.length);
       for (String s : list){
           arrs.add(s);
       }
       return(arrs);
   }
   
   public static void timezone_set(Object zone, Environment env){
       Calendar can = Calendar.getInstance();
       TimeZone timezone = TimeZone.getTimeZone(zone.toString());
       can.setTimeZone(timezone);
   }
    
}
