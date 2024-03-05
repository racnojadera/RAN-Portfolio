import java.awt.*;
import java.awt.geom.*;

/**
 * contains the drawings that make the sun. Imports the values from DrawingComponent.
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

public class Sun
{
    private double x, y, size;
    private Color color;

    public Sun(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Ellipse2D.Double sun = new Ellipse2D.Double(x, y, size, size);
        g2d.setColor(color);
        g2d.fill(sun);
    }
}
