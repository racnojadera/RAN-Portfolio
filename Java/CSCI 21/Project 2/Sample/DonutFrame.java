
/**
 *
 * @author Raymond Andrew C. Nojadera
 * @version November 29, 2018
 */

/*
 * I have not discussed the Java language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
 * I have not used Java language code obtained from another student, or any other unauthorized source, either modified or unmodified.
 * If any Java language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class DonutFrame extends JFrame
{
	private JTextField txtInput1, txtInput2;
	private JButton btnRefill, btnSell, btnChange, btnReport;
	private JTextArea display;
    private DonutShop ds;
	public DonutFrame()
	{
		txtInput1 = new JTextField( 10 );
		txtInput2 = new JTextField( 10 );
		btnRefill = new JButton( "Refill" );
		btnSell = new JButton( "Sell" );
		btnChange = new JButton( "Change" );
		btnReport = new JButton( "Report" );
		display = new JTextArea( 20, 25 );
		ds = new DonutShop();

		Container c = this.getContentPane();
		c.setLayout( new FlowLayout() );

		c.add( txtInput1 );
		c.add( txtInput2 );

		c.add( btnSell );
		class SellL implements ActionListener
		{
			public void actionPerformed( ActionEvent ae )
			{
				int o = Integer.parseInt( txtInput1.getText() );
				int l = Integer.parseInt( txtInput2.getText() );
				double bill = ds.selldonuts(o,l);
				String msg = "Please pay Php " + bill + ".\n";
				display.append( msg );
			}
		}
		btnSell.addActionListener( new SellL() );


		c.add( btnRefill );
		class RefillL implements ActionListener
		{
			public void actionPerformed( ActionEvent ae )
			{
				int r = Integer.parseInt( txtInput1.getText() );
				ds.refillDonuts( r );
				display.append( "Refilled stock with " + r + " donuts" + ".\n" );
			}
		}
		btnRefill.addActionListener( new RefillL() );


		c.add( btnChange );
		class ChangeL implements ActionListener
		{
			public void actionPerformed( ActionEvent ae )
			{
				double n = Double.parseDouble( txtInput2.getText() );
				ds.changePrice( n );
				String msg = "Donut price changed to Php "+ n + ".\n";
				display.append( msg );
			}
		}
		btnChange.addActionListener( new ChangeL() );


		c.add( btnReport );
		class ReportL implements ActionListener
		{
			public void actionPerformed( ActionEvent ae )
			{
				String report = "-----Sales Report-----\n";
				report += "Total Sales: Php " + ds.getSales() + "\n" ;
				report += "Total Donuts Sold: " + ds.getSoldDonuts() + "\n";
				report += "Total Free Donuts: "+ ds.getFreeDonuts() + "\n";
				report += "----------------------\n";

				display.append( report );
			}
		}
		btnReport.addActionListener( new ReportL() );

		c.add( display );

	}
    
	public static void main( String[] args )
	{
		JFrame f = new DonutFrame();
		f.setSize( 300, 450 );
		f.setTitle( "Donut Shop" );
		f.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		f.setVisible( true );
		
	}
}

/*
Test Data
Sell 1, 1
Sell 5, 16
Reprice 40
Sell 4, 22
Refill 10
Report
Sell 3, 15
Sell 6, 12
Sell 3, 20
Report
*/
