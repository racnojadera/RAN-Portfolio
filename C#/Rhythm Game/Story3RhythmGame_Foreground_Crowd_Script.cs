using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story3RhythmGame_Foreground_Crowd_Script : MonoBehaviour
{
    public ScoreManager healthStatus;
    public List<GameObject> listCrowd;
    public AudioSource backgroundMusic;

    private float currentTime;
    private int crowdModeHealth = 0;
    private bool missExecuted = true;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        CheckHealth();
        InitializeList();
        ChangeImage(crowdModeHealth);
    }

    void CheckHealth()
    {
        if(healthStatus.GetHealth() >= 16)
        {
            crowdModeHealth = 0;
        }
        else if(healthStatus.GetHealth() >= 11)
        {
            crowdModeHealth = 1;
        }
        else if(healthStatus.GetHealth() >= 6)
        {
            crowdModeHealth = 2;
        }
        else if(healthStatus.GetHealth() >= 1)
        {
            crowdModeHealth = 3;
        }
        else
        {
            crowdModeHealth = 4;
        }
    }

    void InitializeList()
    {
        for(int i = 0; i < listCrowd.Count; i++)
        {
            listCrowd[i].SetActive(false);
        }
    }

    void ChangeImage(int mode)
    {
        listCrowd[mode].SetActive(true);
    }

    public bool GetMissStatus()
    {
        return missExecuted;
    }
    public void ResetMissStatus()
    {
        missExecuted = false;
    }
}
