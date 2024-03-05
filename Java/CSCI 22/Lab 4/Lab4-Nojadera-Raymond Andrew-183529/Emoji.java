/**
 * The actual drawing.
 * Also modifies the drawing based on the button clicked in the controls.
 *
 * @author Raymond Andrew C. Nojaera
 * @version March 7, 2019
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

import java.awt.*;
import java.awt.geom.*;

public class Emoji
{
    private double x, y, size, degrees;
    private Color color;
    private int darkMode;
    
    public Emoji(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        size = s;
        color = c;
        degrees = 0;
        darkMode = 0;
    }
    
    public void draw(Graphics2D g2d)
    {
        g2d.rotate(Math.toRadians(degrees),x+size/2, y+size/2);
        
        Path2D.Double cowboyHatLeftSide = new Path2D.Double();
        cowboyHatLeftSide.moveTo(x+(size/2)-size*0.30, y+size*0.1);
        cowboyHatLeftSide.curveTo(x+(size/2)-size*0.40, y-size*0.30, x+(size/2)-size*0.7, y+size*0.15, x+(size/2)-size*0.49, y+size*0.4); 
        
        Path2D.Double cowboyHatRightSide = new Path2D.Double();
        cowboyHatRightSide.moveTo(x+(size/2)+size*0.30, y+size*0.1);
        cowboyHatRightSide.curveTo(x+(size/2)+size*0.40, y-size*0.30, x+(size/2)+size*0.7, y+size*0.15, x+(size/2)+size*0.49, y+size*0.4);
        
        
        Ellipse2D.Double face = new Ellipse2D.Double(x, y, size, size);

        Ellipse2D.Double nose = new Ellipse2D.Double(x+(size/2)-size*0.05, y+(size/2)-size*0.05, size*0.1, size*0.1);
        
        Ellipse2D.Double leftEye = new Ellipse2D.Double(x+(size/2)-size*0.20, y+(size/2)-size*0.30, size*0.1, size*0.3);
        
        Ellipse2D.Double rightEye = new Ellipse2D.Double(x+(size/2)+size*0.10, y+(size/2)-size*0.30, size*0.1, size*0.3);
        
        Path2D.Double cowboyHatTop = new Path2D.Double();
        cowboyHatTop.moveTo(x+(size/2)-size*0.30, y+size*0.1);
        cowboyHatTop.lineTo(x+(size/2)-size*0.25, y-size*0.25);
        cowboyHatTop.curveTo(x+(size/2)-size*0.15, y-size*0.35, x+(size/2)+size*0.15, y-size*0.35, x+(size/2)+size*0.25, y-size*0.25);
        cowboyHatTop.lineTo(x+(size/2)+size*0.30, y+size*0.1);
        cowboyHatTop.curveTo(x+(size/2)+size*0.15, y+size*0.20, x+(size/2)-size*0.15, y+size*0.20, x+(size/2)-size*0.30, y+size*0.1);
        
        Path2D.Double mouth = new Path2D.Double();
        mouth.moveTo(x+(size/2)-size*0.35, y+(size/2)+size*0.05);
        mouth.curveTo(x+(size/2)-size*0.25, y+(size/2)+size*0.45, x+(size/2)+size*0.25, y+(size/2)+size*0.45, x+(size/2)+size*0.35, y+(size/2)+size*0.05);
        mouth.curveTo(x+(size/2)+size*0.25, y+(size/2)+size*0.17, x+(size/2)-size*0.25, y+(size/2)+size*0.17, x+(size/2)-size*0.35, y+(size/2)+size*0.05);
        
        Path2D.Double teeth = new Path2D.Double();
        teeth.moveTo(x+(size/2)-size*0.35, y+(size/2)+size*0.05);
        teeth.curveTo(x+(size/2)-size*0.25, y+(size/2)+size*0.17, x+(size/2)+size*0.25, y+(size/2)+size*0.17, x+(size/2)+size*0.35, y+(size/2)+size*0.05);
        teeth.curveTo(x+(size/2)+size*0.33, y+(size/2)+size*0.07, x+(size/2)+size*0.31, y+(size/2)+size*0.09, x+(size/2)+size*0.30, y+(size/2)+size*0.10);
        teeth.curveTo(x+(size/2)+size*0.30, y+(size/2)+size*0.22, x+(size/2)-size*0.25, y+(size/2)+size*0.25, x+(size/2)-size*0.30, y+(size/2)+size*0.10);
        
        if(darkMode == 0)
        {
            g2d.setColor(new Color(180, 125, 73));
            g2d.fill(cowboyHatLeftSide);
            g2d.fill(cowboyHatRightSide);
        
            g2d.setColor(color);
            g2d.fill(face);
        
            g2d.setColor(new Color(180, 125, 73));
            g2d.fill(nose);
            g2d.fill(leftEye);
            g2d.fill(rightEye);
            g2d.fill(cowboyHatTop);
            g2d.fill(mouth);
        
            g2d.setColor(Color.WHITE);
            g2d.fill(teeth);
        }
        else if(darkMode == 1)
        {
            g2d.setColor(new Color(75, 130, 182));
            g2d.fill(cowboyHatLeftSide);
            g2d.fill(cowboyHatRightSide);
            
            g2d.setColor(new Color(10, 60, 197));
            g2d.fill(face);
            
            g2d.setColor(new Color(75, 130, 182));
            g2d.fill(nose);
            g2d.fill(leftEye);
            g2d.fill(rightEye);
            g2d.fill(cowboyHatTop);
            g2d.fill(mouth);
            
            g2d.setColor(Color.BLACK);
            g2d.fill(teeth);
        }
    }
    
    public void adjustX(double distance)
    {
        x += distance;
    }
    
    public void adjustY(double distance)
    {
        y += distance;
    }
    
    public void adjustSize(double increase)
    {
        size += increase;
        x -= increase/2;
        y -= increase/2;
    }
    
    public void rotate(double rotation)
    {
        degrees += rotation;
    }
    
    public void setLight()
    {
        darkMode = 0;
    }
    
    public void setDark()
    {
        darkMode = 1;
    }
}