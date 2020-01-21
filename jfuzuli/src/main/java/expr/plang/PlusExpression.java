package org.expr.plang;

public class PlusExpression extends Expression{

	Expression left, right;
	
	public PlusExpression(Expression left, Expression right) {
		this.left = left;
		this.right = right;
	}
	
	@Override
	public Object eval(Environment env) {
		Object par1 = this.left.eval(env);
		Object par2 = this.right.eval(env);
		String type1 = par1.getClass().getCanonicalName();
		String type2 = par2.getClass().getCanonicalName();
		if(!type1.equals(type2)) {
			throw new RuntimeException("Plus operator cannot be applied to different type of objects: " + type1 + " and " + type2 + " for " + this.left.toString() + " and " + this.right.toString());
		}
		if (par1 instanceof java.lang.Double) {
			return Double.valueOf((double)par1 + (double)par2);
		}else if (par1 instanceof java.lang.Integer) {
			return Integer.valueOf((int)par1 + (int)par2);
		}else if(par1 instanceof java.lang.Short) {
			return Short.valueOf((short) ((short)par1 + (short)par2));
		}else if (par1 instanceof java.lang.Byte) {
			return Byte.valueOf((byte) ((byte)par1 + (byte)par2));
		}else if (par1 instanceof java.lang.Long){
			return Long.valueOf((long)par1 + (long)par2);
		}else if (par1 instanceof java.lang.Character) {
			return Character.valueOf((char) ((char)par1 + (char)par2));
		}else if(par1 instanceof java.lang.String) {
			return String.valueOf(par1).concat(String.valueOf(par2));
		}else {
			throw new RuntimeException("Arguments cannot be summed: " + par1 + " and " + par2 + " of types " + type1 + " and " + type2);
		}
	}
	
	@Override
	public String toString() {
		return "Plus(" + left + " + " + right + ")";
	}

}
