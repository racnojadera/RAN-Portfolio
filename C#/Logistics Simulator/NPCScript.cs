using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;

public class NPCScript : MonoBehaviour
{
    public GameObject interactLabel;
    public Transform playerCheck;
    public float playerDistance = 10f;
    public LayerMask playerMask;
    bool isNearPlayer;

    public InventoryScript SubmitItems;
    public GameObject npcNameObject;
    TextMeshProUGUI npcName;

    bool isOnsite = true;
    public GameObject NPCModel;
    public GameObject HumanModel;
    public GameObject ComputerModel;
    public GameObject DispenserModel;
    Transform NPCModelPosition;

    public MainGameProcessScript mainScript;

    //public AudioSource soundClick;
    public AudioSource soundClick1, soundClick2;
    bool soundClickIsDone;

    ArrayList setOfInstructions = new ArrayList();
    ArrayList setOfOtherNPCInstructions = new ArrayList();
    int currentPlayerProcess = 0;
    int nextTaskFromNPC = 0;

    float xCoordinate, yCoordinate, zCoordinate;

    public DialogueScript playerDialogue;
    //0 if not
    //1 if yes
    //2 if just finished
    public int inDialogue;
    ArrayList listOfDialogues = new ArrayList();
    int dialogueIterator;

    ArrayList listOfOtherNPCs = new ArrayList();
    ArrayList listOfOtherNPCLocations = new ArrayList();
    ArrayList listOfOtherNPCOnlineStatus = new ArrayList();

    string placeholder;
    string action;
    string item;


    void Awake()
    {
        npcName = npcNameObject.GetComponent<TMPro.TextMeshProUGUI>();
        NPCModelPosition = NPCModel.GetComponent<Transform>();
        soundClickIsDone = false;
    }

    void Start()
    {
        interactLabel.SetActive(false);
        xCoordinate = 0;
        yCoordinate = 0;
        zCoordinate = 0;
        inDialogue = 0;
    }

    // Update is called once per frame
    /*void Update()
    {
        isNearPlayer = Physics.CheckSphere(playerCheck.position, playerDistance, playerMask);
        string tempStr;
        string[] inst;
        if(setOfInstructions.Count > 0)
        {
            tempStr = (string)setOfInstructions[0];
            inst = tempStr.Split(' ');
            nextTaskFromNPC = Int32.Parse(inst[0]);
        }


        if (isNearPlayer && nextTaskFromNPC == currentPlayerProcess)
        {
            tempStr = (string)setOfInstructions[0];
            inst = tempStr.Split(' ');
            interactLabel.SetActive(true);
            string action = inst[1];
            string item = inst[2];
            if (Input.GetKeyDown(KeyCode.F) && action.Equals("GIV") && SubmitItems.RetrieveItemName().Equals(item))
            {
                setOfInstructions.RemoveAt(0);
                mainScript.AdjustProgress();
                SubmitItems.RemoveItem();

                if(setOfInstructions.Count > 0)
                {
                    tempStr = (string)setOfInstructions[0];
                    inst = tempStr.Split(' ');
                }
                if(inst[1].Equals("REC"))
                {
                    setOfInstructions.RemoveAt(0);
                    mainScript.AdjustProgress();
                    SubmitItems.GetItem(inst[2]);
                }
            }
            else if (Input.GetKeyDown(KeyCode.F) && action.Equals("REC"))
            {
                setOfInstructions.RemoveAt(0);
                mainScript.AdjustProgress();
                SubmitItems.GetItem(inst[2]);
            }
            playerDialogue.SetDialogueNPCName(npcName.text);
        }
        else
        {
            interactLabel.SetActive(false);
        }
    }*/

