import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;

/**
 * Canvas of the application. Displays all of the drawings from different classes.
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

public class DrawingComponent extends JComponent
{   
    private int width, height;
    private Tree tree1, tree2;
    private Cloud cloud1, cloud2;
    private House house1, house2;
    private Car car1, car2;
    private Bird bird1, bird2, bird3;
    private Sun sun;
    
    /**
     * Constructor for objects of class DrawingComponent
     */
    public DrawingComponent(int w, int h)
    {
       width = w;
       height = h;
    }

    protected void paintComponent(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;
        RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHints(rh);
        
        Rectangle2D.Double background = new Rectangle2D.Double(0, 0, width, height);
        g2d.setColor(new Color(100, 149, 237));
        g2d.fill(background);
        
        Tree tree1 = new Tree(50, 400, 200, new Color(212, 91, 18));
        tree1.draw(g2d);
        
        Tree tree2 = new Tree(680, 400, 200, new Color(243, 188, 46));
        tree2.draw(g2d);
        
        Cloud cloud1 = new Cloud(100, 100, 250, Color.WHITE);
        cloud1.draw(g2d);
        
        Cloud cloud2 = new Cloud(400,20, 250, Color.WHITE);
        cloud2.draw(g2d);
        
        House house1 = new House(420, 425, 140, new Color(255, 203, 164));
        house1.draw(g2d);
        
        House house2 = new House(150, 425, 140, new Color(126, 249, 255));
        house2.draw(g2d);
        
        Car car1 = new Car(480, 520, 80, Color.RED);
        car1.draw(g2d);
        
        Car car2 = new Car(200, 520, 80, Color.BLUE);
        car2.draw(g2d);
        
        Bird bird1 = new Bird(600, 250, 80, Color.BLACK);
        bird1.draw(g2d);
        
        Bird bird2 = new Bird(575, 200, 40, Color.BLUE);
        bird2.draw(g2d);
        
        Bird bird3 = new Bird(625, 150, 20, Color.BLACK);
        bird3.draw(g2d);
        
        Sun sun = new Sun(20, 20, 100, new Color(252, 212, 64));
        sun.draw(g2d);
    }
}
