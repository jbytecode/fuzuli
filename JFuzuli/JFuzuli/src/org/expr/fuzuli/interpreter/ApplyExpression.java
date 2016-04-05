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
import java.util.List;

public class ApplyExpression extends Expression {

    public ApplyExpression(ArrayList<Expression> exprs) {
        this.exprs = exprs;
    }

    @Override
    public Object eval(Environment e) {
        String fname;
        Object result;
        if (this.exprs.get(0) instanceof IdentifierExpression) {
            fname = ((IdentifierExpression) this.exprs.get(0)).iden;
        } else {
            fname = this.exprs.get(0).eval(e).toString();
        }
        List<Expression> cdr = this.exprs.subList(1, this.exprs.size() - 1);
        ArrayList<Expression> cdr2 = new ArrayList<>(cdr);
        FunctionCallExpression fce = new FunctionCallExpression(cdr2);
        fce.fname = fname;
        result = fce.eval(e);
        return (result);
    }
}
