using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using TMPro;

public class ModifyPersonnelScript : MonoBehaviour
{
    int onlineOnsite = 0;
    string locationFieldText, xCoordinateFieldText, yCoordinateFieldText, zCoordinateFieldText;
    public GameObject modifyPersonNameField, modifyPersonnelLocationField, modifyPersonnelXCoordField, modifyPersonnelYCoordField, modifyPersonnelZCoordField;

    public ReadWriteFilesScript mainScript;

    void Start()
    {
        ExistingDataToInputField();
    }

    public void ExistingDataToInputField()
    {
        ArrayList personnelData = mainScript.GetPersonnelData();

        modifyPersonNameField.GetComponent<InputField>().text = mainScript.GetNameOfPersonnel().ToString();
        if (personnelData.Count > 0)
        {
            modifyPersonnelLocationField.GetComponent<InputField>().text = personnelData[0].ToString();
            modifyPersonnelXCoordField.GetComponent<InputField>().text = personnelData[1].ToString();
            modifyPersonnelYCoordField.GetComponent<InputField>().text = personnelData[2].ToString();
            modifyPersonnelZCoordField.GetComponent<InputField>().text = personnelData[3].ToString();
        }
        else
        {
            modifyPersonnelLocationField.GetComponent<InputField>().text = "";
            modifyPersonnelXCoordField.GetComponent<InputField>().text = "";
            modifyPersonnelYCoordField.GetComponent<InputField>().text = "";
            modifyPersonnelZCoordField.GetComponent<InputField>().text = "";
        }
    }

    public void ChangeInteractionType(int newValue)
    {
        //0 if online
        //1 if onsite
        onlineOnsite = newValue;
    }

    public void SetLocation()
    {
        ArrayList listOfData = new ArrayList();
        locationFieldText = modifyPersonnelLocationField.GetComponent<InputField>().text;
        xCoordinateFieldText = modifyPersonnelXCoordField.GetComponent<InputField>().text;
        yCoordinateFieldText = modifyPersonnelYCoordField.GetComponent<InputField>().text;
        zCoordinateFieldText = modifyPersonnelZCoordField.GetComponent<InputField>().text;
        listOfData.Add(locationFieldText);
        listOfData.Add(xCoordinateFieldText);
        listOfData.Add(yCoordinateFieldText);
        listOfData.Add(zCoordinateFieldText);
        listOfData.Add(onlineOnsite.ToString());
        mainScript.SetPersonnelData(listOfData);
    }

    void ClearInputFields()
    {
        modifyPersonNameField.GetComponent<InputField>().text = "Input Person Name Here...";
        modifyPersonnelLocationField.GetComponent<InputField>().text = "Input Person Location Here...";
        modifyPersonnelXCoordField.GetComponent<InputField>().text = "X Coordinate";
        modifyPersonnelYCoordField.GetComponent<InputField>().text = "Y Coordinate";
        modifyPersonnelZCoordField.GetComponent<InputField>().text = "Z Coordinate";
    }
}
