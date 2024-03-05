using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using TMPro;
using System;

public class ModifyProcessesScript : MonoBehaviour
{
    public GameObject dropDownAction, dropDownPersonnel, dropDownItem;
    TMPro.TMP_Dropdown ddAction, ddPersonnel, ddItem;
    List<TMPro.TMP_Dropdown.OptionData> allDDODAction = new List<TMPro.TMP_Dropdown.OptionData>();
    List<TMPro.TMP_Dropdown.OptionData> allDDODItem = new List<TMPro.TMP_Dropdown.OptionData>();
    List<TMPro.TMP_Dropdown.OptionData> allDDODPersonnel = new List<TMPro.TMP_Dropdown.OptionData>();
    int m_Index;

    bool hasInitialized = false;

    GameObject[] listOfSubprocessesButtons, listOfSButtonTexts;

    int selectedSubprocess = 0;

    public ReadWriteFilesScript mainScript;
    // Start is called before the first frame update

    void Start()
    {
        listOfSubprocessesButtons = GameObject.FindGameObjectsWithTag("ModifyProcessesButton");
        listOfSButtonTexts = GameObject.FindGameObjectsWithTag("ModifyProcessesButtonTexts");
        hasInitialized = true;
        InitializeProcessesSubprocessesButtonsTexts();
    }

    public void InitializeProcessesSubprocessesButtonsTexts()
    {
        if(hasInitialized)
        {
            ResetScrollPanel();
            ResetDropDowns();
            InitializeDropDowns();
            InitializeScrollPanel();
        }
    }

    public void SetSelectedSubprocess(int newProcess)
    {
        selectedSubprocess = newProcess;
    }

    void ResetDropDowns()
    {
        ddAction = dropDownAction.GetComponent<TMPro.TMP_Dropdown>();
        ddPersonnel = dropDownPersonnel.GetComponent<TMPro.TMP_Dropdown>();
        ddItem = dropDownItem.GetComponent<TMPro.TMP_Dropdown>();

        ddAction.options.Clear();
        ddPersonnel.options.Clear();
        ddItem.options.Clear();
        //ddAction.ClearOptions();
        //ddPersonnel.ClearOptions();
        //ddItem.ClearOptions();
    }

    void InitializeDropDowns()
    {
        TMPro.TMP_Dropdown.OptionData ddodAction1, ddodAction2, ddodAction3;
        ddodAction1 = new TMP_Dropdown.OptionData();
        ddodAction2 = new TMP_Dropdown.OptionData();
        ddodAction3 = new TMP_Dropdown.OptionData();
        ddodAction1.text = "GIVE";
        allDDODAction.Add(ddodAction1);
        ddodAction2.text = "RECEIVE";
        allDDODAction.Add(ddodAction2);
        ddodAction3.text = "END";
        allDDODAction.Add(ddodAction3);
        
        foreach (TMPro.TMP_Dropdown.OptionData message in allDDODAction)
        {
            ddAction.options.Add(message);
            m_Index = allDDODAction.Count - 1;
        }

        ArrayList listOfItems = mainScript.GetListOfItems();
        ArrayList listOfPersonnel = mainScript.GetListOfPersonnel();

        for(int i = 0; i < listOfItems.Count; i++)
        {
            FileInfo fileInfoTemp = (FileInfo)listOfItems[i];
            string fileName = fileInfoTemp.Name;
            fileName = fileName.Substring(0, fileName.Length - 4);

            TMP_Dropdown.OptionData ddodItem = new TMP_Dropdown.OptionData();
            ddodItem.text = fileName;
            allDDODItem.Add(ddodItem);
        }
        
        foreach (TMPro.TMP_Dropdown.OptionData message in allDDODItem)
        {
            ddItem.options.Add(message);
            m_Index = allDDODItem.Count - 1;
        }

        for(int i = 0; i < listOfPersonnel.Count; i++)
        {
            FileInfo fileInfoTemp = (FileInfo)listOfPersonnel[i];
            string fileName = fileInfoTemp.Name;
            fileName = fileName.Substring(0, fileName.Length - 4);

            TMP_Dropdown.OptionData ddodPersonnel = new TMP_Dropdown.OptionData();
            ddodPersonnel.text = fileName;
            allDDODPersonnel.Add(ddodPersonnel);
        }

        foreach (TMPro.TMP_Dropdown.OptionData message in allDDODPersonnel)
        {
            ddPersonnel.options.Add(message);
            m_Index = allDDODPersonnel.Count - 1;
        }
    }

