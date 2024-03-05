using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LoseScreen_LoseScreenScript : MonoBehaviour
{
    public List<GameObject> loseScreenButtonList;
    public TMPro.TextMeshPro loseLabel;
    private int loseScreenSelector = 0;
    private int currentStory;
    public AudioSource clickSFX;

    // Start is called before the first frame update
    void Start()
    {
        currentStory = StorySelectScreen_StorySelectScreenScript.currentStoryNumber;
        switch(currentStory)
        {
            case 1:
                loseLabel.text = "Oh no! Magellan failed to arrive in the \nPhilippines! The Sto. Nino and its culture will \nnot be passed on to the Filipino ancestors!";
                break;
            case 2:
                loseLabel.text = "Oh no! The Cebuanos were unable to uphold \nSto.Nino and its celebration!The tradition \nhas been lost in time!";
                break;
            case 3:
                loseLabel.text = "Oh no! The Sinulog tradition was a complete \ndisaster! The people are now uninterested \nand the tradition has lost its value!";
                break;
        }
    }

    // Update is called once per frame
    void Update()
    {
        AdjustSelectionLoseScreen();
        SelectButtonLoseScreen();
    }

    void AdjustSelectionLoseScreen()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            clickSFX.Play();
            if (loseScreenSelector == 0)
            {
                loseScreenSelector = 2;
            }
            else
            {
                loseScreenSelector -= 1;
            }
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            clickSFX.Play();
            if (loseScreenSelector == 2)
            {
                loseScreenSelector = 1;
            }
            else
            {
                loseScreenSelector += 1;
            }
        }
        UpdateSelection();
    }

    void UpdateSelection()
    {
        for (int i = 0; i < 3; i++)
        {
            loseScreenButtonList[i].transform.localScale = new Vector3(0.9f, 0.9f, 0.9f);
        }
        loseScreenButtonList[loseScreenSelector].transform.localScale = new Vector3(1.4f, 1.4f, 1.4f);
    }

    void SelectButtonLoseScreen()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            switch (loseScreenSelector)
            {
                case 0:
                    switch (currentStory)
                    {
                        case 1:
                            SceneManager.LoadScene("Story1RhythmGameScene");
                            break;
                        case 2:
                            SceneManager.LoadScene("Story2RhythmGameScene");
                            break;
                        case 3:
                            SceneManager.LoadScene("Story3RhythmGameScene");
                            break;
                    }
                    break;

                case 1:
                    SceneManager.LoadScene("StorySelectionScreenScene");
                    break;

                case 2:
                    Application.Quit();
                    break;
            }
        }
    }
}
