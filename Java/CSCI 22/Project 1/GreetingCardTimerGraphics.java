/**
 * Backbone of all animation-related work. Manipulates the values of the objects through timer and logic
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

import javax.swing.*;
import java.awt.event.*;

public class GreetingCardTimerGraphics implements ActionListener
{
    private int red, green, blue, timeCounter = 0; //16Hz, 5,760 frames, 15s/frame
    private Timer timer;
    private boolean isPlaying, isNight;
    private ActionListener timerCount;
    private GreetingCardCanvas gcCanvas;
    private DrawingObject sunAdjuster, refAdjuster, skyGradientDay, skyGradientNight, skyGradientRiseSet, umbrellaShadow, umbrella, timeShader;
    
    /**
     * Constructor for objects of class GreetingCardTimerGraphics
     * 
     * @param gcc passes on the values of gcc, allowing access into the class
     */
    public GreetingCardTimerGraphics(GreetingCardCanvas gcc) //http://www.java2s.com/Tutorial/Java/0240__Swing/Timerbasedanimation.htm
    {
        red = 0;
        green = 0;
        blue = 0;
        timeCounter = 0;
        isPlaying = true;
        isNight = false;
        gcCanvas = gcc;
        sunAdjuster = gcCanvas.adjustSunLoc();
        refAdjuster = gcCanvas.adjustSunRef();
        skyGradientDay = gcCanvas.getDay("day");
        skyGradientNight = gcCanvas.getDay("night");
        skyGradientRiseSet = gcCanvas.getDay("riseset");
        umbrellaShadow = gcCanvas.getUmbrellaS();
        umbrella = gcCanvas.getUmbrella();
        timeShader = gcCanvas.getShader();
    }
    
    /**
     * Initializes the timer class.
     */
    public void setUpTimer()
    {
        timer = new Timer(16, this);
        timer.setRepeats(true);
        timer.setInitialDelay(200);
        timer.start();
    }
    
    /**
     * Sets up the event when the timer ticks.
     */
    public void actionPerformed(ActionEvent e)
    {
        if(isPlaying)
        {
            if(timeCounter == 2880)
            {
                sunAdjuster.resetX();
                refAdjuster.resetX();
            }
            else
            {
                sunAdjuster.adjustX(-0.4);
                refAdjuster.adjustX(-0.4);
            }
            if(timeCounter < 1440)
            {
                sunAdjuster.adjustY();
                refAdjuster.adjustY();
            }
            else
            {
                sunAdjuster.adjustY();
                refAdjuster.adjustY();
            }
            cycleCounter();
            refresh();
        }
    }
    
    /**
     * Cycles through the number of frames/instances to similarize into a real day cycle (day/night).
     */
    public void cycleCounter()
    {
        if(timeCounter <=2880)
        {
            timeCounter += 1;
            umbrella.adjustRotation(0.0625);
            umbrellaShadow.adjustRotation(-0.0625);
        }
        else if(timeCounter >= 2881)
        {
            timeCounter = 1;
            checkNight();
        }
        changeSkyGradient();
    }
    
    /**
     * Enables/Disables the timer.
     */
    public void setPlay()
    {
        if(isPlaying)
        {
            isPlaying = false;
        }
        else
        {
            isPlaying = true;
        }
    }
    
    /**
     * Checks whether the timer is playing/paused.
     * 
     * @return status of the timer
     */
    public boolean checkPlaying()
    {
        return isPlaying;
    }
    
    /**
     * Refreshes/Repaints the canvas.
     */
    public void refresh()
    {
        gcCanvas.repaint();
    }
    
    /**
     * Gets the current value of the counter
     * 
     * @return value of timeCounter
     */
    public int getTime()
    {
        return timeCounter;
    }
    
    /**
     * Checks whenever the program is on night mode or not.
     */
    public void checkNight()
    {
        
        if(isNight)
            {
                isNight = false;
                sunAdjuster.resetColor(255, 127, 0, 255);
                refAdjuster.resetColor(255, 127, 0, 255);
                skyGradientNight.resetColor(26, 27, 32, 0);
                skyGradientDay.resetColor(82, 150, 212, 255);
            }
        else
            {
                isNight = true;
                sunAdjuster.resetColor(255, 255, 255, 255);
                refAdjuster.resetColor(255, 255, 255, 255);
                skyGradientNight.resetColor(26, 27, 32, 255);
                skyGradientDay.resetColor(82, 150, 212, 0);
            }
    }
    
    /**
     * Changes the colors of the sky based on the current time of the program (cycle)
     */
    public void changeSkyGradient()
    {
        if(timeCounter < 700)
        {
            skyGradientRiseSet.resetColor(76, 61, 90, 255-255*timeCounter/700);
            if(!isNight)
            {
                sunAdjuster.resetColor(255,150+(105*timeCounter/700),90,255);
                refAdjuster.resetColor(255,150+(105*timeCounter/700),90,255);
                timeShader.resetColor(205, 69, 42, 127-127*timeCounter/700);
                umbrellaShadow.resetColor(0,0,0,127*timeCounter/700);
            }
            else
            {
                timeShader.resetColor(205-179*timeCounter/700, 69-42*timeCounter/700, 42-10*timeCounter/700, 127);
            }
        }
        else if(timeCounter > 2180)
        {
            skyGradientRiseSet.resetColor(76, 61, 90, 255*(timeCounter-2180)/700);
            if(!isNight)
            {
                sunAdjuster.resetColor(255,255-125*(timeCounter-2180)/700,90,255);
                refAdjuster.resetColor(255,255-125*(timeCounter-2180)/700,90,255);
                timeShader.resetColor(205,69,42,127*(timeCounter-2180)/700);
                umbrellaShadow.resetColor(0,0,0,127-127*(timeCounter-2180)/700);
            }
            else
            {
                timeShader.resetColor(26+179*(timeCounter-2180)/700, 27+42*(timeCounter-2180)/700, 32+10*(timeCounter-2180)/700, 127);
            }
        }
    }
}
