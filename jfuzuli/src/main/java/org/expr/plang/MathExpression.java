package org.expr.plang;

public class MathExpression extends Expression {

    @Override
    public Object eval(Environment env) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public final static Expression AbsExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.abs(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression SignExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.sign(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression SinExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.sin(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression SinhExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.sinh(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression CosExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.cos(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression CoshExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.cosh(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression TanExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.tan(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression TanhExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.tanh(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression AtanExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.atan(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression Atan2Expression(final Expression expr1, final Expression expr2) {
        return new Expression() {
            private Expression exp1 = expr1;
            private Expression exp2 = expr2;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.atan2(" + exp1.emitJS() + ", " + exp2.emitJS() + ")";
            }
        };
    }

    public final static Expression CbrtExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.cbrt(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression CeilExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.ceil(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression ExpExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.exp(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression FloorExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.floor(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression LogExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.log(" + exp.emitJS() + ")";
            }
        };
    }

    public final static Expression PowExpression(final Expression baseexp, final Expression powerexp) {
        return new Expression() {
            private Expression base = baseexp;
            private Expression power = powerexp;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.pow(" + base.emitJS() + "," + power.emitJS() + ")";
            }
        };
    }

    public final static Expression RandomExpression() {
        return new Expression() {

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.random()";
            }
        };
    }

    public final static Expression SqrtExpression(final Expression expr) {
        return new Expression() {
            private Expression exp = expr;

            @Override
            public Object eval(Environment env) {
                throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            }

            @Override
            public String emitJS() {
                return "Math.sqrt(" + exp.emitJS() + ")";
            }
        };
    }

}