    void Update()
    {
        //Debug.Log("Current Player Process: " + currentPlayerProcess);
        //Debug.Log("Next Task from NPC: " + nextTaskFromNPC);

        isNearPlayer = Physics.CheckSphere(playerCheck.position, playerDistance, playerMask);
        string tempStr;
        string[] inst;
        if (setOfInstructions.Count > 0)
        {
            tempStr = (string)setOfInstructions[0];
            inst = tempStr.Split(' ');
            nextTaskFromNPC = Int32.Parse(inst[0]);
        }

        if (isNearPlayer)
        {
            if (inDialogue == 0)
            {
                placeholder = "HELLO";
                inst = placeholder.Split(' ');
                action = " ";
                item = " ";

                if (setOfInstructions.Count > 0)
                {
                    tempStr = (string)setOfInstructions[0];
                    inst = tempStr.Split(' ');
                    interactLabel.SetActive(true);
                    action = inst[1];
                    item = inst[2];
                }

                if (nextTaskFromNPC == currentPlayerProcess)
                {
                    interactLabel.GetComponent<TMPro.TextMeshProUGUI>().color = new Color(229, 225, 0, 255);
                    if (Input.GetKeyDown(KeyCode.F))
                    {
                        if (action.Equals("GIV") && SubmitItems.RetrieveItemName().Equals(item))
                        {
                            SetDialogues(0);
                            setOfInstructions.RemoveAt(0);
                            mainScript.AdjustProgress();
                            SubmitItems.RemoveItem();

                            if (setOfInstructions.Count > 0)
                            {
                                tempStr = (string)setOfInstructions[0];
                                inst = tempStr.Split(' ');
                            }
                            if (inst[1].Equals("REC"))
                            {
                                setOfInstructions.RemoveAt(0);
                                mainScript.AdjustProgress();
                                SubmitItems.GetItem(inst[2]);
                            }
                            inDialogue = 1;
                            playerDialogue.SetInteractingMode(true);
                            
                            /*listOfDialogues.Add("A");
                            listOfDialogues.Add("B");
                            listOfDialogues.Add("C");
                            listOfDialogues.Add("D");
                            listOfDialogues.Add("E");*/
                            dialogueIterator = 1;
                        }
                        else if(action.Equals("GIV") && !SubmitItems.RetrieveItemName().Equals(item))
                        {
                            inDialogue = 1;
                            playerDialogue.SetInteractingMode(true);
                            SetDialogues(1);
                            //listOfDialogues.Add("K");
                            //listOfDialogues.Add("L");
                            //listOfDialogues.Add("M");
                            //listOfDialogues.Add("N");
                            //listOfDialogues.Add("O");
                            dialogueIterator = 1;
                            //playerDialogue.SetDialogueNPCName(npcName.text);
                            //playerDialogue.SetDialogueParagraph(listOfDialogues[0].ToString());
                        }
                        else if (action.Equals("REC"))
                        {
                            if(npcName.text.Equals("CFMO-LongForm-Dispenser") || npcName.text.Equals("CFMO-ShortForm-Dispenser"))
                            {
                                SetDialogues(4);
                            }
                            else
                            {
                                SetDialogues(0);
                            }
                            setOfInstructions.RemoveAt(0);
                            mainScript.AdjustProgress();
                            SubmitItems.GetItem(inst[2]);
                            inDialogue = 1;
                            playerDialogue.SetInteractingMode(true);
                            /*listOfDialogues.Add("F");
                            listOfDialogues.Add("G");
                            listOfDialogues.Add("H");
                            listOfDialogues.Add("I");
                            listOfDialogues.Add("J");*/
                            dialogueIterator = 1;
                        }

                        if(!soundClickIsDone)
                        {
                            soundClick1.Play();
                            soundClickIsDone = !soundClickIsDone;
                        }
                        else
                        {
                            soundClick2.Play();
                            soundClickIsDone = !soundClickIsDone;
                        }

                        if(npcName.text.Equals("CFMO-LongForm-Dispenser") || npcName.text.Equals("CFMO-ShortForm-Dispenser"))
                        {
                                playerDialogue.SetDialogueNPCName("Player");
                        }
                        else
                        {
                                playerDialogue.SetDialogueNPCName(npcName.text);
                        }

                        playerDialogue.SetDialogueParagraph(listOfDialogues[0].ToString());
                    }
                }
                else
                {
                    interactLabel.GetComponent<TMPro.TextMeshProUGUI>().color = new Color(0, 173, 255, 255);
                    if (Input.GetKeyDown(KeyCode.F))
                    {
                        if(!soundClickIsDone)
                        {
                            soundClick1.Play();
                            soundClickIsDone = !soundClickIsDone;
                        }
                        else
                        {
                            soundClick2.Play();
                            soundClickIsDone = !soundClickIsDone;
                        }

                        inDialogue = 1;
                        playerDialogue.SetInteractingMode(true);
                        if(npcName.text.Equals("CFMO-LongForm-Dispenser") || (npcName.text.Equals("CFMO-ShortForm-Dispenser")))
                        {
                            SetDialogues(5);
                        }
                        else
                        {
                            SetDialogues(2);
                        }
                        //listOfDialogues.Add("K");
                        //listOfDialogues.Add("L");
                        //listOfDialogues.Add("M");
                        //listOfDialogues.Add("N");
                        //listOfDialogues.Add("O");
                        dialogueIterator = 1;
                        
                        if(npcName.text.Equals("CFMO-LongForm-Dispenser") || npcName.text.Equals("CFMO-ShortForm-Dispenser"))
                        {
                                playerDialogue.SetDialogueNPCName("Player");
                        }
                        else
                        {
                                playerDialogue.SetDialogueNPCName(npcName.text);
                        }
                        
                        playerDialogue.SetDialogueParagraph(listOfDialogues[0].ToString());
                    }
                }
            }
            else if (inDialogue == 1)
            {
                if (Input.GetKeyDown(KeyCode.F) && dialogueIterator < listOfDialogues.Count)
                {
                    if(!soundClickIsDone)
                    {
                        soundClick1.Play();
                        soundClickIsDone = !soundClickIsDone;
                    }
                    else
                    {
                        soundClick2.Play();
                        soundClickIsDone = !soundClickIsDone;
                    }

                    playerDialogue.SetDialogueParagraph(listOfDialogues[dialogueIterator].ToString());
                    dialogueIterator++;
                }
                else if (Input.GetKeyDown(KeyCode.F) && dialogueIterator == listOfDialogues.Count)
                {
                    if(!soundClickIsDone)
                    {
                        soundClick1.Play();
                        soundClickIsDone = !soundClickIsDone;
                    }
                    else
                    {
                        soundClick2.Play();
                        soundClickIsDone = !soundClickIsDone;
                    }

                    listOfDialogues.Clear();
                    inDialogue = 2;
                    playerDialogue.SetInteractingMode(false);
                    interactLabel.GetComponent<TMPro.TextMeshProUGUI>().color = new Color(0, 173, 255, 255);
                }
            }
        }
        else
        {
            interactLabel.SetActive(false);
            inDialogue = 0;
            dialogueIterator = 1;
        }
    }


