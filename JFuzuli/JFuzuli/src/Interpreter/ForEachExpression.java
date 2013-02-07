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

public class ForEachExpression extends Expression {

    public ForEachExpression (ArrayList<Expression> expr){
        this.exprs = expr;
    }
    
    @Override
    public Object eval(Environment e) {
        e.subEnvironment = new Environment(e);
        Environment env = e.subEnvironment;
        
        String iden = ((IdentifierExpression)this.exprs.get(0)).iden;
        String in  = ((IdentifierExpression)this.exprs.get(1)).iden;
        ArrayList<Expression> list = (ArrayList<Expression>)this.exprs.get(2).eval(env);
        for (int i=0;i<list.size();i++){
            env.setVariable(iden, list.get(i).eval(env));
            for (int j=3;j<this.exprs.size();j++){
                this.exprs.get(j).eval(env);
            }
        }
        return(FValue.ZERO);
    }
    
}
