using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story3RhythmGame_Background_BanderitasTransition_Script : MonoBehaviour
{
    public AudioSource backgroundMusic;
    public List<GameObject> banderitasPhase1, banderitasPhase2;
    public GameObject banderitasPhase3;
    // Start is called before the first frame update
    void Start()
    {
        InitializeLists();
    }

    // Update is called once per frame
    void Update()
    {
        if(backgroundMusic.time >= 23)
        {
            for(int i = 0; i < banderitasPhase1.Count; i++)
            {
                banderitasPhase1[i].SetActive(true);
            }
        }
        if(backgroundMusic.time >= 46)
        {
            for(int i = 0; i < banderitasPhase2.Count; i++)
            {
                banderitasPhase2[i].SetActive(true);
            }
        }
        if(backgroundMusic.time >= 69)
        {
            banderitasPhase3.SetActive(true);
        }
    }

    void InitializeLists()
    {
        for(int i = 0; i < banderitasPhase1.Count; i++)
        {
            banderitasPhase1[i].SetActive(false);
        }
        for(int i = 0; i < banderitasPhase2.Count; i++)
        {
            banderitasPhase2[i].SetActive(false);
        }
        banderitasPhase3.SetActive(false);
    }
}
