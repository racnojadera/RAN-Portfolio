
/**
 * Contains the stage/drawings of the program.
 * Initializes the actual drawings.
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

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

public class EmojiCanvas extends JComponent
{
    private int width, height;
    private Color backgroundColor;
    private Emoji emoji;
    
    public EmojiCanvas(int w, int h, Color c)
    {
        width = w;
        height = h;
        backgroundColor = c;
        emoji = new Emoji((width-150)/2, (height-150)/2, 150, new Color(245,195,58));
        setPreferredSize(new Dimension(width, height));
    }
    
    @Override
    protected void paintComponent(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;
        
        RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHints(rh);
        
        Rectangle2D.Double background = new Rectangle2D.Double(0, 0, width, height);
        g2d.setColor(backgroundColor);
        g2d.fill(background);
        
        emoji.draw(g2d);
    }
    
    public void setBackgroundColor(Color bgColor)
    {
        backgroundColor = bgColor;
    }
    
    public Emoji getEmoji()
    {
        return emoji;
    }
}