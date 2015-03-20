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


public class FuzuliException extends RuntimeException {

    String message;
    Throwable cause;
    
    @Override
    public String getMessage() {
        return(this.toString());
    }

    @Override
    public String getLocalizedMessage() {
        return (this.message);
    }

    @Override
    public Throwable getCause() {
        return (this.cause);
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder();
        String enter = "\n";
        b.append("********************************************************");
        b.append(enter);
        b.append("* Program aborted:");
        b.append(enter);
        b.append("* ").append(this.cause);
        b.append(enter);
        b.append("* Due to:");
        b.append(enter);
        b.append("* ").append(this.message);
        b.append(enter);
        b.append("********************************************************");
        b.append(enter);
        return (b.toString());
    }
    
    
    public FuzuliException (Exception reason, String custom){
        this.cause = reason;
        this.message=custom;
    }
}
