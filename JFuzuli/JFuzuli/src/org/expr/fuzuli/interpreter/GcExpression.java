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


package org.expr.fuzuli.interpreter;

import java.util.ArrayList;
import java.util.HashMap;


public class GcExpression extends Expression {

    public GcExpression (ArrayList<Expression> exprs){
        this.exprs = exprs;
    }
    
    @Override
    public Object eval(Environment e) {
        Runtime r = Runtime.getRuntime();
        r.gc();
        HashMap<String, Object> memory = new HashMap<String, Object>();
        memory.put("free_memory", r.freeMemory());
        memory.put("total_memory", r.totalMemory());
        memory.put("max_memory", r.maxMemory());
        return(memory);
    }
    
}
