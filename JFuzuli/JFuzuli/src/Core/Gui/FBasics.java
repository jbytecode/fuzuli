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

package Core.Gui;

import Interpreter.Environment;
import Interpreter.FunctionExpression;
import java.awt.Component;
import javax.swing.JFrame;

public class FBasics {

    public static void msgbox (String text, Environment env){
        javax.swing.JOptionPane.showMessageDialog(null, text);
    }
    
    public static Object inputbox (String message, Environment env){
        return (javax.swing.JOptionPane.showInputDialog(message));
    }
    
    public static void registerEvent (Object object, FunctionExpression func, Environment env){
        FuzuliEventListener listen = new FuzuliEventListener(func, env);
        FuzuliEventHandler fev = (FuzuliEventHandler)object;
        fev.setEventListener(listen); 
    }
}
