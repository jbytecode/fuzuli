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
package Core;

import Interpreter.Environment;
import Interpreter.EvalExpression;
import Interpreter.Expression;
import Interpreter.ExpressionExpression;
import Interpreter.FValue;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class FTimerTask {

    public static void schedule(final Object expr, Object Delay, Object Period, final Environment env) {
        long delay = (long) FValue.getAsDouble(Delay);
        long period = (long) FValue.getAsDouble(Period);
        Timer timer = new Timer();
        final ExpressionExpression exx = (ExpressionExpression) expr;
        final ArrayList<Expression> earr = new ArrayList<Expression>();
        earr.add(exx);
        final EvalExpression evalex = new EvalExpression(earr);
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                evalex.eval(env);
            }
        };
        timer.scheduleAtFixedRate(task, delay, period);
    }

    public static void schedule_once(final Object expr, Object Delay, final Environment env) {
        long delay = (long) FValue.getAsDouble(Delay);
        Timer timer = new Timer();
        final ExpressionExpression exx = (ExpressionExpression) expr;
        final ArrayList<Expression> earr = new ArrayList<Expression>();
        earr.add(exx);
        final EvalExpression evalex = new EvalExpression(earr);
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                evalex.eval(env);
            }

            @Override
            protected void finalize() throws Throwable {
                super.finalize(); //To change body of generated methods, choose Tools | Templates.
                System.out.println("Finalize called");
            }

        };
        timer.schedule(task, delay);
    }
}
