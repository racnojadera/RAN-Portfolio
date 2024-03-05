import java.awt.*;
import java.awt.geom.*;

/**
 * contains the drawings that make a house. Imports the values from DrawingComponent.
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

public class House
{
    private double x, y, size;
    private Color color;

    /**
     * Constructor for objects of class House
     */
    public House(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    public void draw(Graphics2D g2d)
    {
        Rectangle2D.Double houseBase = new Rectangle2D.Double(x, y, size*1.4, size);
        g2d.setColor(color);
        g2d.fill(houseBase);
        
        Rectangle2D.Double houseDoor = new Rectangle2D.Double(x+size*0.55, y+size*0.5, size*0.3, size*0.48);
        g2d.setColor(Color.GRAY);
        g2d.fill(houseDoor);
        
        Rectangle2D.Double windowLeft1 = new Rectangle2D.Double(x+size*0.05, y+size*0.5, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowLeft1);
        
        Rectangle2D.Double windowLeft2 = new Rectangle2D.Double(x+size*0.26, y+size*0.5, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowLeft2);
        
        Rectangle2D.Double windowLeft3 = new Rectangle2D.Double(x+size*0.05, y+size*0.1, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowLeft3);
        
        Rectangle2D.Double windowLeft4 = new Rectangle2D.Double(x+size*0.26, y+size*0.1, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowLeft4);
        
        Rectangle2D.Double windowRight1 = new Rectangle2D.Double(x+size*1.18, y+size*0.5, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowRight1);
        
        Rectangle2D.Double windowRight2 = new Rectangle2D.Double(x+size*0.97, y+size*0.5, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowRight2);
        
        Rectangle2D.Double windowRight3 = new Rectangle2D.Double(x+size*1.18, y+size*0.1, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowRight3);
        
        Rectangle2D.Double windowRight4 = new Rectangle2D.Double(x+size*0.97, y+size*0.1, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowRight4);
        
        Rectangle2D.Double windowMiddle = new Rectangle2D.Double(x+size*0.61, y+size*0.1, size*0.17, size*0.35);
        g2d.setColor(Color.BLACK);
        g2d.fill(windowMiddle);
        
        Rectangle2D.Double basement = new Rectangle2D.Double(x, y+size*0.9, size*1.4, size*0.1);
        g2d.setColor(Color.BLACK);
        g2d.fill(basement);
        
        Rectangle2D.Double steps1 = new Rectangle2D.Double(x+size*0.45, y+size*0.95, size*0.5, size*0.05);
        g2d.setColor(Color.WHITE);
        g2d.fill(steps1);
        
        Rectangle2D.Double steps2 = new Rectangle2D.Double(x+size*0.5, y+size*0.90, size*0.4, size*0.05);
        g2d.setColor(Color.WHITE);
        g2d.fill(steps2);
        
        Rectangle2D.Double doorFrameLeft = new Rectangle2D.Double(x+size*0.52, y+size*0.5, size*0.05, size*0.45);
        g2d.setColor(Color.WHITE);
        g2d.fill(doorFrameLeft);
        
        Rectangle2D.Double doorFrameRight = new Rectangle2D.Double(x+size*0.83, y+size*0.5, size*0.05, size*0.45);
        g2d.setColor(Color.WHITE);
        g2d.fill(doorFrameRight);
        
        Rectangle2D.Double doorFrameTop = new Rectangle2D.Double(x+size*0.52, y+size*0.5, size*0.32, size*0.05);
        g2d.setColor(Color.WHITE);
        g2d.fill(doorFrameTop);
        
        Rectangle2D.Double roofTopFence = new Rectangle2D.Double(x, y-size*0.2, size*1.3, size*0.02);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopFence);
        
        Rectangle2D.Double roofTopGrill1 = new Rectangle2D.Double(x, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill1);
        
        Rectangle2D.Double roofTopGrill2 = new Rectangle2D.Double(x+size*0.1, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill2);
        
        Rectangle2D.Double roofTopGrill3 = new Rectangle2D.Double(x+size*0.2, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill3);
        
        Rectangle2D.Double roofTopGrill4 = new Rectangle2D.Double(x+size*0.3, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill4);
        
        Rectangle2D.Double roofTopGrill5 = new Rectangle2D.Double(x+size*0.4, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill5);
        
        Rectangle2D.Double roofTopGrill6 = new Rectangle2D.Double(x+size*0.5, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill6);
        
        Rectangle2D.Double roofTopGrill7 = new Rectangle2D.Double(x+size*0.6, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill7);
        
        Rectangle2D.Double roofTopGrill8 = new Rectangle2D.Double(x+size*0.7, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill8);
        
        Rectangle2D.Double roofTopGrill9 = new Rectangle2D.Double(x+size*0.8, y-size*0.2, size*0.02, size*0.2);
        g2d.setColor(Color.GRAY);
        g2d.fill(roofTopGrill9);
        
        Rectangle2D.Double roofTop = new Rectangle2D.Double(x+size*0.9, y-size*0.4, size*0.5, size*0.4);
        g2d.setColor(color);
        g2d.fill(roofTop);
    }
}
