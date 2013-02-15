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

package Interpreter;

import java.util.ArrayList;
import java.util.List;

public class FillExpression extends Expression{
    
    public FillExpression(ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    public static void fill (ArrayList list, Object value){
        for (int i=0;i<list.size();i++){
           if (value instanceof List){
               fill ((ArrayList)list.get(i), value);
           }else{
               list.set(i, value);
           }
        }
    }
    
    @Override
    public Object eval(Environment e) {
        ArrayList list = (ArrayList)this.exprs.get(0).eval(e);
        Object item = this.exprs.get(1).eval(e);
        fill(list,item);
        return (item);
    }
    
}
