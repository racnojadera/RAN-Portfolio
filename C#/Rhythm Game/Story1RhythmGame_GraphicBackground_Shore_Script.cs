using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story1RhythmGame_GraphicBackground_Shore_Script : MonoBehaviour
{
    public GameObject shoreFront, shoreBack;
    public AudioSource backgroundMusic;

    // Update is called once per frame
    void Update()
    {
        if((backgroundMusic.time > 53) && (backgroundMusic.time < 56))
        {
            shoreFront.transform.position += new Vector3(0.025f, 0, 0);
            shoreBack.transform.position += new Vector3(0.025f, 0, 0);
        }
    }
}
