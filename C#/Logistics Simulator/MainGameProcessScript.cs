using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEngine.SceneManagement;


public class MainGameProcessScript : MonoBehaviour
{
    private object chosenProcess;
    ArrayList instructions = new ArrayList();
    GameObject[] listOfNPCs;

    int currentPlayerCount = 0;

    bool playerIsDone;

    float timerCounter = 7;
    public GameObject instructionLabel;
    // Start is called before the first frame update
    void Start()
    {
        chosenProcess = SelectionMenuScript.chosenProcess;
        FileInfo process = (FileInfo)chosenProcess;
        foreach (string line in File.ReadLines(process.FullName))
        {
            instructions.Add(line);
        }
        listOfNPCs = GameObject.FindGameObjectsWithTag("NPC");
        SetNPCNames();
        SetNPCVisibility();
        SetNPCLocations();
        WriteInstructions(currentPlayerCount);
    }

    void SetNPCVisibility()
    {
        NPCScript temp;
        for (int i = 0; i < listOfNPCs.Length; i++)
        {
            temp = listOfNPCs[i].GetComponent<NPCScript>();
            if (temp.GetName().Equals("npcname"))
            {
                listOfNPCs[i].SetActive(false);
            }
        }
    }

    void SetNPCLocations()
    {
        NPCScript temp;
        DirectoryInfo personnelPath = new DirectoryInfo(Application.dataPath + "/StreamingAssets/database/personnel");
        FileInfo process = (FileInfo)chosenProcess;
        foreach (string line in File.ReadLines(process.FullName))
        {
            string[] choppedLine = line.Split(' ');
            if(!choppedLine[0].Equals("END"))
            {
                ArrayList personnelDetails = new ArrayList();
                FileInfo[] personnelData = personnelPath.GetFiles(choppedLine[2] + ".txt");
                foreach(FileInfo line2 in personnelData)
                {
                    FileInfo fileInfoTemp = line2;
                    foreach(string line3 in File.ReadLines(fileInfoTemp.FullName))
                    {
                        personnelDetails.Add(line3);
                    }
                }
                for(int i = 0; i < listOfNPCs.Length; i++)
                {
                    temp = listOfNPCs[i].GetComponent<NPCScript>();
                    if(temp.GetName().Equals(choppedLine[2]))
                    {
                        temp.SetCoordinate(0, float.Parse((string)personnelDetails[1]));
                        temp.SetCoordinate(1, float.Parse((string)personnelDetails[2]));
                        temp.SetCoordinate(2, float.Parse((string)personnelDetails[3]));
                        temp.SetOnsite(int.Parse((string)personnelDetails[4]));
                    }
                    else
                    {
                        temp.OtherNPCReferenceList(choppedLine[2].ToString(), personnelDetails[0].ToString(), personnelDetails[4].ToString());
                    }
                }
            }
        }
    }

    void SetNPCNames()
    {
        NPCScript temp;
        ArrayList NPCNames = new ArrayList();
        string temporaryInst;
        for(int i = 0; i < instructions.Count; i++)
        {
            temporaryInst = (string)instructions[i];
            string[] line = temporaryInst.Split(' ');
            if(!(line[0].Equals("END")))
            {
                if(!NPCNames.Contains(line[2]))
                {
                    NPCNames.Add(line[2]);
                }
            }
        }
        for(int i = 0; i < NPCNames.Count; i++)
        {
            temp = listOfNPCs[i].GetComponent<NPCScript>();
            temp.SetName((string)NPCNames[i]);
        }

        for(int i = 0; i < listOfNPCs.Length; i++)
        {
            temp = listOfNPCs[i].GetComponent<NPCScript>();
            for(int j = 0; j < instructions.Count; j++)
            {
                temporaryInst = (string)instructions[j];
                string[] line = temporaryInst.Split(' ');
                if(!(line[0].Equals("END")))
                {
                    if(line[2].Equals(temp.GetName()))
                    {
                        temp.AddInstructions(j, line[0], line[1]);
                    }
                    else
                    {
                        temp.AddOtherNPCInstructions(j, line[0], line[1], line[2]);
                    }
                }
            }
        }
    }

    void WriteInstructions(int subproc)
    {
        string temporaryInst = (string)instructions[subproc];
        string inputtedLabel = "";
        string[] line = temporaryInst.Split(' ');

        if(!(line[0].Equals("END")))
        {
            if(line[0].Equals("GIV"))
            {
                inputtedLabel = "Give " + line[1] + " to " + line[2].Replace('-', ' ');
            }
            else
            {
                inputtedLabel = "Receive " + line[1] + " from " + line[2].Replace('-', ' ');
            }
            instructionLabel.GetComponent<TMPro.TextMeshProUGUI>().text = inputtedLabel;
        }
        else
        {
            instructionLabel.GetComponent<TMPro.TextMeshProUGUI>().text = "Done!";
            playerIsDone = true;
        }
    }

    public void AdjustProgress()
    {
        NPCScript temp;
        currentPlayerCount++;
        for (int i = 0; i < listOfNPCs.Length; i++)
        {
            temp = listOfNPCs[i].GetComponent<NPCScript>();
            temp.AdjustCurrentPlayerProcess();
            WriteInstructions(currentPlayerCount);
        }
    }


    // Update is called once per frame
    void Update()
    {
        if(playerIsDone)
        {
            if(timerCounter > 0)
            {
                timerCounter -= Time.deltaTime;
            }
            else
            {
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
            }
        }
    }
}
