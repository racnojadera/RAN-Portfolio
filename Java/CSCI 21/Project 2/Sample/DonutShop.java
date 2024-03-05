
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
public class DonutShop
{
    // instance variables - replace the example below with your own
    private double price, totalSales, bill;
    private int availability, donutsSold, freeDonuts;

    public DonutShop()
    {
        // initialise instance variables
        bill = 0;
        price = 30.00;
        availability = 10;
        totalSales = 0;
        donutsSold = 0;
        freeDonuts = 0;
    }

    public double selldonuts(int donutsOrdered, int loyaltyCard)
    {
        if(donutsOrdered > availability)
            return 0;
        else if(donutsOrdered <= availability)
            if(loyaltyCard >= 15)
            {
                availability -= donutsOrdered;
                freeDonuts += 1;
                donutsSold += (donutsOrdered-1);
                bill = price*(donutsOrdered - 1);
            }
            else if(loyaltyCard <= 15)
            {
                availability -= donutsOrdered;
                bill = price*donutsOrdered;
                donutsSold += donutsOrdered;
            }
            totalSales += bill;
            return bill;
    }
    
    public void refillDonuts(int num)
    {
        availability += num;
    }
    
    public void changePrice(double newCost)
    {
        price = newCost;
    }
    
    public double getSales()
    {
        return totalSales;
    }
    
    public int getSoldDonuts()
    {
        return donutsSold;
    }
    
    public int getFreeDonuts()
    {
        return freeDonuts;
    }
}
