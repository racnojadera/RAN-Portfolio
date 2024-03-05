/**
 * Contains all graphics related content. Also contains methods to access the object's values by the timergraphics
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
import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

public class GreetingCardCanvas extends JComponent
{
    private int width, height, testCounter;
    private Color backgroundColor;
    private ArrayList<DrawingObject> listOfObjects;
    private Sun sun;
    private SunReflection reflection;
    private SkyBackgroundDay skyDay;
    private SkyBackgroundNight skyNight;
    private SkyBackgroundRiseSet skyRiseSet;
    private SeaBackground sea;
    private SandBackground beach;
    private SandCastle castle;
    private Umbrella umbrella;
    private UmbrellaShadow umbrellaShadow;
    private Play playIcon;
    private Pause leftPauseIcon, rightPauseIcon;
    private LandSeaShader moodShader;
    
    /**
     * Constructor for objects of class GreetingCardCanvas
     * @param w sets the width
     * @param h sets the height
     * @param c sets the color
     */
    public GreetingCardCanvas(int w, int h, Color c)
    {
        width = w;
        height = h;
        backgroundColor = c;
        setPreferredSize(new Dimension(width, height));
        listOfObjects = new ArrayList<>();
        
        skyDay = new SkyBackgroundDay(Double.valueOf(width),Double.valueOf(height), 1, 82, 150, 212); //https://www.javatpoint.com/java-int-to-double
        skyNight = new SkyBackgroundNight(Double.valueOf(width),Double.valueOf(height), 1, 26, 27, 32);
        skyRiseSet = new SkyBackgroundRiseSet(Double.valueOf(width),Double.valueOf(height), 1, 76, 61, 90);
        sea = new SeaBackground(Double.valueOf(width), Double.valueOf(height), 1, 50, 109, 187);
        beach = new SandBackground(0, height/2, 500, 218, 173, 118);
        castle = new SandCastle(700, 650, 300, 218, 173, 118);
        sun = new Sun(1100, 377.44, 100, 255, 255, 0);
        reflection = new SunReflection(1100, 377.44, 100, 255, 255, 0);
        umbrella = new Umbrella(200, 450, 75, 255, 255, 255);
        umbrellaShadow = new UmbrellaShadow(200, 450, 75, 0, 0, 0);
        moodShader = new LandSeaShader(Double.valueOf(width),Double.valueOf(height),1,204, 69, 42);
        playIcon = new Play(1090, -10, 50, 255, 255, 255);
        leftPauseIcon = new Pause(1074.5, 5, 1074.5, -25, 20, 255, 255, 255);
        rightPauseIcon = new Pause(1104.5, 5, 1104.5, -25, 20, 255, 255, 255);
        
        listOfObjects.add(skyDay);
        listOfObjects.add(skyNight);
        listOfObjects.add(skyRiseSet);
        listOfObjects.add(sun);
        listOfObjects.add(sea);
        listOfObjects.add(reflection);
        listOfObjects.add(beach);
        listOfObjects.add(castle);
        listOfObjects.add(umbrellaShadow);
        listOfObjects.add(umbrella);
        listOfObjects.add(moodShader);
        listOfObjects.add(playIcon);
        listOfObjects.add(leftPauseIcon);
        listOfObjects.add(rightPauseIcon);
    }
    
    /**
     * draws each object into the canvas
     */
    @Override
    protected void paintComponent(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;
        
        RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHints(rh);
        
        for(int i = 0; i<listOfObjects.size(); i++)
        {
            listOfObjects.get(i).draw(g2d);
        }
    }
    
    /**
     * Gets the object sun from the arraylist of drawingobjects
     * @return the object sun
     */
    public DrawingObject adjustSunLoc()
    {
        return listOfObjects.get(3);
    }
    
    /**
     * Gets the object sunreflection from the arraylist of drawingobjects
     * @return the object sunreflection
     */
    public DrawingObject adjustSunRef()
    {
        return listOfObjects.get(5);
    }
    
    /**
     * Returns a specific skygradient based on its parameter
     * @param t keyword to differentiate the gradients
     * @return the skygradient
     */
    public DrawingObject getDay(String t)
    {
        if(t.equals("day"))
        {
            return listOfObjects.get(0);
        }
        else if(t.equals("riseset"))
        {
            return listOfObjects.get(2);
        }
        else
        {
            return listOfObjects.get(1);
        }
    }
    
    /**
     * Gets the object shader from the arraylist of drawingobjects
     * @return the object shader
     */
    public DrawingObject getShader()
    {
        return listOfObjects.get(listOfObjects.size()-4);
    }
    
    /**
     * Returns the play/pause icon based on its parameters
     * @param t keyword to differentiate the play/pause
     * @return play/pause icons/objects
     */
    public DrawingObject getPlayStatus(String t)
    {
        if(t.equals("left"))
        {
            return listOfObjects.get(listOfObjects.size()-2);
        }
        else if(t.equals("right"))
        {
            return listOfObjects.get(listOfObjects.size()-1);
        }
        else
        {
            return listOfObjects.get(listOfObjects.size()-3);  
        }
    }
    
    /**
     * Gets the object umbrella from the arraylist of drawingobjects
     * @return the object umbrella
     */
    public DrawingObject getUmbrella()
    {
        return listOfObjects.get(9);
    }
    
    /**
     * Gets the object umbrellashadow from the arraylist of drawingobjects
     * @return the object umbrellashadow
     */
    public DrawingObject getUmbrellaS()
    {
        return listOfObjects.get(8);
    }
    
}
