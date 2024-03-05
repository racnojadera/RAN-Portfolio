import java.awt.*;
import java.awt.geom.*;

/**
 * Write a description of class Car here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Car
{
    // instance variables - replace the example below with your own
    private double x, y, width, height;
    private Color color;

    /**
     * Constructor for objects of class Car
     */
    public Car(double x, double y, double w, double h, Color c)
    {
        this.x = x;
        this.y = y;
        this.width = w;
        this.height = h;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Rectangle2D.Double carMain = new Rectangle2D.Double(x+(width/4), y, width/2, height);
        g2d.setColor(color);
        g2d.fill(carMain);
        
        Rectangle2D.Double frontBack = new Rectangle2D.Double(x, y+height/2, width, height/2);
        g2d.setColor(color);
        g2d.fill(frontBack);
        
        Ellipse2D.Double wheel1 = new Ellipse2D.Double(x+width/5, y+(height/2)+(height/6), width/5, width/5);
        g2d.setColor(Color.BLACK);
        g2d.fill(wheel1);
        
        Ellipse2D.Double wheel2 = new Ellipse2D.Double(x+(width/2)+(width/5), y+(height/2)+(height/6), width/5, width/5);
        g2d.setColor(Color.BLACK);
        g2d.fill(wheel2);
    }
}
