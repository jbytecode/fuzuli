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

public class BlockExpression extends Expression{

    public BlockExpression(ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public Object eval(Environment e) {
        e.subEnvironment = new Environment(e);
        Environment currentEnv = e.subEnvironment;
        Object val=null, returnval=0;
        
        for (int i=0;i<this.exprs.size();i++){
            val = this.exprs.get(i).eval(currentEnv);
            if(val instanceof ReturnExpression ){
                ReturnExpression re =  (ReturnExpression)val;
                returnval = re;
                break;
            }
        }
        return(returnval);
    }

    
}
