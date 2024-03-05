
/**
 * Contains the attraction's characteristics (name and cost).
 * 
 * @author Raymond Andrew C. Nojadera
 * @version November 13, 2018
 **/

/*
 * I have not discussed the java language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
 * I have not used java language code obtained from another student, or any other unauthorized source, either modified or unmodified.
 * If any java language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.
 */
public class Attraction
{
   private String attraction;
   private double cost;
   
   public Attraction(String n, double c)
   {
       attraction = n;
       cost = c;
   }
   
   public String getName()
   {
       return attraction;
   }
   
   public double getCost()
   {
       return cost;
   }
}
