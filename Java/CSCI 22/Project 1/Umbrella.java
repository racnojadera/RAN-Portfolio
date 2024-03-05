/**
 * Displays an umbrella. Also implements the interface drawingobject.
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

public class Umbrella implements DrawingObject //http://clipart-library.com/img/798772.jpg
{
    private double x, y, origX, origY, size, degrees;
    private Color color;

    /**
     * Constructor for objects of class Umbrella
     * @param x sets the location horizontally
     * @param y sets the location vertically
     * @param s sets the size
     * @param r gets a value for red
     * @param g gets a value for green
     * @param b gets a value for blue
     */
    public Umbrella(double x, double y, double s, int r, int g, int b)
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
     * Draws the umbrella
     */
    public void draw(Graphics2D g2d)
    {
        g2d.rotate(Math.toRadians(degrees+75),x,y+size);
        
        Line2D.Double stick = new Line2D.Double(x,y-size,x,y+size);
        
        Path2D.Double leftFrontUmbrella = new Path2D.Double();
        leftFrontUmbrella.moveTo(x,y-size*0.95);
        leftFrontUmbrella.curveTo(x-size*0.4,y-size*0.9,x-size*0.7,y-size*0.8,x-size,y-size*0.4);
        leftFrontUmbrella.curveTo(x-size*0.75,y-size*0.45,x-size*0.60,y-size*0.45,x-size*0.35, y-size*0.4);
        leftFrontUmbrella.curveTo(x-size*0.3,y-size*0.8,x-size*0.1,y-size*0.9,x,y-size*0.95);
        
        Path2D.Double rightFrontUmbrella = new Path2D.Double();
        rightFrontUmbrella.moveTo(x,y-size*0.95);
        rightFrontUmbrella.curveTo(x+size*0.4,y-size*0.9,x+size*0.7,y-size*0.8,x+size,y-size*0.4);
        rightFrontUmbrella.curveTo(x+size*0.75,y-size*0.45,x+size*0.60,y-size*0.45,x+size*0.35, y-size*0.4);
        rightFrontUmbrella.curveTo(x+size*0.3,y-size*0.8,x+size*0.1,y-size*0.9,x,y-size*0.95);
        
        Path2D.Double middleFrontUmbrella = new Path2D.Double();
        middleFrontUmbrella.moveTo(x,y-size*0.95);
        middleFrontUmbrella.curveTo(x-size*0.1,y-size*0.9,x-size*0.3,y-size*0.8,x-size*0.35,y-size*0.4);
        middleFrontUmbrella.curveTo(x-size*0.1,y-size*0.45,x+size*0.1,y-size*0.45,x+size*0.35,y-size*0.4);
        middleFrontUmbrella.curveTo(x+size*0.3,y-size*0.8,x+size*0.1,y-size*0.9,x,y-size*0.95);
        
        Path2D.Double backUmbrella = new Path2D.Double();
        backUmbrella.moveTo(x-size,y-size*0.4);
        backUmbrella.curveTo(x-size*0.92,y-size*0.38,x-size*0.84,y-size*0.32,x-size*0.75,y-size*0.3);
        backUmbrella.curveTo(x-size*0.50,y-size*0.3,x-size*0.40,y-size*0.25,x-size*0.3, y-size*0.22);
        backUmbrella.curveTo(x-size*0.2,y-size*0.25,x-size*0.1,y-size*0.30,x,y-size*0.25);
        backUmbrella.curveTo(x+size*0.1,y-size*0.30,x+size*0.2,y-size*0.25,x+size*0.3,y-size*0.22);
        backUmbrella.curveTo(x+size*0.40,y-size*0.25,x+size*0.50,y-size*0.3,x+size*0.75,y-size*0.3);
        backUmbrella.curveTo(x+size*0.84,y-size*0.32,x+size*0.92,y-size*0.38,x+size,y-size*0.4);
        backUmbrella.curveTo(x+size*0.7,y-size*0.8,x+size*0.4,y-size*0.9,x,y-size*0.95);
        backUmbrella.curveTo(x-size*0.4,y-size*0.9,x-size*0.7,y-size*0.8,x-size,y-size*0.4);
        
        g2d.setColor(new Color(179,180,182,255));
        g2d.fill(backUmbrella);
        
        g2d.setColor(Color.BLACK);
        g2d.draw(backUmbrella);
        g2d.setStroke(new BasicStroke((float)(size*0.02)));
        g2d.draw(stick);
        g2d.setStroke(new BasicStroke((float)(1)));
        g2d.draw(leftFrontUmbrella);
        g2d.draw(rightFrontUmbrella);
        g2d.draw(middleFrontUmbrella);

        g2d.setColor(color);
        g2d.fill(middleFrontUmbrella);
        
        g2d.setColor(new Color(33,170,225,255));
        g2d.fill(leftFrontUmbrella);
        g2d.fill(rightFrontUmbrella);
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
