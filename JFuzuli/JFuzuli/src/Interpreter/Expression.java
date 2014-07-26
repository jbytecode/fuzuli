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

import java.io.Serializable;
import java.util.ArrayList;


/**
 *
 * @author hako
 */
public abstract class Expression implements Serializable {
        
    ArrayList<Expression> exprs;
    
    public abstract Object eval (Environment e);
    
    public ArrayList<Expression> getExpressions(){
        return(exprs);
    }
    
    @Override
    public String toString(){
        StringBuilder buf = new StringBuilder();
        buf.append(this.getClass().getCanonicalName()).append("{");
        if(exprs!=null){
        for (int i=0;i<exprs.size();i++){
            if(exprs.get(i) != null){
                buf.append(exprs.get(i).toString());
            }
            buf.append(",");
        }
        }
        buf.append("}\n");
        return(buf.toString());
    }
}
