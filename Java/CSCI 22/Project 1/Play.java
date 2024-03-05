/**
 * Displays a play-like icon on the right top of the screen. Also implements the interface drawingobject.
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

public class Play implements DrawingObject
{
    private double x, y, origX, origY, size, degrees;
    private Color color;
    
    /**
     * Constructor for objects of class Play
     * @param x sets the location horizontally
     * @param y sets the location vertically
     * @param s sets the size
     * @param r gets a value for red
     * @param g gets a value for green
     * @param b gets a value for blue
     */
    public Play(double x, double y, double s, int r, int g, int b)
    {
        this.x = x;
        this.y = y;
        origX = x;
        origY = y;
        size = s;
        degrees = 0;
        
        resetColor(r,g,b,127);
    }
    
    /**
     * Draws the play icon
     */
    public void draw(Graphics2D g2d)
    {
        Path2D.Double playIcon = new Path2D.Double();
        playIcon.moveTo(x-size*0.5, y-size*0.5);
        playIcon.lineTo(x+size*0.5, y);
        playIcon.lineTo(x-size*0.5, y+size*0.5);
        playIcon.lineTo(x-size*0.5, y-size*0.5);
        g2d.setColor(color);
        g2d.fill(playIcon);
    }
    
    /**
     * Adjusts the location horizontally
     * @param xDistance adjusts the location how many units from it (towards the right side)
     */
    public void adjustX(double xDistance)
    {
        x += xDistance;
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
        x = origX;
    }
    
    /**
     * Resets the location vertically
     */
    public void resetY()
    {
        y = origY;
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
