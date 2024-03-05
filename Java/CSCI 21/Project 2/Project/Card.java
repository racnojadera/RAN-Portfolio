
/**
 * A representation of a single card.
 *
 * @author Raymond Andrew C. Nojadera
 * @version December 8, 2018
 */
public class Card
{
    private String frontContent, backContent;
    
    /**
     * Constructs a card
     *
     * @param f sets the content of the front.
     * @param b sets the content of the back.
     */
    public Card(String f, String b)
    {
        frontContent = f;
        backContent = b;
    }
    
    /**
     * Gets the front face of the card.
     * 
     * @return the front content.
     */
    public String getBack()
    {
        return backContent;
    }
    
    /**
     * Gets the back face of the card.
     *
     * @return the back content.
     */
    public String getFront()
    {
        return frontContent;
    }
}
