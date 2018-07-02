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

public class IfExpression extends Expression {
    
    public IfExpression(ArrayList<Expression> expr){
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment e) {
        Object criterian = this.exprs.get(0).eval(e);
        if(this.exprs.size() == 2){
            if(FValue.getAsDouble(criterian) == 1.0){
                return (this.exprs.get(1).eval(e));
            }
        }else if (this.exprs.size() == 3){
            if(FValue.getAsDouble(criterian) == 1.0){
                return (this.exprs.get(1).eval(e));
            }else{
                return (this.exprs.get(2).eval(e));
            }
        }else{
            System.out.println("Criteria: "+FValue.getAsDouble(criterian));
            throw new RuntimeException("Bad if statement: expression count = " +this.exprs.size());
        }
        return(FValue.ZERO);
    }
    
    
}