        /*else if(isNearPlayer && inDialogue == 1)
        {
            Debug.Log("Iterator count: " + dialogueIterator.ToString());
            Debug.Log("Dialogue Count: " + listOfDialogues.Count);
            if (Input.GetKeyDown(KeyCode.F) && dialogueIterator < listOfDialogues.Count)
            {
                playerDialogue.SetDialogueParagraph(listOfDialogues[dialogueIterator].ToString());
                dialogueIterator++;
            }
            else if (Input.GetKeyDown(KeyCode.F) && dialogueIterator == listOfDialogues.Count)
            {
                listOfDialogues.Clear();
                inDialogue = 2;
                playerDialogue.SetInteractingMode(false);
            }
            //REVISE
            /*if(inDialogue == 1)
            {
                Debug.Log("Iterator count: " + dialogueIterator.ToString());
                Debug.Log("Dialogue Count: " + listOfDialogues.Count);
                if(Input.GetKeyDown(KeyCode.F) && dialogueIterator < listOfDialogues.Count)
                {
                    playerDialogue.SetDialogueParagraph(listOfDialogues[dialogueIterator].ToString());
                    dialogueIterator++;
                }
                else if(Input.GetKeyDown(KeyCode.F) && dialogueIterator == listOfDialogues.Count)
                {
                    listOfDialogues.Clear();
                    inDialogue = 2;
                    playerDialogue.SetInteractingMode(false);
                }
            }
            
            if(!isNearPlayer)
            {
                //listOfDialogues.Clear();
                //playerDialogue.SetInteractingMode(false);
                inDialogue = 0;
                dialogueIterator = 1;
            }
        }
        else
        {
            //inDialogue = 0;
           //dialogueIterator = 1;
        }
        

        /*
        if (isNearPlayer && nextTaskFromNPC == currentPlayerProcess)
        {
            tempStr = (string)setOfInstructions[0];
            inst = tempStr.Split(' ');
            interactLabel.SetActive(true);
            string action = inst[1];
            string item = inst[2];
            if (Input.GetKeyDown(KeyCode.F) && action.Equals("GIV") && SubmitItems.RetrieveItemName().Equals(item))
            {
                setOfInstructions.RemoveAt(0);
                mainScript.AdjustProgress();
                SubmitItems.RemoveItem();

                if (setOfInstructions.Count > 0)
                {
                    tempStr = (string)setOfInstructions[0];
                    inst = tempStr.Split(' ');
                }
                if (inst[1].Equals("REC"))
                {
                    setOfInstructions.RemoveAt(0);
                    mainScript.AdjustProgress();
                    SubmitItems.GetItem(inst[2]);
                }
            }
            else if (Input.GetKeyDown(KeyCode.F) && action.Equals("REC"))
            {
                setOfInstructions.RemoveAt(0);
                mainScript.AdjustProgress();
                SubmitItems.GetItem(inst[2]);
            }
            playerDialogue.SetDialogueNPCName(npcName.text);
        }
        else
        {
            interactLabel.SetActive(false);
        }
    }*/


