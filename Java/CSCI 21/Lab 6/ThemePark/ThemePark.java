import java.util.*;

/**
 * Contains the arrays, basically the database of the whole code; Also contains the operations per se and prints the output.
 * 
 * @author Raymond Andrew C. Nojadera
 * @version November 13, 2018
 **/
 
/*
 * I have not discussed the java language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
 * I have not used java language code obtained from another student, or any other unauthorized source, either modified or unmodified.
 * If any java language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.
 */
public class ThemePark
{
    public static void main( String[] args )
    {
        
        /*
            Create an array of TicketScanners named ts, length 5
            Create an array of Attractions named atn, length 3
			Create an array of Tickets named tks, length 25
        */ 
           
        TicketScanner[] ts;
        Attraction[] atn;
        Ticket[] tks;
        ts = new TicketScanner[5];
        atn = new Attraction[3];
        tks = new Ticket[25];
        
        
        /*
            Use a loop to create an instance of TicketScanner in each slot in the array of TicketScanners.
        */
        for( int i = 0; i < ts.length; i++ )
        {
            ts[i] = new TicketScanner();
        }
        
        /*
            In the array of Attractions:
            First Slot: Create an instance of Attraction for the Roller Coaster, cost 85.85
            Second Slot: Create an instance of Attraction for the Ferris Wheel, cost 54.54
            Third Slot: Create an instance of Attraction for the Haunted Castle, cost 67.67
        */
    
        for( int i = 0; i < atn.length; i++ )
        {
            if(i == 0)
            {
                atn[i] = new Attraction("Roller Coaster", 85.85);
            }
            else if(i == 1)
            {
                atn[i] = new Attraction("Ferris Wheel", 54.54);
            }
            else
            {
                atn[i] = new Attraction("Haunted Castle", 67.67);
            }
        }

        
        /* ========== DO NOT EDIT THIS PART ========== */
        /*
            This loop creates multiple instances of Ticket, and places them in the array of Tickets.
            Students are NOT ALLOWED to edit this code.
        */
        for( int i = 0; i < tks.length; i++ )
        {
            if( i % 4 == 0 )
                tks[i] = new Ticket( 150.00 );
            else if( i % 4 == 1 )
                tks[i] = new Ticket( 85.85 );
            else if( i % 4 == 2 )
                tks[i] = new Ticket( 54.54 );
            else
                tks[i] = new Ticket( 67.67 );
        }
        
        /*
            This loop performs multiple scanTicket operations on a specific TicketScanner.
            All Tickets are scanned in this loop.
            Students are NOT ALLOWED to edit this code.
        */
        for( int i = tks.length-1; i >= 0; i-- )
        {
            ts[i%ts.length].scanTicket( atn[i%atn.length], tks[i] );
        }
        
        /*
            This loop performs multiple scanTicket operations on a specific TicketScanner.
            Only the all-access tickets are scanned again in this loop.
            Students are NOT ALLOWED to edit this code.
        */
        for( int i = 0; i < tks.length; i++ )
        {
            if( tks[i].isAllAccess() )
                ts[i%ts.length].scanTicket( atn[i%atn.length], tks[i] );
        }
        
        /*
            Print the details of each TicketScanner.
            Use a loop, where appropriate.
        */
        System.out.println("\n-------------------- MY THEME PARK REPORT --------------------");
        System.out.println("|   Scanner | Collection | SAT | AAT | REJECT | RC | FW | HC |");
        System.out.println("--------------------------------------------------------------");
        for( int i = 0; i < ts.length; i++)
        {
            System.out.printf("| Scanner %d | Php %.2f |   %d |   %d |      %d |  %d |  %d |  %d |\n", i+1, ts[i%ts.length].getCollections(), ts[i%ts.length].getSingleAccess(), ts[i%ts.length].getAllAccess(), ts[i%ts.length].getRejects(), ts[i%ts.length].getRollerCoaster(), ts[i%ts.length].getFerrisWheel(), ts[i%ts.length].getHauntedCastle());
        }
        System.out.println("--------------------------------------------------------------");
    }
}