using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Story2RhythmGame_Background_CharacterBuildingMiss_Script : MonoBehaviour
{
    public Story2RhythmGame_Background_CollapsableBuildingGroup_Script backgroundMiss;
    public Story2RhythmGame_Background_CharacterGroup_Script characterMiss;
    public Story2RhythmGame_Background_StoNino_Script stoNino;
    public ScoreManager scoreMiss;
    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        if(!backgroundMiss.GetMissStatus()) //&& characterMiss.GetMissStatus())
        {
            stoNino.AddError();
            scoreMiss.ResetMiss();
            //backgroundMiss.ResetMissStatus();
            //characterMiss.ResetMissStatus();
        }
    }
}
