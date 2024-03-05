import java.awt.*;
import java.awt.geom.*;

/**
 * Write a description of class Animal here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Animal
{
    // instance variables - replace the example below with your own
    private double x, y, size;
    private Color color;

    /**
     * Constructor for objects of class Animal
     */
    public Animal(double x, double y, double s, Color c)
    {
        this.x = x;
        this.y = y;
        this.size = s;
        this.color = c;
    }

    /**
     * An example of a method - replace this comment with your own
     *
     * @param  y  a sample parameter for a method
     * @return    the sum of x and y
     */
    public int sampleMethod(int y)
    {
        // put your code here
        return x + y;
    }
}
