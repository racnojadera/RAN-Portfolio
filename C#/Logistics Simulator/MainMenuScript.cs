using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuScript : MonoBehaviour
{
    public GameObject adminMenu, nonAdminMenu;
    public AdminMode checkAdminPriv;

    bool aKey, dKey, mKey, iKey, nKey;

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
        if (aKey && dKey && mKey && iKey && nKey)
        {
            ChangeAdminMode();
            aKey = false;
            dKey = false;
            mKey = false;
            iKey = false;
            nKey = false;
        }
    }

    public void ChangeAdminMode()
    {
        if(checkAdminPriv.getAdminStatus())
        {
            nonAdminMenu.SetActive(false);
            adminMenu.SetActive(true);
        }
        else
        {
            adminMenu.SetActive(false);
            nonAdminMenu.SetActive(true);
        }
    }

    public void PlayGame()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex +1);
    }

    public void ExitGame()
    {
            Debug.Log("Quit");
            Application.Quit();
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
