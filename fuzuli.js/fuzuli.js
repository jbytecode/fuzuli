var TokenType = {
    INTEGER: 0,
    LONG: 1,
    DOUBLE: 2,
    PLUS: 3,
    PLUSPLUS: 4,
    MINUS: 5,
    MINUSMINUS: 6,
    ASTERIX: 7,
    DIVISION: 8,
    LPARAN: 9,
    RPARAN: 10,
    OBJECT: 11,
    IDENTIFIER: 12,
    STRING: 13,
    JSCODE: 14,
    EQUALS: 15,
    LESS: 16,
    BIGGER: 17,
    LESSOREQUAL: 18,
    BIGGEROREQUAL: 19,
    NOTEQUAL: 20,
    EXCLAMATION: 21,
    BITAND: 22,
    BITOR: 23,
    BITNOT: 24,
    BITXOR: 25,
    BITSHIFTRIGHT: 26,
    BITSHIFTLEFT: 27,
    COLON: 28,
    SLASHSLASHCOMMENT: 29,
    SLASH_ASTERIX_COMMENT_START: 30,
    SLASH_ASTERIX_COMMENT_END: 31,
    SINGLEQUOTE: 32,
    UNKNOWN: 33,
    EOP: 34};


class Token {
    
    constructor(){
        this.type = "";
        this.content = "";
    }
    
    toString(){
        return(this.content);
    }
};


class Parser {

    constructor(code) {
        this.sourcecode = code;
        this.charIndex = 0;
        this.tokenIndex = 0;
        this.tokens = [];
        this.linenumber = 0;
        this.resetParser();
    }

    getSourceCode() {
        return (this.sourcecode);
    }

    setSourceCode(s) {
        this.sourcecode = s;
    }

    getTokens(){
        return(this.tokens);
    }

    resetParser() {
        this.charIndex = 0;
        this.tokenIndex = 0;
        this.tokens = [];
        this.lineNumber = 0;
        this.readAllTokens();
    }

    consume() {
        if(this.charIndex >= this.sourcecode.length - 1){
            return '\0';
        }
        var current = this.sourcecode.charAt(this.charIndex);
        console.log("Consumed: " + current);
        this.charIndex++;
        if (this.charIndex >= this.sourcecode.length) {
            console.log("charindex is bigger than source code len, exiting");
            return ('');
        }
        return (current);
    }

    putBackChar() {
        this.charIndex--;
    }

    looknext() {
        if ((charIndex + 1) != this.sourcecode.length()) {
            return (this.sourcecode.charAt(this.charIndex + 1));
        } else {
            return ('');
        }
    }

    readAllTokens() {
        var k = 0;
        while (true) {
            var tok = this.parseNextToken();
            this.tokens.push(tok);
            if (tok.type == TokenType["EOP"]){
                break;
            }
            k++;
            if(k > 500){
                console.log("Exit because k > 500");
            }
        }
    }

    isSpaceChar(chr){
        return(chr == " " || chr == "\t");
    }

    isDigit(chr){
        return(chr >= '0' && chr <= '9');
    }

    isLetter(chr){
        return(chr.toLowerCase() != chr.toUpperCase());
    }

