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


public class ParamsExpression extends Expression {

    ArrayList<String> paramNames;
    
    public ParamsExpression(ArrayList<Expression>expr){
        this.exprs = expr;
        paramNames = new ArrayList<String>();
        for (int i=0;i<this.exprs.size();i++){
            IdentifierExpression id = (IdentifierExpression)this.exprs.get(i);
            paramNames.add(id.iden);
        }
    }
    
    @Override
    public FValue eval(Environment e) {
        return(new FValue(paramNames));
    }
    
}
