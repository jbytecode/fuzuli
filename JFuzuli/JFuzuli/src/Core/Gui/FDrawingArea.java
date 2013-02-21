
package Core.Gui;

import Interpreter.Environment;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.LayoutManager;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;


public class FDrawingArea extends JPanel {

    BufferedImage bufferedImage;

    public BufferedImage getBufferedImage() {
        return bufferedImage;
    }

    public void setBufferedImage(BufferedImage bufferedImage) {
        this.bufferedImage = bufferedImage;
    }
    
    public void createBufferedImage(int width, int height, int type){
        this.bufferedImage = new BufferedImage(width, height, type);
    }
    
    
    public FDrawingArea(LayoutManager layout, boolean isDoubleBuffered) {
        super(layout, isDoubleBuffered);
    }

    public FDrawingArea(LayoutManager layout) {
        super(layout);
    }

    public FDrawingArea(boolean isDoubleBuffered) {
        super(isDoubleBuffered);
    }

    public FDrawingArea() {
    }

    @Override
    public void paint(Graphics g) {
            super.paint(g);
            g.drawImage(this.bufferedImage, 0, 0, this);
    }
    
    public static FDrawingArea createDrawingArea(double width, double height, Environment env){
        FDrawingArea fd = new FDrawingArea();
        fd.setLocation(0, 0);
        fd.setSize((int)width, (int)height);
        fd.createBufferedImage((int)width, (int)height, BufferedImage.TYPE_INT_ARGB);
        fd.getBufferedImage().getGraphics().create();
        fd.repaint();
        return fd;
    }
    
    public static Graphics2D getGraphicsOfDrawingArea(FDrawingArea fd, Environment env){
        return((Graphics2D)fd.getBufferedImage().getGraphics());
    }
    
    public static void refreshDrawingArea(FDrawingArea fd, Environment env){
        fd.repaint();
    }
    
   
    
    
}
