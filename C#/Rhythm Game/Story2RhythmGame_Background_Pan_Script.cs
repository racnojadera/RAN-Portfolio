using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story2RhythmGame_Background_Pan_Script : MonoBehaviour
{
    public AudioSource backgroundMusic;
    public GameObject churches, collapsableBuildings, gesu;
    public List<GameObject> allCollapsibleBuildingsList;
    private float multiplier = 1.01f;

    // Update is called once per frame
    void Update()
    {
        if((backgroundMusic.time > 0) && (backgroundMusic.time < 53))
        {
            this.transform.position += new Vector3(0.0282f/multiplier, 0.0f, 0.0f);
            churches.transform.position += new Vector3(0.0282f/multiplier, 0.0f, 0.0f);
            for(int i = 0; i < allCollapsibleBuildingsList.Count; i++)
            {
                allCollapsibleBuildingsList[i].transform.position += new Vector3(0.0282f / multiplier, 0.0f, 0.0f);
            }
            //collapsableBuildings.transform.position += new Vector3(0.0282f/multiplier, 0.0f, 0.0f);
            gesu.transform.position += new Vector3(0.0282f/multiplier, 0.0f, 0.0f);
        }
    }
}
