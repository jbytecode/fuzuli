
package Core.Gui;

import java.awt.GraphicsConfiguration;
import java.awt.HeadlessException;
import javax.swing.JFrame;

public class FFrame extends JFrame implements FuzuliEventHandler {

    public FFrame() throws HeadlessException {
        super();
    }

    public FFrame(GraphicsConfiguration gc) {
        super(gc);
    }

    public FFrame(String title) throws HeadlessException {
        super(title);
    }

    public FFrame(String title, GraphicsConfiguration gc) {
        super(title, gc);
    }

    @Override
    public void setEventListener(FuzuliEventListener fel) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    
}
