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


public class SwitchExpression extends Expression {
    
    public SwitchExpression (ArrayList<Expression> expr){
        this.exprs = expr;
    }

    @Override
    public FValue eval(Environment e) {
        e.subEnvironment = new Environment(e);
        Environment env = e.subEnvironment;
        
        FValue key = this.exprs.get(0).eval(env);
        
        for (int i=1;i<this.exprs.size();i++){
            CaseExpression caze = (CaseExpression)(this.exprs.get(i));
            FValue caseKey = caze.getKey(env);
            if (FValue.Equals(caseKey, key)){
                return(caze.eval(env));
            }
        }
        return(FValue.ZERO);
    }
    
    
}
