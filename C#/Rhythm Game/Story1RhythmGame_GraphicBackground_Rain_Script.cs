using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story1RhythmGame_GraphicBackground_Rain_Script : MonoBehaviour
{
    public GameObject bgNoRain;
    public List<GameObject> allBGRainStrong, allBGRainMedium, allBGRainWeak;
    public List<GameObject> allBGRain;
    private float currentTime;
    private int currentImage = 0;
    public AudioSource backgroundMusic;

    // Start is called before the first frame update
    void Start()
    {
        InitializeLists();
    }

    // Update is called once per frame
    void Update()
    {
        CheckPhase();
        currentTime = Time.time;
        currentTime = (float)((currentTime % 0.4) * 10);
        allBGRain[currentImage].SetActive(false);
        if(backgroundMusic.time < 51)
        {
            if (currentTime < 1)
            {
                currentImage = 0;
            }
            else if (currentTime < 2)
            {
                currentImage = 1;
            }
            else if (currentTime < 3)
            {
                currentImage = 2;
            }
            else if (currentTime < 4)
            {
                currentImage = 3;
            }
            allBGRain[currentImage].SetActive(true);
        }
        else
        {
            for(int i = 0; i < allBGRainWeak.Count; i++)
            {
                allBGRainWeak[i].SetActive(false);
            }
            for(int i = 0; i < allBGRainMedium.Count; i++)
            {
                allBGRainMedium[i].SetActive(false);
            }
            for(int i = 0; i < allBGRainStrong.Count; i++)
            {
                allBGRainStrong[i].SetActive(false);
            }
            bgNoRain.SetActive(true);
        }
    }

    void InitializeLists()
    {
        for(int i = 0; i < allBGRainWeak.Count; i++)
        {
            allBGRainWeak[i].SetActive(false);
        }
        for(int i = 0; i < allBGRainMedium.Count; i++)
        {
            allBGRainMedium[i].SetActive(false);
        }
        for(int i = 0; i < allBGRainStrong.Count; i++)
        {
            allBGRainStrong[i].SetActive(false);
        }
        bgNoRain.SetActive(false);
    }

    public void CheckPhase()
    {
        if(backgroundMusic.time < 17)
        {
            allBGRain = allBGRainStrong;
        }
        else if(backgroundMusic.time < 34)
        {
            allBGRain = allBGRainMedium;
        }
        else if(backgroundMusic.time < 51)
        {
            allBGRain = allBGRainWeak;
        }
    }
}
