import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;

/**
 * Write a description of class DrawingComponent here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class DrawingComponent extends JComponent
{
    // instance variables - replace the example below with your own
    private int width, height;

    /**
     * Constructor for objects of class DrawingComponent
     */
    public DrawingComponent(int w, int h)
    {
       width = w;
       height = h;
    }

    protected void paintComponent(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;
        RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHints(rh);
        
        Rectangle2D.Double background = new Rectangle2D.Double(0, 0, width, height);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(background);
        
        Tree tree1 = new Tree(20, 400, 50, 200, Color.RED);
        tree1.draw(g2d);
        
        Tree tree2 = new Tree(730, 400, 50, 200, Color.YELLOW);
        tree2.draw(g2d);
        
        Car car1 = new Car(300, 530, 80, 30, Color.BLUE);
        car1.draw(g2d);
        
        Car car2 = new Car(200, 530, 80, 30, Color.BLUE);
        car2.draw(g2d);
        
        Cloud cloud1 = new Cloud(100, 300, 200, Color.WHITE);
        cloud1.draw(g2d);
        
        Cloud cloud2 = new Cloud(300, 400, 350, Color.WHITE);
        cloud2.draw(g2d);
        
        House house1 = new House(500, 450, 100, 150, Color.YELLOW);
        house1.draw(g2d);
        
        House house2 = new House(400, 450, 100, 150, Color.RED);
        house2.draw(g2d);
        
        Sun sun = new Sun(20, 20, 100, 100, new Color(252, 212, 64));
        sun.draw(g2d);
    }
}
