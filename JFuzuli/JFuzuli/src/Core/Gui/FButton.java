
package Core.Gui;

import javax.swing.Action;
import javax.swing.Icon;
import javax.swing.JButton;


public class FButton extends JButton implements FuzuliEventHandler {

    FuzuliEventListener eventListener;
   
    @Override
    public void setEventListener(FuzuliEventListener fel){
        this.eventListener = fel;
        this.addActionListener(fel);
    }
    
    public FButton() {
        
    }

    public FButton(Icon icon) {
        super(icon);
    }

    public FButton(String text) {
        super(text);
    }

    public FButton(Action a) {
        super(a);
    }

    public FButton(String text, Icon icon) {
        super(text, icon);
    }
    
    
}
