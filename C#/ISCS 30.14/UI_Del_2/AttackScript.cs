using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class AttackScript : MonoBehaviour
{
    private Attack[] attackArray;
    private Attack fireBreath = new Attack("Fire Breath", 0);
    private Attack inkSquirt = new Attack("Ink Squirt", 1);
    private Attack fireInkFusion = new Attack("Blinding Fire Breath", 2);


    public bool dragonChosen = false, squidChosen = false;
    public GameObject fireBut,inkBut,fireInkBut;
    public Text attackText;
    void start(){
        attackArray[0] = fireBreath;
        attackArray[1] = inkSquirt;
        attackArray[2] = fireInkFusion;
    }

    public void updateMoves()
    {
        if (!dragonChosen && !squidChosen)
        {
            fireBut.SetActive(false);
            inkBut.SetActive(false);
            fireInkBut.SetActive(false);
            Debug.Log("Removed all");
        }else if(dragonChosen && !squidChosen)
        {
            fireBut.SetActive(true);
            inkBut.SetActive(false);
            fireInkBut.SetActive(false);
            Debug.Log("Removed squid");
        }else if(!dragonChosen && squidChosen)
        {
            fireBut.SetActive(false);
            inkBut.SetActive(true);
            fireInkBut.SetActive(false);
            Debug.Log("Removed dragon");
        }else if(dragonChosen && squidChosen)
        {
            fireBut.SetActive(true);
            inkBut.SetActive(true);
            fireInkBut.SetActive(true);
            Debug.Log("Allow All");
        }
    }

    public void dragonUpdate()
    {
        if (dragonChosen)
        {
            dragonChosen = false;
            Debug.Log("Dragon Chosen: FALSE");
        }else
        {
            dragonChosen = true;
            Debug.Log("Dragon Chosen: TRUE");
        }
    }

    public void squidUpdate()
    {
        if (squidChosen)
        {
            squidChosen = false;
            Debug.Log("Squid Chosen: FALSE");
        }else
        {
            squidChosen = true;
            Debug.Log("Squid Chosen: TRUE");
        }
    }

    public void fireBreathUpdate()
    {
        attackText.GetComponent<Text>().text = "Dragon used Fire Breath";
    }
    public void squirtInkUpdate()
    {
        attackText.GetComponent<Text>().text = "Squid used Ink Squirt";
    }
    public void fireInkUpdate()
    {
        attackText.GetComponent<Text>().text = "Dragon and Squid fused used Blinding Fire Breath";
    }

}

public class Attack
{
    private string attackName;
    private int monsterNum;

    public Attack(string name, int monster)
    {
        attackName = name;
        monsterNum = monster;
    }
    
}