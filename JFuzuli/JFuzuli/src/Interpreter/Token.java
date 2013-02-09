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

/**
 *
 * @author hako
 */
public class Token {
    String content;
    TokenType type;
    public static double epsilon = 0.000001;
    public static double precision = 30;
    
    enum TokenType {
        INTEGER,
        LONG,
        DOUBLE,
        PLUS,
        PLUSPLUS,
        MINUS,
        MINUSMINUS,
        ASTERIX,
        DIVISION,
        LPARAN,
        RPARAN,
        OBJECT,
        IDENTIFIER,
        STRING,
        EQUALS,
        LESS,
        BIGGER,
        LESSOREQUAL,
        BIGGEROREQUAL,
        NOTEQUAL,
        EXCLAMATION,
        BITAND,
        BITOR,
        BITNOT,
        BITXOR,
        BITSHIFTRIGHT,
        BITSHIFTLEFT,
        COLON,
        SLASHSLASHCOMMENT,
        SLASH_ASTERIX_COMMENT_START,
        SLASH_ASTERIX_COMMENT_END,
        UNKNOWN,
        EOP,
    }
}

