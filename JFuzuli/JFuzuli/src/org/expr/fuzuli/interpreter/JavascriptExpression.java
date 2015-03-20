/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2014 Mehmet Hakan Satman <mhsatman@yahoo.com>
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
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.script.Bindings;
import javax.script.ScriptContext;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

public class JavascriptExpression extends Expression {

    String code;
    ScriptEngineManager scriptManager;
    ScriptEngine scriptEngine;

    public JavascriptExpression(ArrayList<Expression> expr) {
        this.exprs = expr;
        StringExpression s = (StringExpression) expr.get(0);
        code = s.val;

        scriptManager = new ScriptEngineManager();
        scriptEngine = scriptManager.getEngineByName("javascript");
    }

    @Override
    public Object eval(Environment e) {
        Object[] keynames = e.variables.keySet().toArray();
        for (Object keyname : keynames) {
            scriptEngine.put(keyname.toString(), e.variables.get(keyname.toString()));
        }

        try {
            scriptEngine.eval(code);
        } catch (ScriptException ex) {
            throw new FuzuliException(null, ex.toString());
        }

        Bindings bindings = scriptEngine.getBindings(ScriptContext.ENGINE_SCOPE);
        keynames = bindings.keySet().toArray();
        for (Object keyname : keynames) {
            Object result = scriptEngine.get(keyname.toString());
            e.setVariable(keyname.toString(), result);
        }
        return (1);
    }

}
