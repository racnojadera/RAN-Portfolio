using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AdminMode : MonoBehaviour
{
    bool isActive = false;

    bool aKey, dKey, mKey, iKey, nKey;
    // Start is called before the first frame update
    void Start()
    {
        aKey = false;
        dKey = false;
        mKey = false;
        iKey = false;
        nKey = false;
    }

    void Update()
    {
        ListenForKeyInputs();
        if(aKey && dKey && mKey && iKey && nKey)
        {
            toggleAdminMode();
            aKey = false;
            dKey = false;
            mKey = false;
            iKey = false;
            nKey = false;
        }
    }
    // Update is called once per frame
    public void toggleAdminMode()
    {
        if(!isActive)
        {
            isActive = true;
        }
        else
        {
            isActive = false;
        }
    }

    public bool getAdminStatus()
    {
        return isActive;
    }

    public void showBoolStatus()
    {
        Debug.Log(isActive);
    }

    void ListenForKeyInputs()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            aKey = true;
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            dKey = true;
        }
        if (Input.GetKeyDown(KeyCode.M))
        {
            mKey = true;
        }
        if (Input.GetKeyDown(KeyCode.I))
        {
            iKey = true;
        }
        if (Input.GetKeyDown(KeyCode.N))
        {
            nKey = true;
        }
    }
}
