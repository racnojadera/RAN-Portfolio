using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RhythmGame_ButtonPressScript : MonoBehaviour
{
    public GameObject leftPress, upPress, downPress, rightPress;
    // Start is called before the first frame update
    void Start()
    {
        SetAllInactive();
    }

    // Update is called once per frame
    void Update()
    {
        SetAllInactive();
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            leftPress.SetActive(true);
        }
        if (Input.GetKey(KeyCode.UpArrow))
        {
            upPress.SetActive(true);
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            downPress.SetActive(true);
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            rightPress.SetActive(true);
        }

    }

    void SetAllInactive()
    {
        leftPress.SetActive(false);
        upPress.SetActive(false);
        downPress.SetActive(false);
        rightPress.SetActive(false);
    }
}
