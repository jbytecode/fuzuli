package org.expr.plang;

public class ObjectEncapsulator {

	private Object obj;
	
	public ObjectEncapsulator(Object obj) {
		this.obj = obj;
	}
	
	public void setObject(Object obj) {
		this.obj = obj;
	}
	
	public Object getObject() {
		return this.obj;
	}
}
