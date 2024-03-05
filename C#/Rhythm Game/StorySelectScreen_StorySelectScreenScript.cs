using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;



public class StorySelectScreen_StorySelectScreenScript : MonoBehaviour
{
    public static int currentStoryNumber;
    public GameObject storyPlayButton;
    public AudioSource clickSFX;
    public List<GameObject> backgroundStoryBanners;
    public List<GameObject> storyChaptersList;
    public List<AudioSource> storyMusicSnippets;
    private int storySelectVertical = 0;
    private int storySelectHorizontal = 0;

    // Start is called before the first frame update
    void Start()
    {
        Initialize();
        StopAllAudio();
        storyMusicSnippets[0].Play();
    }

    // Update is called once per frame
    void Update()
    {
        AdjustSelectionStoryMenu();
        BackToMainMenuListener();
    }

    void Initialize()
    {
        for(int i = 0; i < backgroundStoryBanners.Count; i++)
        {
            backgroundStoryBanners[i].SetActive(false);
        }
        backgroundStoryBanners[0].SetActive(true);
    }

    void StopAllAudio()
    {
        for(int i = 0; i < storyMusicSnippets.Count; i++)
        {
            storyMusicSnippets[i].Stop();
        }
    }

    void AdjustSelectionStoryMenu()
    {
        if(storySelectVertical == 0)
        {
            if(Input.GetKeyDown(KeyCode.UpArrow))
            {
                if(storySelectHorizontal != 0)
                {
                    clickSFX.Play();
                    storySelectHorizontal -= 1;
                    for(int i = 0; i < storyChaptersList.Count; i++)
                    {
                        storyChaptersList[i].transform.position -= new Vector3(0.0f, 1.5f, 0.0f);
                        storyMusicSnippets[i].Stop();
                    }
                    storyMusicSnippets[storySelectHorizontal].Play();
                }
            }
            else if(Input.GetKeyDown(KeyCode.DownArrow))
            {
                if (storySelectHorizontal < storyChaptersList.Count - 1)
                {
                    clickSFX.Play();
                    storySelectHorizontal += 1;
                    for(int i = 0; i < storyChaptersList.Count; i++)
                    {
                        storyChaptersList[i].transform.position += new Vector3(0.0f, 1.5f, 0.0f);
                        storyMusicSnippets[i].Stop();
                    }
                    storyMusicSnippets[storySelectHorizontal].Play();
                }
            }
            else if(Input.GetKeyDown(KeyCode.RightArrow))
            {
                clickSFX.Play();
                storySelectVertical = 1;
            }
        }
        else if(storySelectVertical == 1)
        {
            if(Input.GetKeyDown(KeyCode.LeftArrow))
            {
                clickSFX.Play();
                storySelectVertical = 0;
            }    
            else if(Input.GetKeyDown(KeyCode.Return))
            {
                SelectStory(storySelectHorizontal + 1);
            }
        }
        UpdateSelection();
    }

    void UpdateSelection()
    {
        if(storySelectVertical == 0)
        {
            for(int i = 0; i < storyChaptersList.Count; i++)
            {
                storyChaptersList[i].transform.localScale = new Vector3(0.9f, 0.9f, 0.9f);
                backgroundStoryBanners[i].SetActive(false);
            }
            storyChaptersList[storySelectHorizontal].transform.localScale = new Vector3(1.3f, 1.3f, 1.3f);
            storyPlayButton.transform.localScale = new Vector3(0.9f, 0.9f, 0.9f);
            backgroundStoryBanners[storySelectHorizontal].SetActive(true);
        }
        else
        {
            for(int i = 0; i < storyChaptersList.Count; i++)
            {
                storyChaptersList[i].transform.localScale = new Vector3(0.9f, 0.9f, 0.9f);
            }
            storyPlayButton.transform.localScale = new Vector3(1.6f, 1.6f, 1.6f);
        }
    }

    void BackToMainMenuListener()
    {
        if(Input.GetKeyDown(KeyCode.Escape) || Input.GetKeyDown(KeyCode.Backspace))
        {
            SceneManager.LoadScene("MainMenuScreenScene");
        }
    }

    void SelectStory(int storyNumber)
    {
        for (int i = 0; i < storyMusicSnippets.Count; i++)
        {
            storyMusicSnippets[i].Pause();
        }
        currentStoryNumber = storyNumber;
        SceneManager.LoadScene("StoryStartComicScene");
    }
}
