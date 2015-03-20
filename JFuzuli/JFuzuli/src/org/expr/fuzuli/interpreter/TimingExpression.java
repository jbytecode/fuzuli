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

public class TimingExpression extends Expression {

    public TimingExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
    }

    @Override
    public Object eval(Environment e) {
        long time1, time2;
        int size = this.exprs.size();
        Object result = null;

        time1 = System.currentTimeMillis();

        for (int i = 0; i < size; i++) {
            result = this.exprs.get(i).eval(e);
        }

        time2 = System.currentTimeMillis();

        return (new Double(time2 - time1));
    }
}
