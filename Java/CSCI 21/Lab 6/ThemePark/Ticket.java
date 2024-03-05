
/**
 * Identifies whether the ticket is single or double access as well as its balance.
 * 
 * @author Raymond Andrew C. Nojadera
 * @version November 13, 2018
 **/
 
/*
 * I have not discussed the java language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
 * I have not used java language code obtained from another student, or any other unauthorized source, either modified or unmodified.
 * If any java language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.
 */
public class Ticket
{
    private double balance;
    private int usecount;
    public Ticket(double c)
    {
        balance = c;
        usecount = 0;
    }
    
    public double getCredit()
    {
        return balance;
    }
    
    public boolean isAllAccess()
    {
        if(balance == 150.00)
        {
            usecount++;
            return true;
        }
        else if(usecount != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public void updateCredit( double amt )
    {
        balance -= amt;
    }
}
