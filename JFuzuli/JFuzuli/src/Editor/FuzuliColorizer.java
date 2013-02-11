package Editor;

import java.awt.Color;
import java.awt.Font;
import javax.swing.SwingUtilities;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.BadLocationException;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

public class FuzuliColorizer implements DocumentListener {

    SimpleAttributeSet style_paranth;
    SimpleAttributeSet style_string;
    SimpleAttributeSet style_digit;
    SimpleAttributeSet style_text;
    SimpleAttributeSet style_iden;
    SimpleAttributeSet style_comment;
    
    StyledDocument doc;
    MainFrame mf;

    public FuzuliColorizer(MainFrame mf) {
        this.mf = mf;
        this.doc = mf.getTextPane().getStyledDocument();
        doc.addDocumentListener(this);
        constructColors();
    }

    public final void constructColors() {
        style_paranth = new SimpleAttributeSet();
        StyleConstants.setForeground(style_paranth, Color.BLUE);
        StyleConstants.setFontFamily(style_paranth, Font.MONOSPACED);
        StyleConstants.setFontSize(style_paranth, 16);
        StyleConstants.setBold(style_paranth, true);
        
        style_digit = new SimpleAttributeSet();
        StyleConstants.setForeground(style_digit, Color.MAGENTA);
        StyleConstants.setFontFamily(style_digit, Font.MONOSPACED);
        StyleConstants.setFontSize(style_digit, 14);
        StyleConstants.setBold(style_digit, true);
        
        style_string = new SimpleAttributeSet();
        StyleConstants.setForeground(style_string, Color.DARK_GRAY);
        StyleConstants.setFontFamily(style_string, Font.MONOSPACED);
        StyleConstants.setFontSize(style_string, 14);
        StyleConstants.setBold(style_string, true);
        
        style_text = new SimpleAttributeSet();
        StyleConstants.setForeground(style_text, Color.RED);
        StyleConstants.setFontFamily(style_text, Font.DIALOG_INPUT);
        StyleConstants.setFontSize(style_text, 14);
        StyleConstants.setBold(style_text, true);
       
        
        style_iden = new SimpleAttributeSet();
        StyleConstants.setForeground(style_iden, Color.BLACK);
        StyleConstants.setFontFamily(style_iden, Font.MONOSPACED);
        StyleConstants.setFontSize(style_iden, 14);
        StyleConstants.setBold(style_iden, true);
            
        style_comment = new SimpleAttributeSet();
        StyleConstants.setForeground(style_comment, new Color(50, 155, 50));
        StyleConstants.setFontFamily(style_comment, Font.MONOSPACED);
        StyleConstants.setFontSize(style_comment, 14);
        StyleConstants.setBold(style_comment, true);
        
        
    }

    public void updateColors() throws BadLocationException {
        int len = this.doc.getLength();
        for (int i = 0; i < len ; i++) {
            if (doc.getText(i, 1).equals("(") || doc.getText(i, 1).equals(")")) {
                doc.setCharacterAttributes(i, 1, style_paranth, true);
            }else if (Character.isDigit(doc.getText(i, 1).charAt(0)) || doc.getText(i, 1).charAt(0)=='.') {
                doc.setCharacterAttributes(i, 1, style_digit, true);
            }else if (doc.getText(i, 1).equals("\"") ) {
                doc.setCharacterAttributes(i, 1, style_string, true);
                while (true){
                    i++;
                    if(i == len-1){
                        break;
                    }
                    if (doc.getText(i, 1).equals("\"") ) {
                        doc.setCharacterAttributes(i, 1, style_string, true);
                        break;
                    }
                    doc.setCharacterAttributes(i, 1, style_text, true);
                }
            }else if (Character.isLetter(doc.getText(i, 1).charAt(0))) {
                doc.setCharacterAttributes(i, 1, style_iden, true);
            }else if (doc.getText(i, 1).charAt(0)=='#') {
                while(true){
                    if(doc.getText(i, 1).charAt(0)=='\n'){
                        break;
                    }
                    doc.setCharacterAttributes(i, 1, style_comment, true);
                    i++;
                }
            }
        }
    }

    @Override
    public void insertUpdate(DocumentEvent e) {

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    updateColors();
                    mf.updateOutput();
                } catch (Exception exc) {
                    //System.out.println(exc);
                }
            }
        });
        
    }

    
    
    @Override
    public void removeUpdate(DocumentEvent e) {
    }

    @Override
    public void changedUpdate(DocumentEvent e) {
        
        
        
    }
}
