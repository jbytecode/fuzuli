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


class Expression {
    constructor(){

    }
}


class AlertExpression extends Expression {
    
    constructor(exprs){
        super();
        this.exprs = exprs;
    }
    eval(env){
        alert(this.exprs[0].eval(env));
    }
}

class ConstantDoubleNumberExpression extends Expression{

    constructor(doubleValue){
        super();
        this.doubleValue = doubleValue;
    }

    eval(env){
        return(this.doubleValue);
    }
}

class ConstantIntegerNumberExpression extends Expression{

    constructor(longValue){
        super();
        this.longValue = longValue;
    }

    eval(env){
        return(this.longValue);
    }
}

class PlusExpression extends Expression {
    constructor(exprs){
        super();
        this.exprs = exprs;
    }

    eval(env){
        var sum = 0.0;
        for (var i = 0; i < this.exprs.length; i++){
            sum += this.exprs[i].eval(env);
        }
        return(sum);
    }
}

class MinusExpression extends Expression {
    constructor(exprs){
        super();
        this.exprs = exprs;
    }

    eval(env){
        return this.exprs[0].eval(env) - this.exprs[1].eval(env);
    }
}


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
            var next = this.consume();
            if (next == '+') {
                tok.content = "++";
                tok.type = TokenType["PLUSPLUS"];
                return (tok);
            }
            this.putBackChar();
            tok.content = "+";
            tok.type = TokenType["PLUS"];
            return (tok);
        } else if (current == '-') {
            var next = this.consume();
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
            this.putBackChar();
            tok.content = "-";
            tok.type = TokenType["MINUS"];
            return (tok);
        } else if (current == '/') {
            var next = this.consume();
            if (next == '/') {
                while (true) {
                    var c = this.consume();
                    if (c == '\n') {
                        return (this.parseNextToken());
                    }
                }
            } else if (next == '*') {
                while (true) {
                    var c1 = this.consume();
                    var c2 = this.consume();
                    if (c1 == '*' && c2 == '/') {
                        return (this.parseNextToken());
                    }
                    this.putBackChar();
                }
            }
            this.putBackChar();
            tok.content = "/";
            tok.type = TokenType["DIVISION"];
            return (tok);
        } else if (current == '*') {
            tok.content = "*";
            tok.type = TokenType["ASTERIX"];
            return (tok);
        } else if (current == '=') {
            tok.content = "=";
            tok.type = TokenType["EQUALS"];
            return (tok);
        } else if (current == '<') {
            var next = this.consume();
            if (next == '<') {
                tok.content = "<<";
                tok.type = TokenType["BITSHIFTLEFT"];
                return (tok);
            } else if (next == '=') {
                tok.content = "<=";
                tok.type = TokenType["LESSOREQUAL"];
                return (tok);
            }else {
                this.putBackChar();
            }
            tok.content = "<";
            tok.type = TokenType["LESS"];
            return (tok);
        } else if (current == '>') {
            var next = this.consume();
            if (next == '>') {
                tok.content = ">>";
                tok.type = TokenType["BITSHIFTRIGHT"];
                return (tok);
            } else if (next == '=') {
                tok.content = ">=";
                tok.type = TokenType["BIGGEROREQUAL"];
                return (tok);
            } else {
                this.putBackChar();
            }
            tok.content = ">";
            tok.type = TokenType["BIGGER"];
            return (tok);
        } else if (current == '&') {
            tok.content = "&";
            tok.type = TokenType["BITAND"];
            return (tok);
        } else if (current == '|') {
            tok.content = "|";
            tok.type = TokenType["BITOR"];
            return (tok);
        } else if (current == '~') {
            tok.content = "~";
            tok.type = TokenType["BITNOT"];
            return (tok);
        } else if (current == '^') {
            tok.content = "^";
            tok.type = TokenType["BITXOR"];
            return (tok);
        } else if (current == ':') {
            tok.content = ":";
            tok.type = TokenType["COLON"];
            return (tok);
        } else if (current == '!') {
            buf += current;
            current = this.consume();
            if (current == '=') {
                buf += current;
                tok.content = buf.toString();
                tok.type = TokenType["NOTEQUAL"];
                return (tok);
            } else {
                this.putBackChar();
            }
            tok.content = "!";
            tok.type = TokenType["EXCLAMATION"];
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
            tok.type = TokenType["SINGLEQUOTE"];
            return (tok);
        }

        throw new RuntimeException("Unknow character: '" + current + "'");
    }

    
    getNextToken() {
        var tok = this.tokens[this.tokenIndex];
        this.tokenIndex++;
        return (tok);
    }

    getPreviousToken() {
        if (tokenIndex > 1) {
            return (this.tokens[tokenIndex - 2]);
        } else {
            return (null);
        }
    }

    getExpressionList() {
        var exprs = [];
        var e;
        while (true) {
            e = this.getNextExpression();
            if (e == null) {
                break;
            }
            exprs.push(e);
        }
        return (exprs);
    }


    getNextExpression() {
        var tok;
        var exprs = [];
        tok = this.getNextToken();
        if (tok.type != TokenType["IDENTIFIER"]) {
            switch (tok.type) {
                case TokenType["EOP"]:
                    return (null);
                case TokenType["LPARAN"]:
                    return this.getNextExpression();
                case TokenType["RPARAN"]:
                    return (null);
                case TokenType["DOUBLE"]:
                    var dexpr = new ConstantDoubleNumberExpression(parseFloat(tok.content));
                    return (dexpr);
                case TokenType["LONG"]:
                    var iexpr = new ConstantIntegerNumberExpression(parseInt(tok.content));
                    return (iexpr);
                case TokenType["PLUS"]:
                    exprs = this.getExpressionList();
                    return (new PlusExpression(exprs));
                case TokenType["MINUS"]:
                    exprs = this.getExpressionList();
                    return (new MinusExpression(exprs));
                case TokenType["SINGLEQUOTE"]:
                    this.getNextToken(); // This is opening paranthesis.
                    exprs = getExpressionList();
                    return (new ListExpression(exprs));
                default:
                //NOP
            }

        } else if (tok.type == TokenType["IDENTIFIER"]) {
            switch (tok.content) {
                case "alert":
                    exprs = this.getExpressionList();
                    return (new AlertExpression(exprs));     
                default:
                    var fname = tok.content;
                    if (this.getPreviousToken().type == TokenType["LPARAN"]) {
                        exprs = getExpressionList();
                        //System.out.println("Function call to "+fname+" with "+exprs.toString());
                        //var fce = new FunctionCallExpression(exprs);
                        //fce.fname = fname;
                        //return (fce);
                    } else {
                        return (new IdentifierExpression(tok.content));
                    }
            }
        }
        throw new RuntimeException("Can not understand '" + tok.content + "'");
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
//console.log(parser.getTokens());
var exprs = parser.getExpressionList();
var env = null;
var result = null;
for (var i = 0; i < exprs.length; i++){
    expr = exprs[i];
    result = expr.eval(env);
}
console.log(result);
