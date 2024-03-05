import javax.swing.*;

/**
 * Sets the width and height of the frame. Also launches the application.
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
public class DrawingTester
{
    public static void main(String[] args)
    {
        int w = 800;
        int h = 600;
        JFrame f = new JFrame();
        DrawingComponent dc = new DrawingComponent(w,h);
        f.setSize(w,h);
        f.setTitle("Raymond Andrew C. Nojadera - 183529");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.add(dc);
        f.setVisible(true);
    }
}
