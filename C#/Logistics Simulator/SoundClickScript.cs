using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class SoundClickScript : MonoBehaviour
{
    public AudioSource soundClick1;
    public AudioSource soundClick2;
    bool isDone;
    // Start is called before the first frame update
    void Awake()
    {
        Cursor.visible = true;
        isDone = false;
    }

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            if(!isDone)
            {
                soundClick1.Play();
                isDone = !isDone;
            }
            else
            {
                soundClick2.Play();
                isDone = !isDone;
            }
        }
    }
}
