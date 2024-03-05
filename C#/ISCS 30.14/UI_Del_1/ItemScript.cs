using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemScript : MonoBehaviour
{
    // https://forum.unity.com/threads/how-to-display-variable-in-text.846232/
    //public Text counterText;
    //public float counter = 5;
    public Text elixirText;
    public Text vampyrBldText;
    public Text razorJlyText;
    public float elixirCtr = 5;
    public float vampyrBldCtr = 3;
    public float razorJlyCtr = 4;
    public Text itemText;
    /*
    private Item[] itemArray;
    private Item elixir = new Item("Elixir", 5);
    private Item vampyrBld = new Item("Vampyr Blood", 3);
    private Item razorJly = new Item("Razor Jelly", 4);

    public void Start()
    {
        itemArray[0] = elixir;
        itemArray[1] = vampyrBld;
        itemArray[2] = razorJly;
    }
    */

    // Update is called once per frame
    public void Update()
    {
        //counterText.GetComponent<Text>().text = "Elixir x" + counter.ToString();
        elixirText.GetComponent<Text>().text = "Elixir x" + elixirCtr.ToString();
        vampyrBldText.GetComponent<Text>().text = "Vampyr Blood x" + vampyrBldCtr.ToString();
        razorJlyText.GetComponent<Text>().text = "Razor Jelly x" + razorJlyCtr.ToString();
    }
    /*
    public void decrement()
    {
        counter--;
        if (counter<0) counter = 0;
        counterText.GetComponent<Text>().text = "Elixir x" + counter.ToString();
    }
    */
    public void elixirDecrement()
    {
        //elixirCtr--;
        if (elixirCtr>0) {
            elixirCtr--;
            itemText.GetComponent<Text>().text = "You used Elixir!";
        }
        else {
            itemText.GetComponent<Text>().text = "Out of Elixir!";
        }
    }

    public void vampyrBldDecrement()
    {
        //vampyrBldCtr--;
        if (vampyrBldCtr>0) {
            vampyrBldCtr--;
            itemText.GetComponent<Text>().text = "You used Vampyr Blood!";
        }
        else {
            itemText.GetComponent<Text>().text = "Out of Vampyr Blood!";
        }
    }

    public void razorJlyDecrement()
    {
        //razorJlyCtr--;
        if (razorJlyCtr>0) {
            razorJlyCtr--;
            itemText.GetComponent<Text>().text = "You used Razor Jelly!";
        }
        else {
            itemText.GetComponent<Text>().text = "Out of Razor Jelly!";
        }
    }
}

/*
public class Item
{
    private Text itemName;
    private float itemCounter;

    public Item(Text name, float counter)
    {
        itemName = name;
        itemCounter = counter;
    }
}
*/