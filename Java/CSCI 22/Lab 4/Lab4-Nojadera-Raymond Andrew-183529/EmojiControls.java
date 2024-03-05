/**
 * Modifies the drawing in the canvas through different buttons.
 * Located in the south region of the frame.
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
import java.awt.event.*;

public class EmojiControls extends JPanel
{
    private JButton buttonUp, buttonDown, buttonLeft, buttonRight, buttonGrow, buttonShrink, buttonCCW, buttonCW, buttonLight, buttonDark;
    private EmojiCanvas emojiCanvas;
    
    public EmojiControls(EmojiCanvas ec)
    {
        buttonUp = new JButton("UP");
        buttonDown = new JButton("DOWN");
        buttonLeft = new JButton("LEFT");
        buttonRight = new JButton("RIGHT");
        buttonGrow = new JButton("GROW");
        buttonShrink = new JButton("SHRINK");
        buttonCCW = new JButton("CCW");
        buttonCW = new JButton("CW");
        buttonLight = new JButton("LIGHT");
        buttonDark = new JButton("DARK");
        emojiCanvas = ec;
    }
    
    public void setUpPanel()
    {
        setLayout(new GridLayout(3, 4));
        add(buttonUp);
        add(buttonDown);
        add(buttonLeft);
        add(buttonRight);
        add(buttonGrow);
        add(buttonShrink);
        add(buttonCCW);
        add(buttonCW);
        add(buttonLight);
        add(new JLabel(""));
        add(new JLabel(""));
        add(buttonDark);
        
        ButtonListener buttonListener = new ButtonListener();
        buttonUp.addActionListener(buttonListener);
        buttonDown.addActionListener(buttonListener);
        buttonLeft.addActionListener(buttonListener);
        buttonRight.addActionListener(buttonListener);
        buttonGrow.addActionListener(buttonListener);
        buttonShrink.addActionListener(buttonListener);
        buttonCCW.addActionListener(buttonListener);
        buttonCW.addActionListener(buttonListener);
        buttonLight.addActionListener(buttonListener);
        buttonDark.addActionListener(buttonListener);
    }
       
    private class ButtonListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent ae)
        {
            Object o = ae.getSource();
            if(o == buttonUp)
            {
                emojiCanvas.getEmoji().adjustY(-5);
            }
            else if(o == buttonDown)
            {
                emojiCanvas.getEmoji().adjustY(5);
            }
            else if(o == buttonLeft)
            {
                emojiCanvas.getEmoji().adjustX(-5);
            }
            else if(o == buttonRight)
            {
                emojiCanvas.getEmoji().adjustX(5);
            }
            else if(o == buttonGrow)
            {
                emojiCanvas.getEmoji().adjustSize(20);
            }
            else if(o == buttonShrink)
            {
                emojiCanvas.getEmoji().adjustSize(-20);
            }
            else if(o == buttonCCW)
            {
                emojiCanvas.getEmoji().rotate(-30);
            }
            else if(o == buttonCW)
            {
                emojiCanvas.getEmoji().rotate(30);
            }
            else if(o == buttonLight)
            {
                emojiCanvas.setBackgroundColor(Color.WHITE);
                emojiCanvas.getEmoji().setLight();
            }
            else if(o == buttonDark)
            {
                emojiCanvas.setBackgroundColor(Color.BLACK);
                emojiCanvas.getEmoji().setDark();
            }
            emojiCanvas.repaint();
        }
    }
}