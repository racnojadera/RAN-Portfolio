import java.awt.*;
import java.awt.geom.*;

/**
 * contains the drawings that make a tree. Imports the values from DrawingComponent.
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

public class Tree
{
    private double x, y, size;
    private Color color;

    public Tree(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Rectangle2D.Double bark = new Rectangle2D.Double(x, y, size*0.25, size);
        g2d.setColor(new Color(140, 104, 74));
        g2d.fill(bark);
        
        Ellipse2D.Double hollow = new Ellipse2D.Double(x+size*0.09, y+size*0.35, size*0.07, size*0.15);
        g2d.setColor(Color.BLACK);
        g2d.fill(hollow);
        
        Ellipse2D.Double curve1 = new Ellipse2D.Double(x-size*0.165, y-size*0.15, size*0.2, size*1.3);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(curve1);
        
        Ellipse2D.Double curve2 = new Ellipse2D.Double(x+size*0.216, y-size*0.15, size*0.2, size*1.3);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(curve2);
        
        Ellipse2D.Double leaves1 = new Ellipse2D.Double(x+size*0.07, y-size*0.08, size*0.4, size*0.3);
        Ellipse2D.Double leaves2 = new Ellipse2D.Double(x-size*0.03, y+size*0.07, size*0.25, size*0.20);
        Ellipse2D.Double leaves3 = new Ellipse2D.Double(x-size*0.22, y-size*0.07, size*0.4, size*0.3);
        Ellipse2D.Double leaves4 = new Ellipse2D.Double(x-size*0.04, y-size*0.20, size*0.45, size*0.3);
        Ellipse2D.Double leaves5 = new Ellipse2D.Double(x-size*0.17, y-size*0.26, size*0.40, size*0.35);
        
        g2d.setColor(color);
        g2d.fill(leaves1);
        g2d.fill(leaves2);
        g2d.fill(leaves3);
        g2d.fill(leaves4);
        g2d.fill(leaves5);
        
    }
}
