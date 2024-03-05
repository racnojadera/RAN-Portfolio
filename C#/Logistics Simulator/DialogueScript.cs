using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;

public class DialogueScript : MonoBehaviour
{
    //for dialogue
    public GameObject inventoryCanvas, miscCanvas, dialogueCanvas, dialoguePromptNPCNameObject, dialogueDialogueTextObject;
    TextMeshProUGUI dialoguePromptNPCNameTMPro, dialogueDialogueTextTMPro;

    // Start is called before the first frame update
    void Start()
    {
        inventoryCanvas.SetActive(true);
        dialogueCanvas.SetActive(false);
        dialoguePromptNPCNameTMPro = dialoguePromptNPCNameObject.GetComponent<TMPro.TextMeshProUGUI>();
        dialogueDialogueTextTMPro = dialogueDialogueTextObject.GetComponent<TMPro.TextMeshProUGUI>();
    }

    // Update is called once per frame
    public void SetDialogueNPCName(string newName)
    {
        dialoguePromptNPCNameTMPro.text = newName;
        //Debug.Log(dialoguePromptNPCNameTMPro.text);
    }

    public void SetDialogueParagraph(string newText)
    {
        dialogueDialogueTextTMPro.text = newText;
    }

    public void SetInteractingMode(bool isTalking)
    {
        if(isTalking)
        {
            inventoryCanvas.SetActive(false);
            miscCanvas.SetActive(false);
            dialogueCanvas.SetActive(true);
        }
        else
        {
            dialogueCanvas.SetActive(false);
            inventoryCanvas.SetActive(true);
            miscCanvas.SetActive(true);
        }
    }
}
