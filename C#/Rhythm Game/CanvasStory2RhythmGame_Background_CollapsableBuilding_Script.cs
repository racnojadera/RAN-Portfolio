using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CanvasStory2RhythmGame_Background_CollapsableBuilding_Script : MonoBehaviour
{
    public float buildingType;
    public GameObject healthyBuilding;
    public List<GameObject> buildingSink;

    public AudioSource backgroundMusic;

    private float currentTime;
    private int currentImage = 0;
    public bool collapsed = false;
    private bool missAnimationDone = false;

    // Start is called before the first frame update
    void Start()
    {
        healthyBuilding.SetActive(true);
        for(int i = 0; i < buildingSink.Count; i++)
        {
            buildingSink[i].SetActive(false);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(collapsed)
        {
            healthyBuilding.SetActive(false);
            if(!missAnimationDone)
            {
                UpdateBuildingCollapse();
            }
        }
    }

    void UpdateBuildingCollapse()
    {
        currentTime = Time.time;
        currentTime = (float)((currentTime % (0.5 + buildingType / 10)) * 10);
        buildingSink[currentImage].SetActive(false);

        if (currentTime < 1)
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
            if(buildingType == 0)
            {
                missAnimationDone = true;
            }
        }
        else if(currentTime < 6)
        {
            currentImage = 5;
            if(buildingType == 1)
            {
                missAnimationDone = true;
            }
        }
        else if(currentTime < 7)
        {
            currentImage = 6;
        }
        else if(currentTime < 8)
        {
            currentImage = 7;
            if(buildingType == 2)
            {
                missAnimationDone = true;
            }
        }
        buildingSink[currentImage].SetActive(true);
    }

    public bool GetCollapsedStatus()
    {
        return collapsed;
    }

    public void HasCollapsed()
    {
        collapsed = true;
    }
}