    public void ResetScrollPanel()
    {
        for (int i = 0; i < listOfSubprocessesButtons.Length; i++)
        {
            listOfSubprocessesButtons[i].SetActive(false);
        }
    }

    public void InitializeScrollPanel()
    {
        ArrayList listOfSubprocesses = mainScript.GetListOfSubprocesses();
        TextMeshProUGUI file;
        for (int i = 0; i < listOfSubprocesses.Count; i++)
        {
            listOfSubprocessesButtons[i].SetActive(true);
            file = listOfSButtonTexts[i].GetComponent<TMPro.TextMeshProUGUI>();
            string temporarySubp = (string)listOfSubprocesses[i];
            string[] line = temporarySubp.Split(' ');
            if(!(line[0].Equals("END")))
            {
                if (line[0].Equals("GIV"))
                {
                    file.text = "Give " + line[1] + " to " + line[2];
                }
                else
                    file.text = "Receive " + line[1] + " from " + line[2];
            }
            else
            {
                file.text = "END";
            }
            file.text = file.text.Replace("-", " ");
        }
    }

    public void Switch(int upIsOne)
    {
        ArrayList listOfSubprocesses = mainScript.GetListOfSubprocesses();
        object subprocess1 = listOfSubprocesses[selectedSubprocess];
        if(upIsOne == 1)
        {
            object subprocess2 = listOfSubprocesses[selectedSubprocess - 1];
            listOfSubprocesses[selectedSubprocess - 1] = subprocess1;
            listOfSubprocesses[selectedSubprocess] = subprocess2;
            if(selectedSubprocess > 0)
            {
                selectedSubprocess--;
            }
            mainScript.SetListOfSubprocesses(listOfSubprocesses);
        }
        else
        {
            object subprocess2 = listOfSubprocesses[selectedSubprocess + 1];
            listOfSubprocesses[selectedSubprocess + 1] = subprocess1;
            listOfSubprocesses[selectedSubprocess] = subprocess2;
            if (selectedSubprocess < listOfSubprocesses.Count)
            {
                selectedSubprocess++;
            }
            mainScript.SetListOfSubprocesses(listOfSubprocesses);
        }
        ResetScrollPanel();
        InitializeScrollPanel();
    }

    public void DeleteProcess()
    {
        ArrayList listOfSubprocesses = mainScript.GetListOfSubprocesses();
        if(listOfSubprocesses.Count != 0)
        {
            listOfSubprocesses.RemoveAt(selectedSubprocess);
            mainScript.SetListOfSubprocesses(listOfSubprocesses);
            ResetScrollPanel();
            InitializeScrollPanel();
        }
    }

    public void AddSubprocess()
    {
        ArrayList listOfSubprocesses = mainScript.GetListOfSubprocesses();
        string action = ddAction.options[ddAction.value].text;
        string item = ddItem.options[ddItem.value].text;
        string person = ddPersonnel.options[ddPersonnel.value].text;
        string toWrite = "";
        if (!(action.Equals("END")))
        {
            if(action.Equals("GIVE"))
            {
                toWrite = "GIV " + item + " " + person;
            }
            else
            {
                toWrite = "REC " + item + " " + person;
            }
        }
        else
        {
            toWrite = "END";
        }
        
        listOfSubprocesses.Add(toWrite);
        mainScript.SetListOfSubprocesses(listOfSubprocesses);
        ResetScrollPanel();
        InitializeScrollPanel();
        //Array.Clear(listOfSubprocessesButtons, 0, listOfSubprocessesButtons.Length);
        //Array.Clear(listOfSButtonTexts, 0, listOfSButtonTexts.Length);
    }
}
