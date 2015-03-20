/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.expr.fuzuli.gui.editor;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.io.StringWriter;
import javax.swing.JTextArea;


public class FuzuliOutputStream {
    
    PrintStream printStream;
    JTextArea text;
    ByteArrayOutputStream baos;

    public PrintStream getPrintStream() {
        return printStream;
    }

    public void setPrintWriter(PrintStream printStream){
        this.printStream = printStream;
    }
    
    public String readText(){
        String text = new String(baos.toByteArray());
        baos.reset();
        return(text);
    }
    
    public FuzuliOutputStream(JTextArea text){
        this.text = text;
        baos = new ByteArrayOutputStream();
        printStream = new PrintStream(baos);
    }
    
    
}
