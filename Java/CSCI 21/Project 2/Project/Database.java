
/**
 * The backbone of the program, contains most of the necessary data loaded by the multiple GUIs and interfaces.
 *
 * @author Raymond Andrew C. Nojadera
 * @version December 8, 2018
 */
import java.util.*;

public class Database
{
    // instance variables - replace the example below with your own
    private ArrayList<Deck> deckList;
    private int iterator, hardStudy, importCount;
    
    /**
     * Constructor for objects of class Database
     */
    public Database()
    {
        deckList = new ArrayList<Deck>();
        iterator = 0;
        hardStudy = 0;
    }

    /**
     * Returns the value of the iterator of the arraylist deckList.
     *
     * @return the value of the iterator.
     */
    public int getIterator()
    {
        return iterator;
    }
    
    /**
     * Sets the iterator to a certain value.
     *
     * @param i the certain value that will replace the current value of iterator.
     */
    public void setIterator(int i)
    {
        iterator = i;
    }
    
    /**
     * Adds a deck to the deckList.
     *
     * @param name sets the name of the deck.
     */
    public void addDeck(String name)
    {
        deckList.add(new Deck(name));
    }
    
    /**
     * Removes a deck.
     *
     * @param i points out which deck is removed.
     */
    public void removeDeck(int i)
    {
        deckList.remove(i);
    }
    
    /**
     * Returns the title of a deck in the deckList.
     *
     * @param iterator indicates the location of the deck.
     * @return the name of the deck.
     */
    public String getTitle()
    {
        return deckList.get(iterator).getTitle();
    }
    
    /**
     * Returns the size/number of cards of a certain deck in the deckList.
     *
     * @param iterator indicates the location of the deck.
     * @return the size/numer of cards.
     */
    public int getSize()
    {
        return deckList.get(iterator).getSize();
    }
    
    /**
     * Accesses a certain deck from the deckList.
     * 
     * @param iterator indicates the location of the deck.
     * @return the deck
     */
    public Deck getDeck()
    {
        return deckList.get(iterator);
    }
    
    /**
     * Clones a deck and its contents given a location.
     * 
     * @param iterator gives its location
     * @param i iterates the original deck's card content and copies it to the replica
     * @return A replica of the original deck.
     */
    public Deck cloneDeck()
    {
        Deck originalDeck = deckList.get(iterator);
        Deck replicaDeck = new Deck(originalDeck.getTitle());
        for(int i = 0; i < originalDeck.getSize(); i++)
        {
            Card originalCard = originalDeck.getCard(i);
            replicaDeck.addCard(originalDeck.getCard(i).getFront(), originalDeck.getCard(i).getBack());
        }
        return replicaDeck;
    }
    
    /**
     * Determines how many decks are declared.
     *
     * @return The total number of decks.
     */
    public int numberOfDecks()
    {
        return deckList.size();
    }
    
    /**
     * Shuffles the cards in a certain deck.
     *
     * @param iterator indicates the location of the deck.
     */
    public void shuffleDeck()
    {
        deckList.get(iterator).Shuffle();
    }
    
    /**
     * Changes the difficulty of the study function.
     *
     * @param i indicates whether the difficulty is easy(1), normal(2), hard(3)
     */
    public void changeDifficulty(int i)
    {
        hardStudy = i;
    }
    
    /**
     * Determines the difficulty.
     *
     * @return the difficulty( 1 = easy; 2 = normal; 3 = hard)
     */
    public int whatDifficulty()
    {
        return hardStudy;
    }
    
    /**
     * Adds a count whenever a new deck is imported/loaded from a .txt file
     */
    public void addDeckImports()
    {
        importCount += 1;
    }
    
    /**
     * resets the importCount to 0 (used to declare new buttons and labels from imported/loaded .txt file)
     */
    public void removeDeckImports()
    {
        importCount = 0;
    }
    
    /**
     * Determines whether a deck was imported/loaded from a .txt file
     *
     * @return no imports(0) or it was imported(any positive number)
     */
    public int wasImported()
    {
        return importCount;
    }
}

//https://stackoverflow.com/questions/36338870/how-to-i-make-a-variable-accessible-from-multiple-jframes