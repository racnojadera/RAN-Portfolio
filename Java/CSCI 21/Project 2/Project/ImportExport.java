
/**
 * Handles the importing and exporting of .txt files
 *
 * @author Raymond Andrew C. Nojadera
 * @version December 8, 2018
 */

import java.io.*;
import java.util.*;

public class ImportExport
{
    private ArrayList<String> allInputs, allFronts, allBacks, toOutput;
    private FileReader reader;
    private String fileName;
    private Scanner in;
    private PrintWriter out;
    private String input, output;
    private int outputLines;
    /**
     * Constructs the values.
     */
    public ImportExport(String name)
    {
        fileName = name;
        outputLines = 0;
        input = "";
        output = "";
        allInputs = new ArrayList<String>();
        allFronts = new ArrayList<String>();
        allBacks = new ArrayList<String>();
        toOutput = new ArrayList<String>();
    }
    
    /**
     * Handles the importing of values: prints them into a single line, breaking them into an array list, and separating them from front and back content.
     */
    public void importTxt() throws FileNotFoundException
    {
        reader = new FileReader(fileName);
        in = new Scanner(reader).useDelimiter(":"); //https://stackoverflow.com/questions/28766377/how-do-i-use-a-delimiter-in-java-scanner/28767091
        while(in.hasNextLine())
        {
            input += in.nextLine() + ":";
        }
        allInputs = new ArrayList(Arrays.asList(input.split(":"))); //https://stackoverflow.com/questions/7488643/how-to-convert-comma-separated-string-to-arraylist/34735419
        for(int i = 0; i < allInputs.size(); i++)
        {
            if(i%2 == 0)
            {
                allFronts.add(allInputs.get(i));
            }
            else
            {
                allBacks.add(allInputs.get(i));
            }
        }

    }
    //https://stackoverflow.com/questions/28766377/how-do-i-use-a-delimiter-in-java-scanner/28767091
    
    /**
     * Constructs a string that adds up all values loaded in the program.
     *
     * @param a gets the string "title" or the front value of a card.
     * @param b gets the title of the deck or the back value of a card.
     */
    public void exportContent(String a, String b)
    {
        output = a + ":" + b;
        toOutput.add(output);
        outputLines++;
    }
    
    /**
     * Breaks the string output from method exportContent into lines and writes them into a .txt file named fileName.
     */
    public void exportTxt() throws FileNotFoundException
    {
        out = new PrintWriter(fileName);
        for(int i = 0; i < outputLines; i++)
        {
            out.println(toOutput.get(i));
        }
        out.close();
    }

    /**
     * Returns the ArrayList allFronts/ array list of all front content
     *
     * @return the ArrayList containing all front content.
     */
    public ArrayList<String> getAllFront()
    {
        return allFronts;
    }
    
    /**
     * Returns the ArrayList allFronts/ array list of all back content
     *
     * @return the ArrayList containing all back content.
     */
    public ArrayList<String> getAllBack()
    {
        return allBacks;
    }
}
