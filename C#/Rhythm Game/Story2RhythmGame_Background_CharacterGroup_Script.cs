using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story2RhythmGame_Background_CharacterGroup_Script : MonoBehaviour
{
    public ScoreManager missDetection;
    public List<Story2RhythmGame_Background_Character_Script> characterList;
    private int lives = 3;
    
    private bool missExecuted = true;

    // Update is called once per frame
    void Update()
    {
        /*if(missDetection.GetMiss() && !characterList[0].GetFallenStatus())
        {
            missExecuted = false;
            if(lives < 3)
            {
                characterList[lives].HasFallen();
            }
            lives--;
            missExecuted = true;
        }*/
    }

    /*public bool GetMissStatus()
    {
        return missExecuted;
    }
    public void ResetMissStatus()
    {
        missExecuted = false;
    }*/
}
