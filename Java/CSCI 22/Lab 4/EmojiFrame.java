/**
 * Initializes the frame of the program.
 * Contains both the canvas of the drawing and the controls to modify the said canvas.
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

public class EmojiFrame extends JFrame
{
    private int width, height;
    private String title;
    
    public EmojiFrame(int w, int h, String t)
    {
        width = w;
        height = h;
        title = t;
    }
    
    public void setUpFrame()
    {
        setTitle(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container contentPane = getContentPane();
        EmojiCanvas emojiCanvas = new EmojiCanvas(width, height, Color.WHITE);
        EmojiControls emojiControls = new EmojiControls(emojiCanvas);
        emojiControls.setUpPanel();
        contentPane.add(emojiCanvas, BorderLayout.CENTER);
        contentPane.add(emojiControls, BorderLayout.SOUTH);
        pack();
        setVisible(true);
    }
}