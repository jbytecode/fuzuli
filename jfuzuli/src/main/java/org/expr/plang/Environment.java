package org.expr.plang;

import java.util.Map;
import java.util.HashMap;

public class Environment {

	Map<String, Object> objects;
	
	public Environment() {
		this.objects = new HashMap<>();
	}
	
	public void setObject(String name, Object obj) {
		this.objects.put(name, obj);
	}
	
	public Object getObject(String name) {
		Object obj = this.objects.get(name);
		if(obj == null) {
			throw new RuntimeException("Object " + name + " not found");
		}
		return obj;
	}
	
	public Map<String, Object> getObjectMappings() {
		return this.objects;
	}
}
