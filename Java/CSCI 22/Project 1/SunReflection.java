/**
 * Draws a reflection of the sun in the sea. Also implements the interface drawingobject.
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

public class SunReflection implements DrawingObject
{
    private double x, y, origX, origY, size, degrees;
    private Color colorIn, colorOut;
    
    /**
     * Constructor for objects of class SunReflection
     * @param x sets the location horizontally
     * @param y sets the location vertically
     * @param s sets the size
     * @param r gets a value for red
     * @param g gets a value for green
     * @param b gets a value for blue
     */
    public SunReflection(double x, double y, double s, int r, int g, int b)
    {
        this.x = x;
        this.y = y;
        origX = x;
        origY = y;
        size = s;
        degrees = 0;
        colorIn = new Color(r, g, b, 255); //https://stackoverflow.com/questions/8110975/how-to-make-a-rectangle-in-graphics-in-a-transparent-colour
        colorOut = new Color(r, g, b, 0);
    }
    
    /**
     * Draws the reflection of the sun in the sea
     */
    public void draw(Graphics2D g2d)
    {
        //https://docs.oracle.com/javase/7/docs/api/java/awt/RadialGradientPaint.html
        //https://stackoverflow.com/questions/47230738/java-drawing-a-radialgradientpaint-circle-cut-into-a-rectangle
        Point2D center = new Point2D.Float((float)x,(float)y);
        float radius = (float)(size/2);
        float[] dist = {0.7f, 1.0f};
        Color[] colors = {colorIn, colorOut};
        RadialGradientPaint gradient = new RadialGradientPaint(center, radius, dist, colors);

        Ellipse2D sunReflect = new Ellipse2D.Double(x-(size*0.5), y-(size*0.5), size, size);
        g2d.setPaint(gradient);
        g2d.fill(sunReflect);
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
        y = -Math.pow((x-512),2)/2700 + 420.8;
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
        colorOut = new Color(r,g,b,0);
        colorIn = new Color(r,g,b,255);
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
