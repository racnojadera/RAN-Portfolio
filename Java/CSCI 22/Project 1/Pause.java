/**
 * Displays one of the boxes seen in a pause icon. Also implements the interface drawingobject.
 *
 * @author Raymond Andrew C. Nojadera
 * @version April 5, 2019
**/
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

import java.util.*;
import java.awt.*;
import java.awt.geom.*;

public class Pause implements DrawingObject
{
    private double x1, y1, x2, y2, size, degrees;
    private Color color;
    
    /**
     * Constructor for objects of class Pause
     * @param x1 sets the starting location horizontally
     * @param y1 sets the starting location vertically
     * @param x2 sets the ending lcoation horizontally
     * @param x2 sets the ending lcoation vertically
     * @param s sets the size
     * @param r gets a value for red
     * @param g gets a value for green
     * @param b gets a value for blue
     */
    public Pause(double x1, double y1, double x2, double y2, double s, int r, int g, int b)
    {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        size = s;
        degrees = 0;
        
        resetColor(r,g,b,0);
    }
    
    /**
     * Draws one of the boxes seen in a pause icon
     */
    public void draw(Graphics2D g2d)
    {
        Line2D.Double playIcon = new Line2D.Double(x1, y1, x2, y2);
        g2d.setColor(color);
        g2d.setStroke(new BasicStroke((float)size));
        g2d.draw(playIcon);
    }
    
    /**
     * Adjusts the location horizontally
     * @param xDistance adjusts the location how many units from it (towards the right side)
     */
    public void adjustX(double xDistance)
    {
        //
    }
    
    /**
     * Adjusts the location vertically
     */
    public void adjustY()
    {
        //
    }
    
    /**
     * Resets the location horizontally
     */
    public void resetX()
    {
        //
    }
    
    /**
     * Resets the location vertically
     */
    public void resetY()
    {
        //
    }
    
    /**
     * Resets the color of based on the red green and blue values
     * @param r red
     * @param g green
     * @param b blue
     * @param t alpha/transparency
     */
    public void resetColor(int r, int g, int b, int t)
    {
        color = new Color(r,g,b,t);
    }
    
    /**
     * Adjusts the tilt
     * @param degrees how much tilt
     */
    public void adjustRotation(double degrees)
    {
        this.degrees += degrees;
    }
}
