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
import Interpreter.FValue;
import java.util.ArrayList;
import java.util.Random;

public class FRandom {

    private static Random random = new Random();
    
    public static void randomize(Object o, Environment env){
        long seed = (long)FValue.getAsDouble(o);
        System.out.println("F: Setting seed to " + seed);
        random.setSeed(seed); 
    }
    
    public static double nextDouble(Environment env){
        return(random.nextDouble());
    }
    
    public static float nextFloat(Environment env){
        return(random.nextFloat());
    }
    
    public static int nextInt(Environment env){
        return(random.nextInt()); 
    }
    
    public static long nextLong(Environment env){
        return(random.nextLong());
    }
    
    public static boolean nextBoolean(Environment env){
        return(random.nextBoolean()); 
    }
    
    public static double nextGaussian(Environment env){
        return(random.nextGaussian()); 
    }
    
    public static ArrayList<Double> nextDoubleList(Object o, Environment env){
        int n = (int)FValue.getAsDouble(o);
        ArrayList<Double> arr = new ArrayList<Double>(n);
        for (int i=0;i<n;i++){
            arr.add(random.nextDouble());
        }
        return(arr);
    }
    
}
