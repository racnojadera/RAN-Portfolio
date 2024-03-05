using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story2RhythmGame_Background_Character_Script : MonoBehaviour
{
    public List<GameObject> tribalWalking, tribalMiss, priestWalking, priestMiss;

    public AudioSource backgroundMusic;

    private float currentTime;
    private int currentImage = 0;
    private bool fallen = false;
    private bool missAnimationDone = false;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (!fallen)
        {
            if((backgroundMusic.time > 0) && (backgroundMusic.time < 27.5f))
            {
                UpdateTribal();
            }
            else if(backgroundMusic.time > 27.5f)
            {
                tribalWalking[currentImage].SetActive(false);
                UpdatePriest();
            }
        }
        else
        {
            PlayerMissed();
        }
        MoveCharacter();
    }

    void PlayerMissed()
    {
        tribalWalking[0].SetActive(false);
        tribalWalking[1].SetActive(false);
        priestWalking[0].SetActive(false);
        priestWalking[1].SetActive(false);
        if ((backgroundMusic.time > 0) && (backgroundMusic.time < 27.5f))
        {
            if(!missAnimationDone)
            {
                UpdateTribalMissed();
            }
        }
        else
        {
            if(!missAnimationDone)
            {
                UpdatePriestMissed();
            }
        }
    }

    void UpdateTribal()
    {
        tribalWalking[currentImage].SetActive(false);
        if (backgroundMusic.time > 54)
        {
            currentImage = 0;
        }
        else
        {
            currentTime = Time.time;
            currentTime = (float)((currentTime % 0.2) * 10);

            if (currentTime < 1)
            {
                currentImage = 0;
            }
            else
            {
                currentImage = 1;
            }
        }
        tribalWalking[currentImage].SetActive(true);
    }

    void UpdatePriest()
    {
        priestWalking[currentImage].SetActive(false);
        if(backgroundMusic.time > 54)
        {
            currentImage = 0;
        }
        else
        {
            currentTime = Time.time;
            currentTime = (float)((currentTime % 0.2) * 10);

            if (currentTime < 1)
            {
                currentImage = 0;
            }
            else
            {
                currentImage = 1;
            }
        }
        priestWalking[currentImage].SetActive(true);
    }

    void UpdateTribalMissed()
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % 0.5) * 10);
        tribalMiss[currentImage].SetActive(false);

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
        else if(currentTime < 5)
        {
            currentImage = 4;
            missAnimationDone = true;
        }
        tribalMiss[currentImage].SetActive(true);
    }

    void UpdatePriestMissed()
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % 0.6) * 10);
        priestMiss[currentImage].SetActive(false);

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
        else if(currentTime < 5)
        {
            currentImage = 4;
        }
        else if(currentTime < 6)
        {
            currentImage = 5;
            missAnimationDone = true;
        }
        priestMiss[currentImage].SetActive(true);
    }

    void MoveCharacter()
    {
        if(((backgroundMusic.time > 53) && (backgroundMusic.time < 54)) && !fallen)
        {
            this.transform.position += new Vector3(-0.0248f, 0, 0);
        }
        else if((fallen))
        {
            this.transform.position += new Vector3(0.0285f, 0, 0);
        }
    }

    public bool GetFallenStatus()
    {
        return fallen;
    }

    public void HasFallen()
    {
        fallen = true;
    }
}