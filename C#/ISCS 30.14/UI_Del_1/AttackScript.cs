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
    private Attack shadowPunch = new Attack("Shadow Punch", 3);

    public bool dragonChosen = false, squidChosen = false, lonerChosen =false;
    public GameObject fireBut,inkBut,fireInkBut, shadowPunchBut;
    public Toggle dragonToggle, squidToggle, lonerToggle;
    public Text attackText;

    void start(){
        attackArray[0] = fireBreath;
        attackArray[1] = inkSquirt;
        attackArray[2] = fireInkFusion;
        attackArray[3] = shadowPunch;
    }

    void Update(){
        if(dragonChosen || squidChosen)
        {
            lonerToggle.interactable=false;
        } else 
        {
            lonerToggle.interactable=true;
        }

        if(lonerChosen)
        {
            dragonToggle.interactable = false;
            squidToggle.interactable = false;
        }else 
        {
            dragonToggle.interactable = true;
            squidToggle.interactable = true;
        }

    }
    public void updateMoves()
    {
        

        if (!dragonChosen && !squidChosen && !lonerChosen )
        {
            fireBut.SetActive(false);
            inkBut.SetActive(false);
            fireInkBut.SetActive(false);
            shadowPunchBut.SetActive(false);
        }else if(dragonChosen && !squidChosen && !lonerChosen)
        {
            fireBut.SetActive(true);
            inkBut.SetActive(false);
            fireInkBut.SetActive(false);
            shadowPunchBut.SetActive(false);
        }else if(!dragonChosen && squidChosen && !lonerChosen)
        {
            fireBut.SetActive(false);
            inkBut.SetActive(true);
            fireInkBut.SetActive(false);
            shadowPunchBut.SetActive(false);
        }else if(dragonChosen && squidChosen && !lonerChosen)
        {
            fireBut.SetActive(true);
            inkBut.SetActive(true);
            fireInkBut.SetActive(true);
            shadowPunchBut.SetActive(false);
        }else if(!dragonChosen && !squidChosen && lonerChosen)
        {
            fireBut.SetActive(false);
            inkBut.SetActive(false);
            fireInkBut.SetActive(false);
            shadowPunchBut.SetActive(true);
        }
    }

    public void dragonUpdate()
    {
        if (dragonChosen)
        {
            dragonChosen = false;
        }else
        {
            dragonChosen = true;
        }
    }

    public void squidUpdate()
    {
        if (squidChosen)
        {
            squidChosen = false;
        }else
        {
            squidChosen = true;
        }
    }

    public void lonerUpdate()
    {
        if (lonerChosen)
        {
            lonerChosen = false;
        }else
        {
            lonerChosen = true;
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
    public void shadowPunchUpdate()
    {
        attackText.GetComponent<Text>().text = "Loner used Shadow Punch";
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