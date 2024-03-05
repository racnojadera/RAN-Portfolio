
/**
 * Views and allows modification to the cards in the deck (including deleting the deck).
 *
 * @author Raymond Andrew C. Nojadera
 * @version December 8, 2018
 */
import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ViewCardsDeckGUI extends JFrame
{
    private Database data;
    private ArrayList<JButton> deleteCard;
    private ArrayList<Card> cardList;
    private JLabel deckName;
    private JPanel centerArea, bottomArea, centerStage;
    private JButton previousWindow, nextWindow, backMain, removeDeck;
    private GridBagConstraints mainCenter;
    private int counter, dataSize, sizeTens;
    /**
     * Creates the interface.
     *
     * @param data Imports the data from the database
     */
    public ViewCardsDeckGUI(Database data)
    {
        this.data = data;
        dataSize = data.getSize();
        sizeTens = dataSize/10;
        counter = 0;
        deckName = new JLabel(data.getTitle());
        deckName.setHorizontalAlignment(JLabel.CENTER);
        deckName.setPreferredSize(new Dimension(300, 50));
        centerArea = new JPanel();
        centerArea.setLayout(new GridBagLayout());
        mainCenter = new GridBagConstraints();
        bottomArea = new JPanel();
        bottomArea.setLayout(new FlowLayout());
        centerStage = new JPanel();
        centerStage.setLayout(new BorderLayout());
        previousWindow = new JButton("Previous");
        previousWindow.setEnabled(false);
        nextWindow = new JButton("Next");
        if(data.getSize() <= 10)
        {
            nextWindow.setEnabled(false);
        }
        else
        {
            nextWindow.setEnabled(true);
        }
        backMain = new JButton("Main Menu");
        removeDeck = new JButton("Delete Deck");
        deleteCard = new ArrayList<JButton>();
        cardList = new ArrayList<Card>();
        
        Container viewCardGUI = this.getContentPane();
        viewCardGUI.setLayout(new BorderLayout());
        
        class removeCardDeck implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                for(int i = 0; i < deleteCard.size(); i++)
                {
                    if(ae.getSource() == deleteCard.get(i))
                    {
                        cardList.remove(i);
                        deleteCard.remove(i);
                        data.getDeck().removeCard(i);
                    }
                }
                dataSize = data.getSize();
                sizeTens = dataSize/10;
                centerArea.removeAll();
                for(int i = 0; i < 10 && counter*10 + i < dataSize; i++)
                {
                    JButton newButton = deleteCard.get(i);
                    mainCenter.gridx = 0;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.1;
                    centerArea.add(newButton, mainCenter);
                    
                    Card currentCard = cardList.get(i);
                    JLabel currentFront = new JLabel(currentCard.getFront());
                    mainCenter.gridx = 1;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.5;
                    centerArea.add(currentFront, mainCenter);
                    
                    JLabel currentBack = new JLabel(currentCard.getBack());
                    mainCenter.gridx = 2;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.5;
                    centerArea.add(currentBack, mainCenter);
                }
                if(data.getSize() <= 10)
                {
                    nextWindow.setEnabled(false);
                }
                else
                {
                    nextWindow.setEnabled(true);
                }
                revalidate();
                repaint();
            }
        }
        
        for(int i = 0; i < dataSize; i++)
        {
            JButton newButton = new JButton("Delete Card");
            deleteCard.add(newButton);
            newButton.addActionListener(new removeCardDeck());
            
            cardList.add(data.getDeck().getCard(i));
        }
        
        
        for(int i = 0; i < 10 && counter*10 + i < dataSize; i++)
        {
            JButton newButton = deleteCard.get(i);
            mainCenter.gridx = 0;
            mainCenter.gridy = i;
            mainCenter.weightx = 0.1;
            centerArea.add(newButton, mainCenter);
            
            Card currentCard = cardList.get(i);
            JLabel currentFront = new JLabel(currentCard.getFront());
            mainCenter.gridx = 1;
            mainCenter.gridy = i;
            mainCenter.weightx = 0.5;
            centerArea.add(currentFront, mainCenter);
            
            JLabel currentBack = new JLabel(currentCard.getBack());
            mainCenter.gridx = 2;
            mainCenter.gridy = i;
            mainCenter.weightx = 0.5;
            centerArea.add(currentBack, mainCenter);
        }
        
        bottomArea.add(previousWindow);
        class backPreviousWindow implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                counter -= 1;
                nextWindow.setEnabled(true);
                centerArea.removeAll(); //https://stackoverflow.com/questions/38349445/how-to-delete-all-components-in-a-jpanel-dynamically
                for(int i = 0; i < 10 && counter*10 + i < data.getSize(); i++)
                {
                    int iterator = counter*10 + i;
                    JButton newButton = deleteCard.get(iterator);
                    mainCenter.gridx = 0;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.1;
                    centerArea.add(newButton, mainCenter);
                    //addactionListener
                    
                    Card currentCard = cardList.get(iterator);
                    JLabel currentFront = new JLabel(currentCard.getFront());
                    mainCenter.gridx = 1;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.5;
                    centerArea.add(currentFront, mainCenter);
                    
                    JLabel currentBack = new JLabel(currentCard.getBack());
                    mainCenter.gridx = 2;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.5;
                    centerArea.add(currentBack, mainCenter);
                }
                
                if(counter == 0)
                {
                    previousWindow.setEnabled(false);
                }
                else
                {
                    previousWindow.setEnabled(true);
                }
                revalidate();
                repaint();
            }
        }
        previousWindow.addActionListener(new backPreviousWindow());
        
        bottomArea.add(nextWindow);
        class toNextWindow implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                counter += 1;
                previousWindow.setEnabled(true);
                centerArea.removeAll();
                for(int i = 0; i < 10 && counter*10 + i < data.getSize(); i++)
                {
                    int iterator = counter*10 + i;
                    JButton newButton = deleteCard.get(iterator);
                    mainCenter.gridx = 0;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.1;
                    centerArea.add(newButton, mainCenter);
                    //addactionListener
                    
                    Card currentCard = cardList.get(iterator);
                    JLabel currentFront = new JLabel(currentCard.getFront());
                    mainCenter.gridx = 1;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.5;
                    centerArea.add(currentFront, mainCenter);
                    
                    JLabel currentBack = new JLabel(currentCard.getBack());
                    mainCenter.gridx = 2;
                    mainCenter.gridy = i;
                    mainCenter.weightx = 0.5;
                    centerArea.add(currentBack, mainCenter); 
                }
                if(counter >= sizeTens)
                {
                    nextWindow.setEnabled(false);
                }
                revalidate();
                repaint();
            }
        }
        nextWindow.addActionListener(new toNextWindow());
        
        bottomArea.add(removeDeck);
        class removingDeck implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                int i = data.getIterator();
                data.removeDeck(i);
                dispose();
            }
        }
        removeDeck.addActionListener(new removingDeck());
        
        bottomArea.add(backMain);
        class backToMain implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                dispose();
            }
        }
        backMain.addActionListener(new backToMain());
        
        centerStage.add(centerArea, "North");
        
        viewCardGUI.add(deckName, "North");
        viewCardGUI.add(centerStage, "Center");
        viewCardGUI.add(bottomArea, "South");
    }
}
