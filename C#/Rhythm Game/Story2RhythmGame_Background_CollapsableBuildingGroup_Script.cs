using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story2RhythmGame_Background_CollapsableBuildingGroup_Script : MonoBehaviour
{
    public ScoreManager missDetection;
    public List<CanvasStory2RhythmGame_Background_CollapsableBuilding_Script> buildingList;
    public List<GameObject> allBuildingsList;
    public List<Story2RhythmGame_Background_Character_Script> characterList;
    public AudioSource backgroundMusic;

    private int lives = 3;
    private float currentTime;
    private int checkIndex;
    public bool missExecuted = true;
    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        for(int i = 0; i < allBuildingsList.Count; i++)
        {
            if((allBuildingsList[i].transform.position.x >= -1500) && (allBuildingsList[i].transform.position.x <= 2000))
            {
                if (missDetection.GetMiss() && missExecuted)
                {
                    Debug.Log(i);
                    missExecuted = false;
                    buildingList[i].HasCollapsed();
                    if (lives < 3)
                    {
                        characterList[lives].HasFallen();
                    }
                    lives--;
                    //missExecuted = true;
                }
            }
        }
        currentTime = backgroundMusic.time-1.60f;
        checkIndex = (int)Mathf.Floor((currentTime/3.2f) + 1);
    }

    public bool GetMissStatus()
    {
        return missExecuted;
    }

    public void ResetMissStatus()
    {
        missExecuted = false;
    }
}
