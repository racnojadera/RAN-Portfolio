using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story3RhythmGame_Background_CharacterMovement_Script : MonoBehaviour
{
    public List<GameObject> characterHealthy, characterDamaged, characterBad;
    public ScoreManager healthStatus;
    public AudioSource backgroundMusic;

    private int characterModeHealth = 1;
    private float currentTime;
    // Start is called before the first frame update
    void Start()
    {
        InitializeList();
    }

    // Update is called once per frame
    void Update()
    {
        CheckHealth();
        InitializeList();
        ChangeImage(characterModeHealth);
    }

    void InitializeList()
    {
        for(int i = 0; i < characterHealthy.Count; i++)
        {
            characterHealthy[i].SetActive(false);
        }
        for(int i = 0; i < characterDamaged.Count; i++)
        {
            characterDamaged[i].SetActive(false);
        }
        for(int i = 0; i < characterBad.Count; i++)
        {
            characterBad[i].SetActive(false);
        }
    }

    void CheckHealth()
    {
        if(healthStatus.GetHealth() >= 12)
        {
            characterModeHealth = 1;
        }
        else if(healthStatus.GetHealth() >=6)
        {
            characterModeHealth = 2;
        }
        else
        {
            characterModeHealth = 3;
        }
    }

    void ChangeImage(int mode)
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % (3*mode) * 10));
        switch(mode)
        {
            case 1:
                characterHealthy[(int)currentTime].SetActive(true);
                break;
            case 2:
                characterDamaged[(int)currentTime/6].SetActive(true);
                break;
            case 3:
                characterBad[(int)currentTime/9].SetActive(true);
                break;
        }
        
    }
}