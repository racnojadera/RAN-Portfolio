using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CongratulationsSceneEndScript : MonoBehaviour
{
    float currentTime;
    void Awake()
    {
        currentTime = 5.0f;
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(currentTime > 0.0f)
        {
            currentTime -= Time.deltaTime;
        }
        else
        {
            Application.Quit();
        }
    }
}
