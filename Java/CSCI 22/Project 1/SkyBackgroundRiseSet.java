/**
 * Displays the sky when it is sunrise or sunset. Also implements the interface drawingobject.
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

import java.awt.*;
import java.awt.geom.*;

public class SkyBackgroundRiseSet implements DrawingObject
{
    private double x, y, origX, origY, size, degrees;
    private Color colorTop, colorBottom;
    private GradientPaint skyColor;
    
    /**
     * Constructor for objects of class SkyBackgroundRiseSet
     * @param x sets the location horizontally
     * @param y sets the location vertically
     * @param s sets the size
     * @param r gets a value for red
     * @param g gets a value for green
     * @param b gets a value for blue
     */
    public SkyBackgroundRiseSet(double x, double y, double s, int r, int g, int b)
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
     * Paints the color of the sky when it is sunrise or sunset time
     */
    public void draw(Graphics2D g2d)
    {
        Float middleX = (float)(x*0.5); 
        Float bottomY = (float)(y*0.4);

        GradientPaint skyColor = new GradientPaint(middleX, 30, colorTop, middleX, bottomY-50, colorBottom); //https://www.pictorem.com/collection/900_Rizwana-Khan_Red%20to%20Black%20Gradient%20Background.jpg
        Rectangle2D background = new Rectangle2D.Double(0, 0, x, y*size*0.4);
        g2d.setPaint(skyColor);
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
        colorBottom = new Color(r+128, g+8, b-46,t);
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