    public void SetName(string name)
    {
        npcName.text = name;
    }

    public string GetName()
    {
        return npcName.text;
    }

    public void SetOnsite(int value)
    {
        if(value == 1)
        {
            isOnsite = true;
        }
        else
        {
            isOnsite = false;
        }

        string tempName = npcName.text;
        if(!tempName.Contains("Dispenser"))
        {
            DispenserModel.SetActive(false);
            if(isOnsite)
            {
                HumanModel.SetActive(true);
                ComputerModel.SetActive(false);
            }
            else
            {
                string newName = "(Online) " + npcName.text;
                npcName.text = newName;
                HumanModel.SetActive(false);
                ComputerModel.SetActive(true);
            }
        }
        else
        {
            HumanModel.SetActive(false);
            ComputerModel.SetActive(false);
            DispenserModel.SetActive(true);
        }
    }


    public void SetCoordinate(int xyz, float value)
    {
        switch(xyz)
        {
            case 0:
                xCoordinate = value;
                break;
            case 1:
                yCoordinate = value;
                break;
            case 2:
                zCoordinate = value;
                break;
        }
        NPCModelPosition.Translate(xCoordinate-NPCModelPosition.position.x, yCoordinate-NPCModelPosition.position.y, zCoordinate-NPCModelPosition.position.z);
    }

    string GetCurrentTask(int currentProcess)
    {
        for(int i = 0; i < setOfOtherNPCInstructions.Count; i++)
        {
            string tempString = setOfOtherNPCInstructions[i].ToString();
            string[] tempCurrentTask = tempString.Split(' ');
            if(int.Parse(tempCurrentTask[0]) == currentProcess)
            {
                return setOfOtherNPCInstructions[i].ToString();
            }
        }
        for(int i = 0; i < setOfInstructions.Count; i++)
        {
            string tempString = setOfInstructions[i].ToString();
            string[] tempCurrentTask = tempString.Split(' ');
            if (int.Parse(tempCurrentTask[0]) == currentProcess)
            {
                return setOfInstructions[i].ToString();
            }
        }
        return "";
        //return setOfOtherNPCInstructions[currentPlayerProcess].ToString();
    }

