package org.expr.plang;

public class TypeCastExpression extends Expression {

	@Override
	public Object eval(Environment env) {
		// TODO Auto-generated method stub
		return null;
	}

	public final static Expression ByteCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Byte b = Byte.valueOf(String.valueOf(obj));
				return b;
			}
		};
	}

	public final static Expression IntegerCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Integer i = Integer.valueOf(String.valueOf(obj));
				return i;
			}
		};
	}

	public final static Expression FloatCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Float f = Float.valueOf(String.valueOf(obj));
				return f;
			}
		};
	}

	public final static Expression DoubleCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Double d = Double.valueOf(String.valueOf(obj));
				return d;
			}
		};
	}

	public final static Expression ShortCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Short s = Short.valueOf(String.valueOf(obj));
				return s;
			}
		};
	}

	public final static Expression LongCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Long l = Long.valueOf(String.valueOf(obj));
				return l;
			}
		};
	}

	public final static Expression CharCastExpression(final Expression expr) {
		return new Expression() {
			private Expression exp = expr;

			@Override
			public Object eval(Environment env) {
				Object obj = this.exp.eval(env);
				Integer i = Integer.valueOf(String.valueOf(obj));
				char c = (char)i.intValue();
				return c;
			}
		};
	}

}
