using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using TMPro;

public class ReadWriteFilesScript : MonoBehaviour
{
    public ArrayList listOfItems = new ArrayList();
    public ArrayList listOfPersonnel = new ArrayList();
    public ArrayList listOfProcesses = new ArrayList();
    GameObject[] listOfEditButtons, listOfEButtonTexts;

    public GameObject addModifyPanel;
    public GameObject addItem, addPersonnel, addProcess;
    public GameObject modifyItem, modifyPersonnel, modifyProcess;

    public GameObject addItemField, addPersonnelField, addProcessField;
    public GameObject modifyItemField, modifyPersonnelField, modifyProcessField;


    string path;
    int selectedButton, selectedCategory;

    bool initialized = false;

    // Start is called before the first frame update
    void Start()
    {
        initialized = true;
        listOfEditButtons = GameObject.FindGameObjectsWithTag("EditPanelButtons");
        listOfEButtonTexts = GameObject.FindGameObjectsWithTag("EditPanelButtonTexts");
        selectedButton = 0;
        selectedCategory = 0;
        path = Application.dataPath;
        InitializeItemList(path);
        InitializePersonnelList(path);
        InitializeProcessesList(path);

        ResetPanel(0);
    }

    // Update is called once per frame
    void LateUpdate()
    {
        
    }

    void InitializeItemList(string path)
    {
        DirectoryInfo itemPath = new DirectoryInfo(path + "/StreamingAssets/database/items");
        FileInfo[] files = itemPath.GetFiles("*.txt");
        foreach (FileInfo file in files)
        {

            listOfItems.Add(file);
        }
    }

    void InitializePersonnelList(string path)
    {
        DirectoryInfo personnelPath = new DirectoryInfo(path + "/StreamingAssets/database/personnel");
        FileInfo[] personnel = personnelPath.GetFiles("*.txt");
        foreach (FileInfo person in personnel)
        {
            listOfPersonnel.Add(person);
        }
    }

    void InitializeProcessesList(string path)
    {
        DirectoryInfo processesPath = new DirectoryInfo(path + "/StreamingAssets/database/processes");
        FileInfo[] processes = processesPath.GetFiles("*.txt");
        foreach (FileInfo process in processes)
        {
            listOfProcesses.Add(process);
        }
    }

    public void ResetPanel(int categoryType)
    {
        if(initialized)
        {
            //0 is for items
            //1 is for personnel
            //2 is for processes
            //selectedCategory = categoryType;
            for (int i = 0; i < listOfEditButtons.Length; i++)
            {
                listOfEditButtons[i].SetActive(false);
            }

            TextMeshProUGUI file;
            switch (categoryType)
            {
                case 0:
                    for (int i = 0; i < listOfItems.Count; i++)
                    {
                        listOfEditButtons[i].SetActive(true);
                        file = listOfEButtonTexts[i].GetComponent<TMPro.TextMeshProUGUI>();
                        FileInfo fileInfoTemp = (FileInfo)listOfItems[i];
                        string fileName = fileInfoTemp.Name;
                        fileName = fileName.Substring(0, fileName.Length - 4);
                        fileName = fileName.Replace("-", " ");
                        file.text = fileName;
                    }
                    break;
                case 1:
                    for (int i = 0; i < listOfPersonnel.Count; i++)
                    {
                        listOfEditButtons[i].SetActive(true);
                        file = listOfEButtonTexts[i].GetComponent<TMPro.TextMeshProUGUI>();
                        FileInfo fileInfoTemp = (FileInfo)listOfPersonnel[i];
                        string fileName = fileInfoTemp.Name;
                        fileName = fileName.Substring(0, fileName.Length - 4);
                        fileName = fileName.Replace("-", " ");
                        file.text = fileName;
                    }
                    break;
                case 2:
                    for (int i = 0; i < listOfProcesses.Count; i++)
                    {
                        listOfEditButtons[i].SetActive(true);
                        file = listOfEButtonTexts[i].GetComponent<TMPro.TextMeshProUGUI>();
                        FileInfo fileInfoTemp = (FileInfo)listOfProcesses[i];
                        string fileName = fileInfoTemp.Name;
                        fileName = fileName.Substring(0, fileName.Length - 4);
                        fileName = fileName.Replace("-", " ");
                        file.text = fileName;
                    }
                    break;
            }
        }
        
    }

    public ArrayList GetArray(int identifier)
    {
        //0 is for items
        //1 is for personnel
        //2 is for processes
        switch(identifier)
        {
            case 0:
                return listOfItems;
            case 1:
                return listOfPersonnel;
            case 2:
                return listOfProcesses;
            default:
                return new ArrayList();
        }
    }

    public void SetSelectedArray(int newSelect)
    {
        selectedButton = newSelect;
    }

    public void AddModify()
    {
        addModifyPanel.SetActive(true);
    }

    public void EditAddObject()
    {
        addItem.SetActive(false);
        addPersonnel.SetActive(false);
        addProcess.SetActive(false);
        modifyItem.SetActive(false);
        modifyPersonnel.SetActive(false);
        modifyProcess.SetActive(false);
        switch(selectedCategory)
        {
            case 0:
                addItem.SetActive(true);
                break;
            case 1:
                addPersonnel.SetActive(true);
                break;
            case 2:
                addProcess.SetActive(true);
                break;
        }
    }

