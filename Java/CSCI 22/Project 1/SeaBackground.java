/**
 * Displays the Sea. Also implements the interface drawingobject.
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

public class SeaBackground implements DrawingObject
{
    private double x, y, origX, origY, size, degrees;
    private Color colorTop, colorBottom;
    private GradientPaint seaColor;
    
    /**
     * Constructor for objects of class SeaBackground
     * @param x sets the location horizontally
     * @param y sets the location vertically
     * @param s sets the size
     * @param r gets a value for red
     * @param g gets a value for green
     * @param b gets a value for blue
     */
    public SeaBackground(double x, double y, double s, int r, int g, int b)
    {
        this.x = x;
        this.y = y;
        origX = x;
        origY = y;
        size = s;
        degrees = 0;
        
        resetColor(r,g,b,255);
    }
    
    /**
     * Draws the sea
     */
    public void draw(Graphics2D g2d)
    {
        Float middleX = (float)(x*0.5);
        Float topY = (float)(y*0.4);
        Float bottomY = (float)(y*0.6);

        GradientPaint seaColor = new GradientPaint(middleX, topY, colorTop, middleX, bottomY-50, colorBottom); //https://stackoverflow.com/questions/10273949/double-cannot-be-dereferenced
        Rectangle2D background = new Rectangle2D.Double(0, y*size*0.4, x, y*size*0.2);
        g2d.setPaint(seaColor);
        g2d.fill(background);
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
    public void resetColor(int r, int g, int b,  int t)
    {
        colorTop = new Color(r,g,b,t);
        colorBottom = new Color(r+63, g+68, b+35,t);
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
