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


public class FunctionExpression extends Expression {

    String fname;
    ArrayList<String> params;
    ArrayList<Expression> body;
    
    public FunctionExpression(ArrayList<Expression>expr){
        this.exprs = expr;
        body = new ArrayList<Expression>();
    }
    
    @Override
    public Object eval(Environment e) {
        this.fname = ((IdentifierExpression)this.exprs.get(0)).iden;
        params = (ArrayList<String>)this.exprs.get(1).eval(e);
        for (int i=2;i<this.exprs.size();i++){
            this.body.add(this.exprs.get(i));
        }
        e.registerFunction(fname, this);
        return(this);
    }
    
}
