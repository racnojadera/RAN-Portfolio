using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story2RhythmGame_Background_StoNino_Script : MonoBehaviour
{
    private bool isGameOver;
    private int errorCount = 0;
    public ScoreManager health;
    private float currentTime, orientationTime;
    public AudioSource backgroundMusic;

    // Start is called before the first frame update
    void Start()
    {
        isGameOver = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (((backgroundMusic.time > 53) && (backgroundMusic.time < 54)) && !isGameOver)
        {
            this.transform.position += new Vector3(-0.0248f, 0, 0);
        }
        else if ((isGameOver))
        {
            if (Time.time - currentTime < 0.55f)
            {
                this.transform.position += new Vector3(0, -0.02f, 0);
                this.transform.rotation = Quaternion.Euler(0, 0, (Time.time - currentTime) * 100);
            }
            else
            {
                this.transform.position += new Vector3(0.0275f, 0, 0);
            }
        }
    }

    public void AddError()
    {
        errorCount++;
        if ((errorCount >= 5) && !isGameOver)
        {
            isGameOver = true;
            currentTime = Time.time;
        }
    }
}
