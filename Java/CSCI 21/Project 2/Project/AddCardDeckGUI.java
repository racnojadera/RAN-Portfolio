
/**
 * Class that contains the frame for adding a card to a certain deck.
 *
 * @author Raymond Andrew C. Nojadera
 * @version December 8, 2018
 */

import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class AddCardDeckGUI extends JFrame
{
    private Database data;
    private JLabel frontLabel, backLabel, deckName;
    private JTextField frontInput, backInput;
    private JButton addCard, backMain;
    private JPanel centerArea, bottomArea;
    private GridBagConstraints mainCenter;
    /**
     * Initializes and contains all the components found in the container.
     *
     * @param  data loads data from the Database.
     */
    public AddCardDeckGUI(Database data)
    {
        this.data = data;
        deckName = new JLabel(data.getTitle());
        deckName.setHorizontalAlignment(JLabel.CENTER);
        deckName.setPreferredSize(new Dimension(300, 50));
        addCard = new JButton("Add Card");
        addCard.setSize(50, 30);
        backMain = new JButton("Back");
        backMain.setSize(50, 30);
        centerArea = new JPanel();
        centerArea.setPreferredSize(new Dimension(300, 100));
        centerArea.setLayout(new GridBagLayout());
        mainCenter = new GridBagConstraints();
        bottomArea = new JPanel();
        bottomArea.setPreferredSize(new Dimension(300, 50));
        bottomArea.setLayout(new FlowLayout());
        
        Container addCardGUI = this.getContentPane();
        addCardGUI.setLayout(new BorderLayout());
        
        frontLabel = new JLabel("Front: ");
        mainCenter.gridx = 0;
        mainCenter.gridy = 0;
        mainCenter.weightx = 0.1;
        centerArea.add(frontLabel, mainCenter);
        
        frontInput = new JTextField(20);
        mainCenter.gridx = 1;
        mainCenter.gridy = 0;
        mainCenter.weightx = 0.2;
        centerArea.add(frontInput, mainCenter);
        
        backLabel = new JLabel("Back: ");
        mainCenter.gridx = 0;
        mainCenter.gridy = 1;
        mainCenter.weightx = 0.1;
        centerArea.add(backLabel, mainCenter);
        
        backInput = new JTextField(20);
        mainCenter.gridx = 1;
        mainCenter.gridy = 1;
        mainCenter.weightx = 0.2;
        centerArea.add(backInput, mainCenter);
        
        
        bottomArea.add(addCard);
        class addingCard implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                data.getDeck().addCard(frontInput.getText(), backInput.getText());
                revalidate();
                dispose();
            }
        }
        addCard.addActionListener(new addingCard());
        
        bottomArea.add(backMain);
        class backToMain implements ActionListener
        {
            public void actionPerformed(ActionEvent ae)
            {
                revalidate();
                dispose();
            }
        }
        backMain.addActionListener(new backToMain());
        
        addCardGUI.add(deckName, "North");
        addCardGUI.add(centerArea, "Center");
        addCardGUI.add(bottomArea, "South");
        
    }
}