    public void EditModifyObject()
    {
        addItem.SetActive(false);
        addPersonnel.SetActive(false);
        addProcess.SetActive(false);
        modifyItem.SetActive(false);
        modifyPersonnel.SetActive(false);
        modifyProcess.SetActive(false);
        switch (selectedCategory)
        {
            case 0:
                modifyItem.SetActive(true);
                break;
            case 1:
                modifyPersonnel.SetActive(true);
                break;
            case 2:
                modifyProcess.SetActive(true);
                break;
        }
    }

    public void AddButton()
    {
        //0 is for items
        //1 is for personnel
        //2 is for processes
        string inputFieldText = "";
        string newPath = "";

        switch (selectedCategory)
        {
            case 0:
                inputFieldText = addItemField.GetComponent<InputField>().text;
                newPath = path + "/StreamingAssets/database/items/" + inputFieldText + ".txt";
                File.WriteAllText(newPath, "");
                listOfItems.Clear();
                InitializeItemList(path);
                selectedCategory = 0;
                break;
            case 1:
                inputFieldText = addPersonnelField.GetComponent<InputField>().text;
                newPath = path + "/StreamingAssets/database/personnel/" + inputFieldText + ".txt";
                File.WriteAllText(newPath, "");
                listOfPersonnel.Clear();
                InitializePersonnelList(path);
                selectedCategory = 1;
                break;
            case 2:
                inputFieldText = addProcessField.GetComponent<InputField>().text;
                newPath = path + "/StreamingAssets/database/processes/" + inputFieldText + ".txt";
                File.WriteAllText(newPath, "");
                listOfProcesses.Clear();
                InitializeProcessesList(path);
                selectedCategory = 2;
                break;
        }
        ResetPanel(selectedCategory);
    }

    public void ModifyButton()
    {
        //0 is for items
        //1 is for personnel
        //2 is for processes
        string inputFieldText = "";
        string newPath = "";

        switch (selectedCategory)
        {
            case 0:
                inputFieldText = modifyItemField.GetComponent<InputField>().text;
                newPath = path + "/StreamingAssets/database/items/" + inputFieldText + ".txt";
                FileInfo fileTemp1 = (FileInfo)listOfItems[selectedButton];
                string sourceFile1 = fileTemp1.FullName;
                FileInfo newFile1 = new FileInfo(sourceFile1);
                if(newFile1.Exists)
                {
                    newFile1.MoveTo(newPath);
                }
                listOfItems.Clear();
                InitializeItemList(path);
                selectedCategory = 0;
                break;
            case 1:
                inputFieldText = modifyPersonnelField.GetComponent<InputField>().text;
                newPath = path + "/StreamingAssets/database/personnel/" + inputFieldText + ".txt";
                FileInfo fileTemp2 = (FileInfo)listOfPersonnel[selectedButton];
                string sourceFile2 = fileTemp2.FullName;
                FileInfo newFile2 = new FileInfo(sourceFile2);
                if(newFile2.Exists)
                {
                    newFile2.MoveTo(newPath);
                }
                listOfPersonnel.Clear();
                InitializePersonnelList(path);
                selectedCategory = 1;
                break;
            case 2:
                break;
        }
        ResetPanel(selectedCategory);
    }

    public void ChangeCategory(int newCategory)
    {
        selectedCategory = newCategory;
    }

    public ArrayList GetListOfPersonnel()
    {
        return listOfPersonnel;
    }

    public ArrayList GetPersonnelData()
    {
        ArrayList personnelData = new ArrayList();
        FileInfo fileInfoTemp = (FileInfo)listOfPersonnel[selectedButton];
        foreach (string line in File.ReadLines(fileInfoTemp.FullName))
        {
            personnelData.Add(line);
        }
        return personnelData;
    }

    public string GetNameOfPersonnel()
    {
        /*
         * listOfEditButtons[i].SetActive(true);
           file = listOfEButtonTexts[i].GetComponent<TMPro.TextMeshProUGUI>();
           FileInfo fileInfoTemp = (FileInfo)listOfItems[i];
           string fileName = fileInfoTemp.Name;
           fileName = fileName.Substring(0, fileName.Length - 4);
           file.text = fileName;
         */
        FileInfo fileInfoTemp = (FileInfo)listOfPersonnel[selectedButton];
        string fileName = fileInfoTemp.Name;
        fileName = fileName.Substring(0, fileName.Length - 4);
        return fileName;
    }

    public void SetPersonnelData(ArrayList newList)
    {
        FileInfo fileInfoTemp = (FileInfo)listOfPersonnel[selectedButton];
        string[] line = (string[])newList.ToArray(typeof(string));
        File.WriteAllLines(fileInfoTemp.FullName, line);
    }

    public ArrayList GetListOfItems()
    {
        return listOfItems;
    }

    public ArrayList GetListOfProcesses()
    {
        return listOfProcesses;
    }

    public ArrayList GetListOfSubprocesses()
    {
        ArrayList subprocesses = new ArrayList();
        FileInfo fileInfoTemp = (FileInfo)listOfProcesses[selectedButton];
        foreach (string line in File.ReadLines(fileInfoTemp.FullName))
        {
            subprocesses.Add(line);
        }
        return subprocesses;
    }

    public void SetListOfSubprocesses(ArrayList newList)
    {
        FileInfo fileInfoTemp = (FileInfo)listOfProcesses[selectedButton];
        string[] line = (string[])newList.ToArray(typeof(string));
        File.WriteAllLines(fileInfoTemp.FullName, line);
    }
}
