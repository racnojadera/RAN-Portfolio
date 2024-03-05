using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.IO;
using UnityEngine.SceneManagement;

public class SelectionMenuScript : MonoBehaviour
{
    public static object chosenProcess;
    public ArrayList listOfProcesses = new ArrayList();

    GameObject[] listOfSelectionButtons, listOfSButtonTexts;
    int selectedProcess;

    bool initialized = false;

    string path;

    // Start is called before the first frame update
    void Start()
    {
        listOfSelectionButtons = GameObject.FindGameObjectsWithTag("SelectionPanelButtons");
        listOfSButtonTexts = GameObject.FindGameObjectsWithTag("SelectionPanelButtonTexts");
        path = Application.dataPath;
        initialized = true;
        RefreshProcessesList();
    }

    void InitializeProcessesList(string path)
    {
        DirectoryInfo processesPath = new DirectoryInfo(path + "/StreamingAssets/database/processes");
        FileInfo[] processes = processesPath.GetFiles("*.txt");
        foreach (FileInfo process in processes)
        {
            listOfProcesses.Add(process);
        }
        ResetList();
    }

    public void SetSelectedProcess(int newSelect)
    {
        selectedProcess = newSelect;
    }

    public void ResetList()
    {
        for(int i = 0; i < listOfSelectionButtons.Length; i++)
        {
            listOfSelectionButtons[i].SetActive(false);
        }

        TextMeshProUGUI file;
        for(int i = 0; i < listOfProcesses.Count; i++)
        {
            listOfSelectionButtons[i].SetActive(true);
            file = listOfSButtonTexts[i].GetComponent<TMPro.TextMeshProUGUI>();
            FileInfo fileInfoTemp = (FileInfo)listOfProcesses[i];
            string fileName = fileInfoTemp.Name;
            fileName = fileName.Substring(0, fileName.Length - 4);
            fileName = fileName.Replace("-", " ");
            file.text = fileName;
        }
    }

    public void RefreshProcessesList()
    {
        if(initialized)
        {
            listOfProcesses.Clear();
            InitializeProcessesList(path);
        }
    }

    public void SelectProcess()
    {
        chosenProcess = listOfProcesses[selectedProcess];
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex+1);
    }
}
