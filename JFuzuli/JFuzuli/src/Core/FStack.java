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
import java.util.Stack;

public class FStack {

    public static Stack<Object> stack_new(Environment env) {
        Stack<Object> stack = new Stack<Object>();
        return (stack);
    }

    public static Object stack_push(Object Stack, Object o, Environment env) {
        Stack<Object> stack = (Stack<Object>) Stack;
        return (stack.push(o));
    }

    public static Object stack_pop(Object Stack, Environment env) {
        Stack<Object> stack = (Stack<Object>) Stack;
        return (stack.pop());
    }

    public static Object stack_peek(Object Stack, Environment env) {
        Stack<Object> stack = (Stack<Object>) Stack;
        return (stack.peek());
    }

    public static void stack_clear(Object Stack, Environment env) {
        Stack<Object> stack = (Stack<Object>) Stack;
        stack.clear();
    }

    public static boolean stack_empty(Object Stack, Environment env) {
        Stack<Object> stack = (Stack<Object>) Stack;
        return (stack.empty());
    }

}
