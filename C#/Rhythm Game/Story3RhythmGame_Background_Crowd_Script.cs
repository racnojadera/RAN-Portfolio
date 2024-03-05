using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story3RhythmGame_Background_Crowd_Script : MonoBehaviour
{
    public AudioSource backgroundMusic;
    public List<GameObject> listCrowd;
    private int currentImage = 0;

    // Start is called before the first frame update
    void Start()
    {
        InitializeList();
    }

    // Update is called once per frame
    void Update()
    {
        InitializeList();
        if(backgroundMusic.time >= 69)
        {
            currentImage = 3;
        }
        else if(backgroundMusic.time >= 46)
        {
            currentImage = 2;
        }
        else if(backgroundMusic.time >= 23)
        {
            currentImage = 1;
        }
        else
        {
            currentImage = 0;
        }
        listCrowd[currentImage].SetActive(true);
    }

    void InitializeList()
    {
        for(int i = 0; i < listCrowd.Count; i++)
        {
            listCrowd[i].SetActive(false);
        }
    }
}
