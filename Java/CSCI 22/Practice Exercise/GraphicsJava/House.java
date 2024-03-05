import java.awt.*;
import java.awt.geom.*;

/**
 * Write a description of class House here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class House
{
    // instance variables - replace the example below with your own
    private double x, y, width, height;
    private Color color;

    /**
     * Constructor for objects of class House
     */
    public House(double x, double y, double w, double h, Color c)
    {
        this.x = x;
        this.y = y;
        this.width = w;
        this.height = h;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Rectangle2D.Double houseBase = new Rectangle2D.Double(x, y, width, height);
        g2d.setColor(color);
        g2d.fill(houseBase);
        
        Rectangle2D.Double houseDoor = new Rectangle2D.Double(x+(width/3)-(width/10), y+(height/4), width/5, height/3);
        g2d.setColor(Color.BLACK);
        g2d.fill(houseDoor);
        
        Rectangle2D.Double window = new Rectangle2D.Double(x+(width/2)+20, y+(height/4), width/4, width/4);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(window);
    }
}
