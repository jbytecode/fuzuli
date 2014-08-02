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
import Interpreter.Expression;
import Interpreter.FValue;
import Interpreter.FunctionCallExpression;
import Interpreter.FunctionExpression;
import java.util.ArrayList;


public class FThread {
    
    public static void thread_sleep(Object millis, Environment env){
        long Millis = (long)FValue.getAsDouble(millis);
        try{
            Thread.sleep(Millis);
        }catch(InterruptedException e){
            System.out.println(e.toString());
        }
    }
 
    public static Thread thread_new(String functionname, final Environment env){
        final FunctionExpression func = env.findFunction(functionname);
        ArrayList<Expression> params = new ArrayList<Expression>();
        final FunctionCallExpression call = new FunctionCallExpression(params);
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                call.EvalWithoutName(func, env);
            }
        });
        return(th);
    }
    
    public static void thread_start(Thread th, Environment env){
        th.start();
    }
    
    public static void thread_join(Thread th, Environment env){
        try{
            th.join();
        }catch(InterruptedException e){
            System.out.println(e.toString());
        }
    }
    
}