    void SetDialogues(int interactionType)
    {
        //0 is correct npc, correct item
        //1 is correct npc, wrong item
        //2 is wrong npc
        //3 correct npc gives back an item
        //4 is dispenser
        if(interactionType < 4)
        {
            listOfDialogues.Add("Hello!");
        }
        switch(interactionType)
        {
            case 0:
                //correctNPC, correct item
                string tempString2 = GetCurrentTask(currentPlayerProcess);
                string[] tempCurrentTask2 = tempString2.Split(' ');
                if (tempCurrentTask2[1] == "GIV")
                {
                    listOfDialogues.Add("Thank you for giving me the " + SubmitItems.RetrieveItemName() + ".");
                }
                else
                {
                    listOfDialogues.Add("Please receive this " + item);
                }
                listOfDialogues.Add("You can now proceed to your next task. Good luck!");             
                break;
            case 1:
                //correctNPC, wrong item
                listOfDialogues.Add("Sadly, I am unable to process your request");
                if(SubmitItems.RetrieveItemName().Equals(""))
                {
                    listOfDialogues.Add("To proceed to the next task, I am asking for the item " + item);
                }
                else
                {
                    listOfDialogues.Add("To proceed to the next task, I am asking for the item " + item + ", not " + SubmitItems.RetrieveItemName());
                }
                listOfDialogues.Add("Please come back after you have selected the item in your inventory. Thank you!");
                break;
            case 2:
                //wrong npc
                //string tempString = GetCurrentTask();
                //string[] tempCurrentTask = tempString.Split(' ');
                string tempString = GetCurrentTask(currentPlayerProcess);
                string[] tempCurrentTask = tempString.Split(' ');
                if(tempCurrentTask[1] == "GIV")
                {
                    listOfDialogues.Add("Please go to " + tempCurrentTask[3].ToString() + " and give the " + tempCurrentTask[2] + " to continue.");
                }
                else
                {
                    listOfDialogues.Add("Please go to " + tempCurrentTask[3].ToString() + " and receive the " + tempCurrentTask[2] + " to continue.");
                }

                int indexOfNPCRef = listOfOtherNPCs.IndexOf(tempCurrentTask[3].ToString());
                listOfDialogues.Add("They should be located at " + listOfOtherNPCLocations[indexOfNPCRef] + " around this time.");

                if(int.Parse((string)listOfOtherNPCOnlineStatus[indexOfNPCRef]) == 0)
                {
                    listOfDialogues.Add("You can also interact with them online. You can go to Faura and use one of the laptops there to proceed.");
                }

                listOfDialogues.Add("Good luck!");
                break;
            case 4:
                listOfDialogues.Add("(You get a " + item + " from the table.)");
                break;
            case 5:
                tempString = GetCurrentTask(currentPlayerProcess);
                tempCurrentTask = tempString.Split(' ');
                if(tempCurrentTask[1] == "GIV")
                {
                    listOfDialogues.Add("(I should probably go to " + tempCurrentTask[3].ToString() + " and give the " + tempCurrentTask[2] + " to continue.)");
                }
                else
                {
                    listOfDialogues.Add("(I should probably go to " + tempCurrentTask[3].ToString() + " and receive the " + tempCurrentTask[2] + " to continue.)");
                }
                break;
            
        }
    }

    public void AddInstructions(int ord, string act, string item)
    {
        setOfInstructions.Add(ord.ToString() + " " + act + " " + item);
    }

    public string GetInstructions(int i)
    {
        return (string)setOfInstructions[i];
    }

    public void AddOtherNPCInstructions(int ord, string act, string item, string otherNPCName)
    {
        setOfOtherNPCInstructions.Add(ord.ToString() + " " + act + " " + item + " " + otherNPCName);
    }

    public void OtherNPCReferenceList(string npcname, string npclocation, string isOnline)
    {
        listOfOtherNPCs.Add(npcname);
        listOfOtherNPCLocations.Add(npclocation);
        listOfOtherNPCOnlineStatus.Add(isOnline);
    }

    public void AdjustCurrentPlayerProcess()
    {
        currentPlayerProcess++;
    }
}
