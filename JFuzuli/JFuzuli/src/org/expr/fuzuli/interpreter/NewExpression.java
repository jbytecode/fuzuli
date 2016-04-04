/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2016 Mehmet Hakan Satman <mhsatman@yahoo.com>
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

public class NewExpression extends Expression {

    //Class [classname] extends [Object] [exprlist]
    public NewExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment e) {
        Environment env = new Environment(e);
        String classname = ((IdentifierExpression)this.exprs.get(0)).iden;
        ClassExpression clz = (ClassExpression) e.findClass(classname);
        inherit(clz, env);
        for(int i=3;i<clz.exprs.size();i++){
            clz.exprs.get(i).eval(env);
        }
        return(env);
    }
    
     private void inherit(ClassExpression clz, Environment e){
        if(clz.extendsobject.equals("Object")){
            return;
        }
        ClassExpression parent = (ClassExpression) e.findClass(clz.extendsobject);
        
        for(int i=3;i<parent.exprs.size();i++){
            parent.exprs.get(i).eval(e);
        }
        
        inherit(parent, e);
    }
}
