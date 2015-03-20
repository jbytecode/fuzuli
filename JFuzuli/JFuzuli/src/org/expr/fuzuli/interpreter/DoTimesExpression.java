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

public class DoTimesExpression extends Expression {

    public DoTimesExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment e) {
        Environment env = new Environment(e);
        Object result = null;
        IdentifierExpression iden = (IdentifierExpression) this.exprs.get(0);
        int times = (int) FValue.getAsDouble(this.exprs.get(1).eval(env));
        for (int i = 0; i < times; i++) {
            env.setVariableInThisEnvironment(iden.iden, i);
            for (int j = 2; j < this.exprs.size(); j++) {
                Expression ex = this.exprs.get(j);
                result = ex.eval(env);
                if (result instanceof BreakExpression) {
                    return (result);
                }
                if (result instanceof ReturnExpression) {
                    ReturnExpression re = (ReturnExpression) (result);
                    return (re);
                }
            }
        }
        return (result);
    }
}
