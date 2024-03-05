using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story1RhythmGame_GraphicBackground_Waves_Script : MonoBehaviour
{
    public List<GameObject> allBGWaves;
    private float currentTime;
    private int currentImage = 0;

    // Start is called before the first frame update
    void Start()
    {
        for(int i = 0; i < allBGWaves.Count; i++)
        {
            allBGWaves[i].SetActive(false);
        }
    }

    // Update is called once per frame
    void Update()
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % 0.4) * 10);
        allBGWaves[currentImage].SetActive(false);
        if(currentTime < 1)
        {
            currentImage = 0;
        }
        else if(currentTime < 2)
        {
            currentImage = 1;
        }
        else if(currentTime < 3)
        {
            currentImage = 2;
        }
        else if(currentTime < 4)
        {
            currentImage = 3;
        }
        allBGWaves[currentImage].SetActive(true);
    }
}
