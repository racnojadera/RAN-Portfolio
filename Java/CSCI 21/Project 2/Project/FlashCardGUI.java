
/**
 * Runs the interface of the main menu.
 *
 * @Raymond Andrew C. Nojadera
 * @version December 8, 2018
 */

import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class FlashCardGUI extends JFrame
{
    private Database data;
    private ArrayList<JButton> addCardDeck, viewCardDeck, studyDeck;
    private JPanel topArea, centerArea, centerStage, bottomArea;
    private GridBagConstraints dataTable, bottomPanel;
    private JLabel deckTitleMain, deckNameLabel;
    private JTextField nameNewDeck;
    private JButton addNewDeck, options, refresh;
    private JTextArea testingField;
    private int verticalIterator;
    /**
     * The main menu/first screen or frame of the program.
     *
     * @param data loads the Database data into the interface.
     */
    public FlashCardGUI(Database data)
    {
        this.data = data;
        verticalIterator = 0;
        deckTitleMain = new JLabel("Decks");
        deckTitleMain.setHorizontalAlignment(JLabel.CENTER); //https://stackoverflow.com/questions/12589494/align-text-in-jlabel-to-the-right
        deckNameLabel = new JLabel("Deck Name: ");
        nameNewDeck = new JTextField(20);
        addNewDeck = new JButton("Add Deck");
        addNewDeck.setPreferredSize(new Dimension(90, 25)); ////https://stackoverflow.com/questions/2536873/how-can-i-set-size-of-a-button
        refresh = new JButton("Refresh");
        refresh.setPreferredSize(new Dimension(90, 25));
        options = new JButton("Options");
        options.setPreferredSize(new Dimension(90, 25));
        addCardDeck = new ArrayList<JButton>();
        viewCardDeck = new ArrayList<JButton>();
        studyDeck = new ArrayList<JButton>();
        topArea = new JPanel();
        topArea.setPreferredSize(new Dimension(100, 30));
        bottomArea = new JPanel();
        bottomArea.setLayout(new GridBagLayout()); //https://docs.oracle.com/javase/tutorial/uiswing/layout/gridbag.html
        bottomPanel = new GridBagConstraints();
        centerArea = new JPanel();
        centerArea.setLayout(new GridBagLayout());
        dataTable = new GridBagConstraints();
        centerStage = new JPanel();
        centerStage.setLayout(new BorderLayout()); //https://stackoverflow.com/questions/6364280/starting-gridbaglayout-from-top-left-corner-in-java-swing
        
        Container main = this.getContentPane();
        main.setLayout(new BorderLayout());
        
        class addingCardToDeck implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                for(int i = 0; i < addCardDeck.size(); i++)
                {
                    if(ae.getSource() == addCardDeck.get(i)) //https://stackoverflow.com/questions/26433975/which-jbutton-is-being-clicked-when-it-is-an-array-of-jbuttons-with-the-same-ac
                    {
                        data.setIterator(i);
                        studyDeck.get(i).setEnabled(false); //https://stackoverflow.com/questions/21209532/how-to-enable-disable-buttons-in-java-eclipse
                        viewCardDeck.get(i).setEnabled(false);
                        JFrame addNewCard = new AddCardDeckGUI(data);
                        addNewCard.setSize(300,200);
                        addNewCard.setTitle("Add New Card");
                        addNewCard.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); //https://stackoverflow.com/questions/33764752/jframe-all-the-frames-close-when-i-try-to-close-just-one-of-them
                        addNewCard.setVisible(true);
                        break;
                    }
                }
                addNewDeck.setEnabled(false);
            }
        }
        
        class viewingCardsOfDeck implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                for(int i = 0; i < viewCardDeck.size(); i++)
                {
                    viewCardDeck.get(i).setEnabled(false);
                    if(ae.getSource() == viewCardDeck.get(i))
                    {
                        data.setIterator(i);
                        addCardDeck.get(i).setEnabled(false);
                        studyDeck.get(i).setEnabled(false);
                        JFrame viewCards = new ViewCardsDeckGUI(data);
                        viewCards.setSize(480,420);
                        viewCards.setTitle("View Cards");
                        viewCards.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                        viewCards.setVisible(true);
                    }
                }
                addNewDeck.setEnabled(false);
            }
        }
        
        class studyingDeck implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                for(int i = 0; i < studyDeck.size(); i++)
                {
                    if(ae.getSource() == studyDeck.get(i))
                    {
                        data.setIterator(i);
                        JFrame studyTheDeck = new StudyDeckGUI(data);
                        studyTheDeck.setSize(300,200);
                        studyTheDeck.setTitle("Study Session");
                        studyTheDeck.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                        studyTheDeck.setVisible(true);
                        break;
                    }
                }
            }
            
        }
        
        topArea.add(deckTitleMain);
        
        bottomPanel.gridx = 0;
        bottomPanel.gridy = 0;
        bottomPanel.weightx = 0.2;
        bottomArea.add(deckNameLabel, bottomPanel);
        
        bottomPanel.gridx = 1;
        bottomPanel.gridy = 0;
        bottomPanel.weightx = 0.1;
        bottomArea.add(nameNewDeck, bottomPanel);
        
        bottomPanel.gridx = 2;
        bottomPanel.gridy = 0;
        bottomPanel.weightx = 0.2;
        bottomArea.add(addNewDeck, bottomPanel);
        class addingNewDeck implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                data.setIterator(verticalIterator);
                data.addDeck(nameNewDeck.getText());
                centerArea.removeAll(); //https://stackoverflow.com/questions/38349445/how-to-delete-all-components-in-a-jpanel-dynamically
		int verticalCounter = data.numberOfDecks() - data.wasImported();
		addCardDeck.clear(); //https://stackoverflow.com/questions/7032070/what-is-the-difference-between-arraylist-clear-and-arraylist-removeall
		viewCardDeck.clear();
		studyDeck.clear();
		for(int i = 0; i < verticalCounter; i++)
                {
                    data.setIterator(i);
                            
                    Deck current = data.getDeck();
                            
                    JLabel modifyCardCount = new JLabel();
                    if(current.getSize() == 1)
                    {
                        modifyCardCount.setText(Integer.toString(data.getDeck().getSize()) + " card");
                    }
                    else if(current.getSize() == 0)
                    {
                        modifyCardCount.setText("no cards");
                    }
                    else
                    {
                        modifyCardCount.setText(Integer.toString(data.getDeck().getSize()) + " cards");
                    }
                            
                    dataTable.gridx = 0;
                    dataTable.gridy = i;
                    dataTable.weightx = 1;
                    centerArea.add(new JLabel(current.getTitle()), dataTable);
                            
                    dataTable.gridx = 1;
                    centerArea.add(modifyCardCount, dataTable);
                            
                    JButton addCard = new JButton("Add Card");
                    dataTable.gridx = 2;
                    dataTable.weightx = 0.05;
                    centerArea.add(addCard, dataTable);
                    addCardDeck.add(addCard);
                    addCard.addActionListener(new addingCardToDeck());
                    
                    JButton viewCards = new JButton("View Cards");
                    dataTable.gridx = 3;
                    centerArea.add(viewCards, dataTable);
                    viewCardDeck.add(viewCards);
                    viewCards.addActionListener(new viewingCardsOfDeck());
                    
                    JButton study = new JButton("Study");;
                    dataTable.gridx = 4;
                    centerArea.add(study, dataTable);
                    studyDeck.add(study);
                    study.addActionListener(new studyingDeck());
                    
                    if(data.getDeck().getSize() != 0)
                    {
                        viewCards.setEnabled(true);
                        study.setEnabled(true);
                    }
                    else
                    {
                        study.setEnabled(false);
                    }
                        
                    verticalIterator += 1;
                }
                if(data.wasImported() != 0)
                {
                    for(int i = verticalCounter; i < data.numberOfDecks(); i++)
                    {
                        data.setIterator(i);
                        JLabel deckTitle = new JLabel(data.getTitle());
                        dataTable.gridx = 0;
                        dataTable.gridy = verticalIterator;
                        dataTable.weightx = 1;
        
                        centerArea.add(deckTitle, dataTable);
                        
                        JLabel deckCount = new JLabel();
                        if(data.getSize() == 1)
                        {
                            deckCount.setText(Integer.toString(data.getDeck().getSize()) + " card");
                        }
                        else if(data.getSize() == 0)
                        {
                            deckCount.setText("no cards");
                        }
                        else
                        {
                            deckCount.setText(Integer.toString(data.getDeck().getSize()) + " cards");
                        }
                        dataTable.gridx = 1;
                        dataTable.gridy = verticalIterator;
                        centerArea.add(deckCount, dataTable);
                        
                        JButton addCard = new JButton("Add Card");
                        dataTable.gridx = 2;
                        dataTable.gridy = verticalIterator;
                        dataTable.weightx = 0.05;
                        centerArea.add(addCard, dataTable);
                        addCardDeck.add(addCard);
                        addCard.addActionListener(new addingCardToDeck());
                        
                        JButton viewCards = new JButton("View Cards");
                        dataTable.gridx = 3;
                        dataTable.gridy = verticalIterator;
                        centerArea.add(viewCards, dataTable);
                        viewCardDeck.add(viewCards);
                        viewCards.addActionListener(new viewingCardsOfDeck());
                        
                        JButton study = new JButton("Study");
                        dataTable.gridx = 4;
                        dataTable.gridy = verticalIterator;
                        centerArea.add(study, dataTable);
                        studyDeck.add(study);
                        study.addActionListener(new studyingDeck());
                        
                        if(data.getSize() == 0)
                        {
                            study.setEnabled(false);
                        }
                        verticalIterator += 1;
                    }
                    data.removeDeckImports();
                }
                nameNewDeck.setText("");
                
                revalidate(); //https://stackoverflow.com/questions/12865803/how-do-i-refresh-a-gui-in-java
                repaint();
            }
        }
        addNewDeck.addActionListener(new addingNewDeck());
        
        bottomPanel.gridx = 0;
        bottomPanel.gridy = 1;
        bottomPanel.weightx = 0.2;
        bottomArea.add(options, bottomPanel);
        class optionsGUI implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                JFrame optionsPanel = new OptionsPanelGUI(data);
                optionsPanel.setSize(300,200);
                optionsPanel.setTitle("Options");
                optionsPanel.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                optionsPanel.setVisible(true);
            }
        }
        options.addActionListener(new optionsGUI());
        
        bottomPanel.gridx = 2;
        bottomPanel.gridy = 1;
        bottomPanel.weightx = 0.2;
        bottomArea.add(refresh, bottomPanel);
        class refreshingUI implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                centerArea.removeAll();
		int verticalCounter = data.numberOfDecks() - data.wasImported();
		addCardDeck.clear(); //https://stackoverflow.com/questions/7032070/what-is-the-difference-between-arraylist-clear-and-arraylist-removeall
		viewCardDeck.clear();
		studyDeck.clear();
		for(int i = 0; i < verticalCounter; i++)
                {
                    data.setIterator(i);
                            
                    Deck current = data.getDeck();
                            
                    JLabel modifyCardCount = new JLabel();
                    if(current.getSize() == 1)
                    {
                        modifyCardCount.setText(Integer.toString(data.getDeck().getSize()) + " card");
                    }
                    else if(current.getSize() == 0)
                    {
                        modifyCardCount.setText("no cards");
                    }
                    else
                    {
                        modifyCardCount.setText(Integer.toString(data.getDeck().getSize()) + " cards");
                    }
                            
                    dataTable.gridx = 0;
                    dataTable.gridy = i;
                    dataTable.weightx = 1;
                    centerArea.add(new JLabel(current.getTitle()), dataTable);
                            
                    dataTable.gridx = 1;
                    centerArea.add(modifyCardCount, dataTable);
                            
                    JButton addCard = new JButton("Add Card");
                    dataTable.gridx = 2;
                    dataTable.weightx = 0.05;
                    centerArea.add(addCard, dataTable);
                    addCardDeck.add(addCard);
                    addCard.addActionListener(new addingCardToDeck());
                    
                    JButton viewCards = new JButton("View Cards");
                    dataTable.gridx = 3;
                    centerArea.add(viewCards, dataTable);
                    viewCardDeck.add(viewCards);
                    viewCards.addActionListener(new viewingCardsOfDeck());
                    
                    JButton study = new JButton("Study");;
                    dataTable.gridx = 4;
                    centerArea.add(study, dataTable);
                    studyDeck.add(study);
                    study.addActionListener(new studyingDeck());
                    
                    if(data.getDeck().getSize() != 0)
                    {
                        viewCards.setEnabled(true);
                        study.setEnabled(true);
                    }
                    else
                    {
                        study.setEnabled(false);
                    }
                        
                    verticalIterator += 1;
                }
                if(data.wasImported() != 0)
                {
                    for(int i = verticalCounter; i < data.numberOfDecks(); i++)
                    {
                        data.setIterator(i);
                        JLabel deckTitle = new JLabel(data.getTitle());
                        dataTable.gridx = 0;
                        dataTable.gridy = verticalIterator;
                        dataTable.weightx = 1;
        
                        centerArea.add(deckTitle, dataTable);
                        
                        JLabel deckCount = new JLabel();
                        if(data.getSize() == 1)
                        {
                            deckCount.setText(Integer.toString(data.getDeck().getSize()) + " card");
                        }
                        else if(data.getSize() == 0)
                        {
                            deckCount.setText("no cards");
                        }
                        else
                        {
                            deckCount.setText(Integer.toString(data.getDeck().getSize()) + " cards");
                        }
                        dataTable.gridx = 1;
                        dataTable.gridy = verticalIterator;
                        centerArea.add(deckCount, dataTable);
                        
                        JButton addCard = new JButton("Add Card");
                        dataTable.gridx = 2;
                        dataTable.gridy = verticalIterator;
                        dataTable.weightx = 0.05;
                        centerArea.add(addCard, dataTable);
                        addCardDeck.add(addCard);
                        addCard.addActionListener(new addingCardToDeck());
                        
                        JButton viewCards = new JButton("View Cards");
                        dataTable.gridx = 3;
                        dataTable.gridy = verticalIterator;
                        centerArea.add(viewCards, dataTable);
                        viewCardDeck.add(viewCards);
                        viewCards.addActionListener(new viewingCardsOfDeck());
                        
                        JButton study = new JButton("Study");
                        dataTable.gridx = 4;
                        dataTable.gridy = verticalIterator;
                        centerArea.add(study, dataTable);
                        studyDeck.add(study);
                        study.addActionListener(new studyingDeck());
                        
                        if(data.getSize() == 0)
                        {
                            study.setEnabled(false);
                        }
                        verticalIterator += 1;
                    }
                    data.removeDeckImports();
                }
                addNewDeck.setEnabled(true);
                revalidate();
                repaint();
            }
        }
        refresh.addActionListener(new refreshingUI());
        
        centerStage.add(centerArea, "North");
        main.add(topArea, "North");
        main.add(centerStage, "Center");
        main.add(bottomArea, "South");
    }
}

//https://stackoverflow.com/questions/15262682/replace-component-in-gridbaglayout