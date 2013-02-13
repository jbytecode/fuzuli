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

public class ClassExpression extends Expression {

    Environment classEnvironment;
    String className;
    
    public Environment getClassEnvironment() {
        return classEnvironment;
    }

    public void setClassEnvironment(Environment classEnvironment) {
        this.classEnvironment = classEnvironment;
    }
    
    
    public ClassExpression (ArrayList<Expression> exprs){
        this.exprs = exprs;
    }
    
    @Override
    public Object eval(Environment e) {
        IdentifierExpression class_id = (IdentifierExpression)this.exprs.get(0);
        className = class_id.iden;
        
        IdentifierExpression extends_id = (IdentifierExpression)this.exprs.get(1);
        if(!extends_id.iden.equals("extends")){
            throw new FuzuliException(null, "Keyword 'extends' required in class definition");
        }
        
        classEnvironment = new Environment(null);
        
        e.registerClass(className, this);
        return(null);
    }
    
}