    parseNextToken() {
        var buf = "";
        var tok = new Token();
        var current;
        current = this.consume();
        if (current == null || current == '' || current == '\0') {
            tok.type = TokenType["EOP"];
            tok.content = "End of Program";
            return (tok);
        } else if (current == ' ' || current == '\t' || current == '\n' || current == '\r' || this.isSpaceChar(current)) {
            if (current == '\n') {
                this.lineNumber++;
            }
            return (this.parseNextToken());
        } else if (current == '#') {
            while (true) {
                current = this.consume();
                if (current == '\n') {
                    this.lineNumber++;
                    break;
                }
            }
            return (this.parseNextToken());
        } else if (current == '(') {
            tok.content = "(";
            tok.type = TokenType["LPARAN"];
            return (tok);
        } else if (current == ')') {
            tok.content = ")";
            tok.type = TokenType["RPARAN"];
            return (tok);
        } else if (this.isDigit(current)) {
            if (current == '0') {
                var next = this.consume();
                if (next == 'x') {
                    while (true) {
                        current = this.consume();
                        if (this.isDigit(current) || (current >= 'a' && current <= 'f') || (current >= 'A' && current <= 'F')) {
                            buf += current;
                        } else {
                            break;
                        }
                    }
                    this.putBackChar();
                    tok.content = String.valueOf(Long.parseLong(buf.toString(), 16));
                    tok.type = TokenType["LONG"];
                    return (tok);
                } else {
                    this.putBackChar();
                }
            }
            buf += (current);
            while (true) {
                current = this.consume();
                if (this.isDigit(current) || current == '.' || current == 'E') {
                    if (current == '.') {
                        tok.type = TokenType["DOUBLE"];
                    }
                    buf += (current);
                } else {
                    this.putBackChar();
                    break;
                }
            }
            tok.content = buf.toString();
            tok.type = TokenType["DOUBLE"];
            if (tok.content.indexOf(".") == -1) {
                tok.type = TokenType["LONG"];
            }
            return (tok);
        } else if (current == '+') {
            var next = consume();
            if (next == '+') {
                tok.content = "++";
                tok.type = Token.TokenType.PLUSPLUS;
                return (tok);
            }
            putBackChar();
            tok.content = "+";
            tok.type = Token.TokenType.PLUS;
            return (tok);
        } else if (current == '-') {
            var next = consume();
            if (this.isDigit(next)) {
                this.putBackChar();
                var t = this.parseNextToken();
                buf += "-";
                buf += t.content;
                tok.content = buf.toString();
                tok.type = TokenType["DOUBLE"];
                return (tok);
            } else if (next == '-') {
                tok.content = "--";
                tok.type = Token.TokenType.MINUSMINUS;
                return (tok);
            }
            putBackChar();
            tok.content = "-";
            tok.type = Token.TokenType.MINUS;
            return (tok);
        } else if (current == '/') {
            var next = consume();
            if (next == '/') {
                while (true) {
                    var c = consume();
                    if (c == '\n') {
                        return (parseNextToken());
                    }
                }
            } else if (next == '*') {
                while (true) {
                    var c1 = consume();
                    var c2 = consume();
                    if (c1 == '*' && c2 == '/') {
                        return (parseNextToken());
                    }
                    putBackChar();
                }
            }
            putBackChar();
            tok.content = "/";
            tok.type = Token.TokenType.DIVISION;
            return (tok);
        } else if (current == '*') {
            tok.content = "*";
            tok.type = Token.TokenType.ASTERIX;
            return (tok);
        } else if (current == '=') {
            tok.content = "=";
            tok.type = Token.TokenType.EQUALS;
            return (tok);
        } else if (current == '<') {
            var next = consume();
            if (next == '<') {
                tok.content = "<<";
                tok.type = Token.TokenType.BITSHIFTLEFT;
                return (tok);
            } else if (next == '=') {
                tok.content = "<=";
                tok.type = Token.TokenType.LESSOREQUAL;
                return (tok);
            } else if (next == '?') {
                var sb = "";
                while (looknext() != '\n') {
                    sb += consume();
                }
                consume();
                if (sb.substring(0, 10).equals("javascript")) {
                    var jscode = "";
                    while (true) {
                        if (jscode.length() > 2) {
                            if (jscode.toString().endsWith("?>")) {
                                break;
                            }
                        }
                        jscode.append(consume());
                        //System.out.println(jscode);
                    }
                    var jsfinalcode = jscode.substring(0, jscode.length() - 2);
                    tok.content = jsfinalcode;
                    tok.type = Token.TokenType.JSCODE;
                    return (tok);
                }
            } else {
                putBackChar();
            }
            tok.content = "<";
            tok.type = Token.TokenType.LESS;
            return (tok);
        } else if (current == '>') {
            var next = consume();
            if (next == '>') {
                tok.content = ">>";
                tok.type = Token.TokenType.BITSHIFTRIGHT;
                return (tok);
            } else if (next == '=') {
                tok.content = ">=";
                tok.type = Token.TokenType.BIGGEROREQUAL;
                return (tok);
            } else {
                putBackChar();
            }
            tok.content = ">";
            tok.type = Token.TokenType.BIGGER;
            return (tok);
        } else if (current == '&') {
            tok.content = "&";
            tok.type = Token.TokenType.BITAND;
            return (tok);
        } else if (current == '|') {
            tok.content = "|";
            tok.type = Token.TokenType.BITOR;
            return (tok);
        } else if (current == '~') {
            tok.content = "~";
            tok.type = Token.TokenType.BITNOT;
            return (tok);
        } else if (current == '^') {
            tok.content = "^";
            tok.type = Token.TokenType.BITXOR;
            return (tok);
        } else if (current == ':') {
            tok.content = ":";
            tok.type = Token.TokenType.COLON;
            return (tok);
        } else if (current == '!') {
            buf.append(current);
            current = consume();
            if (current == '=') {
                buf.append(current);
                tok.content = buf.toString();
                tok.type = Token.TokenType.NOTEQUAL;
                return (tok);
            } else {
                putBackChar();
            }
            tok.content = "!";
            tok.type = Token.TokenType.EXCLAMATION;
            return (tok);
        } else if (this.isLetter(current)) {
            buf += current;
            while (true) {
                current = this.consume();
                if (!this.isLetter(current) && !this.isDigit(current) && current != '_' && current != '.') {
                    this.putBackChar();
                    break;
                }
                buf += current;
            }
            tok.content = buf.toString();
            tok.type = TokenType["IDENTIFIER"];
            return (tok);
        } else if (current == '"') {
            while (true) {
                current = this.consume();
                if (current == '\\') {
                    current = this.consume();
                    if (current == 'n') {
                        buf += "\n";
                    } else {
                        buf += current;
                    }
                } else if (current == '"') {
                    break;
                } else {
                    buf += current;
                }
            }
            tok.type = TokenType["STRING"];
            tok.content = buf.toString();
            return (tok);
        } else if (current == '\'') {
            tok.content = "'";
            tok.type = Token.TokenType.SINGLEQUOTE;
            return (tok);
        }

        throw new RuntimeException("Unknow character: '" + current + "'");
    }

    
    getNextToken() {
        var tok = this.tokens[tokenIndex];
        tokenIndex++;
        return (tok);
    }

    getPreviousToken() {
        if (tokenIndex > 1) {
            return (this.tokens[tokenIndex - 2]);
        } else {
            return (null);
        }
    }
};


var scripts = document.getElementsByTagName("script");
var sourcecode = "";
for(var i = 0; i < scripts.length; i++){
    var scrpt = scripts[i];
    if(scrpt.type == "text/fuzuli"){
        sourcecode += scrpt.text + "\n\n";
    }
}

console.log("Received source code: " + sourcecode);
var parser = new Parser(sourcecode);
console.log("Parser created with content: " + parser.getSourceCode());
console.log(parser.getTokens());

