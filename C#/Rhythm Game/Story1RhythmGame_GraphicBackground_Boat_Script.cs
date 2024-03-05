using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story1RhythmGame_GraphicBackground_Boat_Script : MonoBehaviour
{
    public ScoreManager health;
    public List<GameObject> allBoatHealthy, allBoatDamaged, allBoatBad;
    private float currentTime;
    private int currentImage = 0;
    public AudioSource backgroundMusic;


    // Start is called before the first frame update
    void Start()
    {
        for (int i = 0; i < 4; i++)
        {
            allBoatHealthy[i].SetActive(false);
            allBoatHealthy[i].SetActive(false);
            allBoatHealthy[i].SetActive(false);
        }
    }

    // Update is called once per frame
    void Update()
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % 0.8) * 10);

        allBoatHealthy[currentImage].SetActive(false);
        allBoatDamaged[currentImage].SetActive(false);
        allBoatBad[currentImage].SetActive(false);

        if(backgroundMusic.time > 56)
        {
            currentImage = 1;
        }

        else
        {
            if(currentTime < 2)
            {
                currentImage = 0;
            }
            else if(currentTime < 4)
            {
                currentImage = 1;
            }
            else if(currentTime < 6)
            {
                currentImage = 2;
            }
            else if(currentTime < 8)
            {
                currentImage = 3;
            }
        }

        
        if(health.GetHealth() >= 12)
        {
            allBoatHealthy[currentImage].SetActive(true);
            allBoatDamaged[currentImage].SetActive(false);
            allBoatBad[currentImage].SetActive(false);
        }
        else if(health.GetHealth() >= 6)
        {
            allBoatHealthy[currentImage].SetActive(false);
            allBoatDamaged[currentImage].SetActive(true);
            allBoatBad[currentImage].SetActive(false);
        }
        else
        {
            allBoatHealthy[currentImage].SetActive(false);
            allBoatDamaged[currentImage].SetActive(false);
            allBoatBad[currentImage].SetActive(true);
        }
        
        MoveBoat();
    }

    void MoveBoat()
    {
        if((backgroundMusic.time > 56) && (backgroundMusic.time < 57))
        {
            for(int i = 0; i < 4; i++)
            {
                allBoatHealthy[i].transform.position = allBoatHealthy[i].transform.position + new Vector3(-0.025f, 0, 0);
                allBoatDamaged[i].transform.position = allBoatDamaged[i].transform.position + new Vector3(-0.025f, 0, 0);
                allBoatBad[i].transform.position = allBoatBad[i].transform.position + new Vector3(-0.025f, 0, 0);
            }
        }
    }
}
