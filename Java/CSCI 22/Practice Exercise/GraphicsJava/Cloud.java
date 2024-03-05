import java.awt.*;
import java.awt.geom.*;

/**
 * Write a description of class Cloud here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Cloud
{
    // instance variables - replace the example below with your own
    private double x, y, size, width, height;
    private Color color;

    /**
     * Constructor for objects of class Cloud
     */
    public Cloud(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Ellipse2D.Double cloud1 = new Ellipse2D.Double(x+size*0.8, y+size*0.3, size*0.7, size*0.3);
        Ellipse2D.Double cloud2 = new Ellipse2D.Double(x+size*0.4, y-size*1.8, size*0.3, size*0.9);
        Ellipse2D.Double cloud3 = new Ellipse2D.Double(x-size*0.6, y-size*1.2, size*0.35, size*0.2);
        Ellipse2D.Double cloud4 = new Ellipse2D.Double(x-size*1.3, y-size*0.7, size*0.5, size*0.6);
        Ellipse2D.Double cloud5 = new Ellipse2D.Double(x+size*0.7, y+size*0.5, size*0.2, size*0.7);
        g2d.setColor(color);
        g2d.fill(cloud1);
        g2d.fill(cloud2);
        g2d.fill(cloud3);
        g2d.fill(cloud4);
        g2d.fill(cloud5);
    }
}
