using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ColorButton : MonoBehaviour
{
    private bool darkModeBool;
    public Button[] buttons;
    private Color buttonColor;
    private Options optionScript;
    private GameObject optionsObj;
    // Start is called before the first frame update
    void Start()
    {
        optionsObj = GameObject.Find("OptionScript");
        optionScript = optionsObj.GetComponent <Options> ();
    }

    // Update is called once per frame
    public void switchColor()
    {   
        
        darkModeBool = optionScript.darkModeBool;

        foreach (Button x in buttons)
        {
            buttonColor = x.GetComponent<Image>().color;
            if(darkModeBool){
                x.GetComponent<Image>().color = new Color(0.407f,0.407f,0.407f);
                x.GetComponentInChildren<Text>().color = new Color(1,1,1);
            }else
            {
                x.GetComponent<Image>().color = new Color(1,1,1);
                x.GetComponentInChildren<Text>().color = new Color(0,0,0);
            }
        }
        
    }
}
