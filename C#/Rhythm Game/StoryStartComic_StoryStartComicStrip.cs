using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class StoryStartComic_StoryStartComicStrip : MonoBehaviour
{
    public List<GameObject> comic1, comic2, comic3;
    private List<GameObject> comicStrip;
    private int currentPageMarker = 0;
    private int currentStory;
    // Start is called before the first frame update
    void Start()
    {
        currentStory = StorySelectScreen_StorySelectScreenScript.currentStoryNumber;
        InitializeComicPages();
    }

    // Update is called once per frame
    void Update()
    {
        GoToNextPreviousPage();
    }

    void InitializeComicPages()
    {
        for(int i = 0; i < comic1.Count; i++)
        {
            comic1[i].SetActive(false);
        }
        for(int i = 0; i < comic2.Count; i++)
        {
            comic2[i].SetActive(false);
        }
        for(int i = 0; i < comic3.Count; i++)
        {
            comic3[i].SetActive(false);
        }

        switch(currentStory)
        {
            case 1:
                comicStrip = comic1;
                break;
            case 2:
                comicStrip = comic2;
                break;
            case 3:
                comicStrip = comic3;
                break;
        }
        comicStrip[0].SetActive(true);
    }

    void GoToNextPreviousPage()
    {
        if((Input.GetKeyDown(KeyCode.RightArrow)) || (Input.GetKeyDown(KeyCode.Return)))
        {
            if(currentPageMarker == (comicStrip.Count - 1))
            {
                switch(currentStory)
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
            }
            else
            {
                currentPageMarker += 1;
                RefreshComic();
            }
        }
        else if ((Input.GetKeyDown(KeyCode.LeftArrow)) || (Input.GetKeyDown(KeyCode.Backspace)))
        {
            if(currentPageMarker != 0)
            {
                currentPageMarker -= 1;
                RefreshComic();
            }
        }
    }

    void RefreshComic()
    {
        for(int i = 0; i < comicStrip.Count; i++)
        {
            comicStrip[i].SetActive(false);
        }
        comicStrip[currentPageMarker].SetActive(true);
    }
}
