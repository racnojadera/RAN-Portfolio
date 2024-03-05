using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story1RhythmGame_GraphicBackground_StoNino_Script : MonoBehaviour
{
    private bool isGameOver;
    public ScoreManager health;
    public GameObject stoNinoHealthy;
    public List<GameObject> allStoNinoDamaged, allStoNinoBad;
    private int currentImage, currentStoNinoStatus;
    private float currentTime, orientationTime, finalMultiplier;

    public AudioSource backgroundMusic;

    // Start is called before the first frame update
    void Start()
    {
        stoNinoHealthy.SetActive(false);
        isGameOver = false;
        for (int i = 0; i < 12; i++)
        {
            allStoNinoDamaged[i].SetActive(false);
            allStoNinoBad[i].SetActive(false);
        }
        finalMultiplier = 0;
        currentImage = 0;
        currentStoNinoStatus = 1;
    }

    // Update is called once per frame
    void Update()
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % 1) * 10);
        orientationTime = Time.time;
        orientationTime = (float)((orientationTime % 0.8) * 10);
        CheckHealthStatus();
        AdjustCurrentImage();
        CheckOrientation();
        MoveAshore();
    }

    public void CheckHealthStatus()
    {
        if (health.GetHealth() >= 15)
        {
            currentStoNinoStatus = 1;
        }
        else if (health.GetHealth() >= 10)
        {
            currentStoNinoStatus = 2;
        }
        else if (health.GetHealth() >= 5)
        {
            currentStoNinoStatus = 3;
        }
        else
        {
            currentStoNinoStatus = 4;
        }
    }

    public void AdjustCurrentImage()
    {
        stoNinoHealthy.SetActive(false);
        allStoNinoDamaged[currentImage].SetActive(false);
        allStoNinoBad[currentImage].SetActive(false);

        if (backgroundMusic.time > 56.5)
        {
            currentImage = 1;
        }
        else
        {
            if (currentStoNinoStatus != 1)
            {
                if (currentTime < 0.5)
                {
                    currentImage = 0;
                }
                else if (currentTime < 1)
                {
                    currentImage = 1;
                }
                else if (currentTime < 1.5)
                {
                    currentImage = 2;
                }
                else if (currentTime < 2)
                {
                    currentImage = 3;
                }
                else if (currentTime < 2.5)
                {
                    currentImage = 4;
                }
                else if (currentTime < 3)
                {
                    currentImage = 5;
                }
                else if (currentTime < 3.5)
                {
                    currentImage = 6;
                }
                else if (currentTime < 4)
                {
                    currentImage = 7;
                }
                else if (currentTime < 4.5)
                {
                    currentImage = 8;
                }
                else if (currentTime < 5)
                {
                    currentImage = 9;
                }
                else if (currentTime < 5.5)
                {
                    currentImage = 10;
                }
                else if (currentTime < 6)
                {
                    currentImage = 11;
                }
            }
        }

        if (currentStoNinoStatus == 1)
        {
            stoNinoHealthy.SetActive(true);
            allStoNinoDamaged[currentImage].SetActive(false);
            allStoNinoBad[currentImage].SetActive(false);
        }
        else if (currentStoNinoStatus == 2)
        {
            stoNinoHealthy.SetActive(false);
            allStoNinoDamaged[currentImage].SetActive(true);
            allStoNinoBad[currentImage].SetActive(false);
        }
        else if (currentStoNinoStatus == 3)
        {
            stoNinoHealthy.SetActive(false);
            allStoNinoDamaged[currentImage].SetActive(false);
            allStoNinoBad[currentImage].SetActive(true);
        }
        else if (currentStoNinoStatus == 4)
        {
            if (!isGameOver)
            {
                stoNinoHealthy.transform.position = allStoNinoBad[currentImage].transform.position;
                stoNinoHealthy.SetActive(true);
                isGameOver = true;
            }
            else
            {
                stoNinoHealthy.SetActive(true);
                stoNinoHealthy.transform.position += new Vector3(0.02f, -0.0003f, 0);
                stoNinoHealthy.transform.rotation = Quaternion.Euler(0, 0, Time.time * (-320.0f));
            }

            allStoNinoDamaged[currentImage].SetActive(false);
            allStoNinoBad[currentImage].SetActive(false);
        }
    }

    public void CheckOrientation()
    {
        if (backgroundMusic.time <= 56)
        {
            if (currentStoNinoStatus == 1)
            {
                if (orientationTime < 2)
                {
                    this.transform.position = new Vector3(0, 0, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, -25);
                }
                else if (orientationTime < 4)
                {
                    this.transform.position = new Vector3(-0.27f, -0.2f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, -16);
                }
                else if (orientationTime < 6)
                {
                    this.transform.position = new Vector3(-0.5f, -0.3f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, -8);
                }
                else if (orientationTime < 8)
                {
                    this.transform.position = new Vector3(-0.27f, -0.2f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, -16);
                }
            }
            else if (currentStoNinoStatus == 2)
            {
                if (orientationTime < 2)
                {
                    this.transform.position = new Vector3(0.4f, -1.99f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, -10);
                }
                else if (orientationTime < 4)
                {
                    this.transform.position = new Vector3(0.45f, -2.02f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, 0);
                }
                else if (orientationTime < 6)
                {
                    this.transform.position = new Vector3(0.46f, -2.06f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, 7);
                }
                else if (orientationTime < 8)
                {
                    this.transform.position = new Vector3(0.45f, -2.02f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, 0);
                }
            }
            else if (currentStoNinoStatus == 3)
            {
                if (orientationTime < 2)
                {
                    this.transform.position = new Vector3(3.15f, -1.15f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, -7);
                }
                else if (orientationTime < 4)
                {
                    this.transform.position = new Vector3(3.07f, -0.72f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, 2);
                }
                else if (orientationTime < 6)
                {
                    this.transform.position = new Vector3(2.92f, -0.45f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, 9);
                }
                else if (orientationTime < 8)
                {
                    this.transform.position = new Vector3(3.07f, -0.72f, 90);
                    this.transform.rotation = Quaternion.Euler(0, 0, 2);
                }
            }
        }
        else
        {
            if (currentStoNinoStatus == 1)
            {
                this.transform.position = new Vector3(-0.27f + finalMultiplier, -0.2f, 90);
                this.transform.rotation = Quaternion.Euler(0, 0, -16);
            }
            else if (currentStoNinoStatus == 2)
            {
                this.transform.position = new Vector3(0.45f + finalMultiplier, -2.02f, 90);
                this.transform.rotation = Quaternion.Euler(0, 0, 0);
            }
            else if (currentStoNinoStatus == 3)
            {
                this.transform.position = new Vector3(3.07f + finalMultiplier, -0.72f, 90);
                this.transform.rotation = Quaternion.Euler(0, 0, 2);
            }
        }
    }

    public void MoveAshore()
    {
        if ((backgroundMusic.time > 56) && (backgroundMusic.time < 57))
        {
            finalMultiplier -= (0.025f);
            //this.transform.position += new Vector3(-0.025f, 0, 0);
        }
    }
}
