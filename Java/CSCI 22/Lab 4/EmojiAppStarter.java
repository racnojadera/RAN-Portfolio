/**
 * Main launcher of the program.
 * Sets up the emoji frame.
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

public class EmojiAppStarter
{
    public static void main(String[] args)
    {
        EmojiFrame ef = new EmojiFrame(640, 480, "Emoji - Nojadera, Raymond Andrew - 183529");
        ef.setUpFrame();
    }
}