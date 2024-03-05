using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuScreen_MainMenuScreenScript : MonoBehaviour
{
    public AudioSource mainSinulogThemeBGM, clickSFX;
    public List<GameObject> mainMenuButtonList;
    private int mainMenuSelector = 0;


    // Start is called before the first frame update
    void Start()
    {
        mainSinulogThemeBGM.Play();
    }

    // Update is called once per frame
    void Update()
    {
        AdjustSelectionMainMenu();
        SelectButtonMainMenu();
    }

    void AdjustSelectionMainMenu()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            clickSFX.Play();
            if (mainMenuSelector == 0)
            {
                mainMenuSelector = 2;
            }
            else
            {
                mainMenuSelector -= 1;
            }
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            clickSFX.Play();
            if (mainMenuSelector == 2)
            {
                mainMenuSelector = 0;
            }
            else
            {
                mainMenuSelector += 1;
            }
        }
        UpdateSelection();
    }

    void UpdateSelection()
    {
        for (int i = 0; i < 3; i++)
        {
            mainMenuButtonList[i].transform.localScale = new Vector3(0.9f, 0.9f, 0.9f);
        }
        mainMenuButtonList[mainMenuSelector].transform.localScale = new Vector3(1.4f, 1.4f, 1.4f);
    }

    void SelectButtonMainMenu()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            mainSinulogThemeBGM.Stop();
            switch (mainMenuSelector)
            {
                case 0:
                    SceneManager.LoadScene("StorySelectionScreenScene");
                    break;
                case 1:
                    print("To be implemented");
                    break;
                case 2:
                    Application.Quit();
                    break;
            }
        }
    }
}
