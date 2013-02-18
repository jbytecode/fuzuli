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

public class NewExpression extends Expression {

    public NewExpression(ArrayList<Expression> exprs) {
        this.exprs = exprs;
    }

    @Override
    public Object eval(Environment e) {
        String classname = ((IdentifierExpression) this.exprs.get(0)).iden;
        Environment objectEnvironment = new Environment(null);
        ClassExpression clazz = e.findClass(classname);
        if (clazz == null) {
            throw new FuzuliException(new RuntimeException(), "Class " + classname + " is not found");
        }

        if (!clazz.extendsClassName.equals("Object")) {
            ClassExpression class_extends = e.findClass(clazz.extendsClassName);
            for (int i = 3; i < class_extends.exprs.size(); i++) {
                class_extends.exprs.get(i).eval(objectEnvironment);
            }
        }

        for (int i = 3; i < clazz.exprs.size(); i++) {
            clazz.exprs.get(i).eval(objectEnvironment);
        }

        return (objectEnvironment);
    }
}
