using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Options : MonoBehaviour
{
    // Start is called before the first frame update
    public bool darkModeBool = true;

    // Update is called once per frame
    public void darkModeUpdate()
    {
        if (darkModeBool)
        {
            darkModeBool = false;
        }else
        {
            darkModeBool = true;
        }
    }
}
