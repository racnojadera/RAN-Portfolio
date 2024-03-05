import java.awt.*;
import java.awt.geom.*;

/**
 * contains the drawings that make a car. Imports the values from DrawingComponent.
 *
 * @author Raymond Andrew C. Nojadera
 * @version February 21, 2019
 */

/*
I have not discussed the Java language code 
in my program with anyone other than my instructor 
or the teaching assistants assigned to this course.

I have not used Java language code obtained 
from another student, or any other unauthorized 
source, either modified or unmodified.

If any Java language code or documentation 
used in my program was obtained from another source, 
such as a text book or webpage, those have been 
clearly noted with a proper citation in the comments 
of my code.
*/

public class Car
{
    private double x, y, size;
    private Color color;

    public Car(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Ellipse2D.Double carBase = new Ellipse2D.Double(x+size*0.27, y, size*0.7, size*0.4);
        g2d.setColor(color);
        g2d.fill(carBase);
        
        Ellipse2D.Double carLength = new Ellipse2D.Double(x, y+size*0.18, size*1.2, size*0.4);
        g2d.setColor(color);
        g2d.fill(carLength);
        
        Rectangle2D.Double under = new Rectangle2D.Double(x, y+size*0.38, size*1.2, size*0.3);
        g2d.setColor(color.BLACK);
        g2d.fill(under);
        
        Ellipse2D.Double wheels1 = new Ellipse2D.Double(x+size*0.15, y+size*0.3, size*0.25, size*0.22);
        g2d.setColor(new Color(227, 222, 219));
        g2d.fill(wheels1);
        
        Ellipse2D.Double wheels2 = new Ellipse2D.Double(x+size*0.78, y+size*0.3, size*0.25, size*0.22);
        g2d.setColor(new Color(227, 222, 219));
        g2d.fill(wheels2);
        
        
        
    }
}
