import java.awt.*;
import java.awt.geom.*;

/**
 * contains the drawings that make a bird. Imports the values from DrawingComponent.
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

public class Bird
{
    private double x, y, size;
    private Color color;

    public Bird(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Ellipse2D.Double leftWing = new Ellipse2D.Double(x, y, size*0.5, size*0.5);
        g2d.setColor(color);
        g2d.fill(leftWing);
        
        Ellipse2D.Double rightWing = new Ellipse2D.Double(x+size*0.45, y, size*0.5, size*0.5);
        g2d.setColor(color);
        g2d.fill(rightWing);
        
        Ellipse2D.Double leftWingSet = new Ellipse2D.Double(x-size*0.02, y+size*0.08,size*0.53, size*0.53);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(leftWingSet);
        
        Ellipse2D.Double rightWingSet = new Ellipse2D.Double(x+size*0.45, y+size*0.08, size*0.53, size*0.53);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(rightWingSet);
    }
}
