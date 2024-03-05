import java.awt.*;
import java.awt.geom.*;

/**
 * contains the drawings that make a cloud. Imports the values from DrawingComponent.
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

public class Cloud
{
    private double x, y, size, width, height;
    private Color color;

    public Cloud(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Ellipse2D.Double cloud1 = new Ellipse2D.Double(x+size*0.05, y+size*0.1, size, size*0.4);
        Ellipse2D.Double cloud2 = new Ellipse2D.Double(x+size*0.5, y+size*0.02, size*0.45, size*0.45);
        Ellipse2D.Double cloud3 = new Ellipse2D.Double(x+size*0.13, y-size*0.01, size*0.6, size*0.5);
        
        g2d.setColor(color);
        g2d.fill(cloud1);
        g2d.fill(cloud2);
        g2d.fill(cloud3);
    }
}
