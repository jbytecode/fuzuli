/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package org.expr;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import javax.servlet.jsp.JspWriter;

/**
 *
 * @author hako
 */
public class WebOutput extends PrintStream {

    JspWriter writer;

     
    
    public WebOutput(OutputStream out) throws Exception {
        super(new FileOutputStream(File.createTempFile("fuzuli", "")));
    }
    
    public void setWriter(JspWriter w){
        this.writer = w;
    }

    @Override
    public void println(Object x) {
        try{
            writer.println(x);
        }catch (Exception e){
            
        }
    }

    @Override
    public void println(String x) {
        try{
            writer.println(x);
        }catch (Exception e){
            
        }
    }

    @Override
    public void print(Object obj) {
        try{
            writer.print(obj);
        }catch (Exception e){
            
        }
    }

    @Override
    public void print(String s) {
        try{
            writer.print(s);
        }catch (Exception e){
            
        }
    }
    
 
    
    
}
