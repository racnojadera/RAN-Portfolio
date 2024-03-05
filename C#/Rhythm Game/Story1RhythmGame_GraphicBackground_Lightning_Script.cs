using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story1RhythmGame_GraphicBackground_Lightning_Script : MonoBehaviour
{
    public ScoreManager missDetection;
    public List<GameObject> allLLight, allRLight;

    public float currentTime;

    // Start is called before the first frame update
    void Start()
    {
        for(int i = 0; i < 4; i++)
        {
            allLLight[i].SetActive(false);
            allRLight[i].SetActive(false);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(missDetection.GetMiss())
        {
            PlayLightning();
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                allLLight[i].SetActive(false);
                allRLight[i].SetActive(false);
            }
        }
    }

    void PlayLightning()
    {
        currentTime = Time.time;
        currentTime = (float)(((Time.time) % 0.8) * 10);
        for (int i = 0; i < 4; i++)
        {
            allLLight[i].SetActive(false);
            allRLight[i].SetActive(false);
        }
        if (currentTime < 2)
        {
            allLLight[0].SetActive(true);
            allRLight[0].SetActive(true);
        }
        else if (currentTime < 4)
        {
            allLLight[1].SetActive(true);
            allRLight[1].SetActive(true);
        }
        else if (currentTime < 6)
        {
            allLLight[2].SetActive(true);
            allRLight[2].SetActive(true);
        }
        else if (currentTime < 8)
        {
            for (int i = 0; i < 4; i++)
            {
                allLLight[i].SetActive(false);
                allRLight[i].SetActive(false);
            }
            missDetection.ResetMiss();
        }
    }
}
