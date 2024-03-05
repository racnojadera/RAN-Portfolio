using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;

public class InventoryScript : MonoBehaviour
{
    public GameObject inv1, inv2, inv3;
    List<GameObject> listOfInv;
    TextMeshProUGUI invItemCount;
    public GameObject selector1, selector2, selector3, itemTitle;
    public GameObject previewBackdrop, shortFormPicture, longFormPicture;
    int currentItemSelector = 0;

    bool isFormVisible;
    ArrayList actualInventoryCount;
    ArrayList actualInventory;

    void Awake()
    {
        isFormVisible = false;
        shortFormPicture.SetActive(false);
        longFormPicture.SetActive(false);
        previewBackdrop.SetActive(false);
    }
    // Start is called before the first frame update
    void Start()
    {
        actualInventory = new ArrayList();
        actualInventoryCount = new ArrayList();
        for (int i = 0; i < 3; i++)
        {
            actualInventory.Add("");
            actualInventoryCount.Add(0);
        }
        listOfInv = new List<GameObject>();
        listOfInv.Add(inv1);
        listOfInv.Add(inv2);
        listOfInv.Add(inv3);
        for(int i = 0; i < listOfInv.Count; i++)
        {
            invItemCount = listOfInv[i].GetComponent<TMPro.TextMeshProUGUI>();
            invItemCount.text = "";
        }
    }

    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Alpha1) && !isFormVisible)
        {
            currentItemSelector = 0;
            SetInvSelectorVisible(currentItemSelector);
        }
        if(Input.GetKeyDown(KeyCode.Alpha2) && !isFormVisible)
        {
            currentItemSelector = 1;
            SetInvSelectorVisible(currentItemSelector);
        }
        if(Input.GetKeyDown(KeyCode.Alpha3) && !isFormVisible)
        {
            currentItemSelector = 2;
            SetInvSelectorVisible(currentItemSelector);
        }

        if(Input.GetKeyDown(KeyCode.N) && ((string)actualInventory[currentItemSelector]).Contains("Short-Form"))
        {
            isFormVisible = !isFormVisible;
            previewBackdrop.SetActive(false);
        }
        if(Input.GetKeyDown(KeyCode.N) && ((string)actualInventory[currentItemSelector]).Contains("Long-Form"))
        {
            isFormVisible = !isFormVisible;
            previewBackdrop.SetActive(false);
        }

        if(isFormVisible)
        {
            previewBackdrop.SetActive(true);
            if(((string)actualInventory[currentItemSelector]).Contains("Short-Form"))
            {
                shortFormPicture.SetActive(true);
                longFormPicture.SetActive(false);
            }
            else if(((string)actualInventory[currentItemSelector]).Contains("Long-Form"))
            {
                shortFormPicture.SetActive(false);
                longFormPicture.SetActive(true);
            }
        }
        /*if(Input.GetKeyDown(KeyCode.N) && (string)actualInventory[currentItemSelector].Contains("ShortForm"))
        {
            Debug.Log("Opening Short Form");
        }
        if(Input.GetKeyDown(KeyCode.N) && (string)actualInventory[currentItemSelector].Contains("LongForm"))
        {
            Debug.Log("Opening Long Form");
        }*/
    }

    void SetInvSelectorVisible(int currentSelected)
    {
        string temp = (string)actualInventory[currentSelected];
        itemTitle.GetComponent<TMPro.TextMeshProUGUI>().text = temp;
        for(int i = 0; i < actualInventoryCount.Count; i++)
        {
            invItemCount = listOfInv[i].GetComponent<TMPro.TextMeshProUGUI>();
            if ((int)actualInventoryCount[i] != 0)
            {
                invItemCount.text = actualInventoryCount[i].ToString();
            }
            else
            {
                invItemCount.text = "";
            }
        }
        switch (currentSelected)
        {
            case 0:
                selector1.SetActive(true);
                selector2.SetActive(false);
                selector3.SetActive(false);
                break;
            case 1:
                selector1.SetActive(false);
                selector2.SetActive(true);
                selector3.SetActive(false);
                break;
            case 2:
                selector1.SetActive(false);
                selector2.SetActive(false);
                selector3.SetActive(true);
                break;
        }
    }

    public void GetItem(string item)
    {
        if (actualInventory[currentItemSelector].Equals(""))
        {
            actualInventory[currentItemSelector] = item;
            int tempCont = (int)actualInventoryCount[currentItemSelector];
            actualInventoryCount[currentItemSelector] = tempCont + 1;
        }
        else if (((string)actualInventory[currentItemSelector]).Equals(item))
        {
            int tempCont = (int)actualInventoryCount[currentItemSelector];
            actualInventoryCount[currentItemSelector] = tempCont + 1;
        }
        else
        {
            if(currentItemSelector < 3)
            {
                actualInventory[currentItemSelector+1] = item;
                int tempCont = (int)actualInventoryCount[currentItemSelector + 1];
                actualInventoryCount[currentItemSelector + 1] = tempCont + 1;
            }
            else
            {
                actualInventory[0] = item;
                int tempCont = (int)actualInventoryCount[0];
                actualInventoryCount[0] = tempCont + 1;
            }
            
        }
        SetInvSelectorVisible(currentItemSelector);
    }

    public void RemoveItem()
    {
        actualInventory[currentItemSelector] = "";
        int tempCont = (int)actualInventoryCount[currentItemSelector];
        actualInventoryCount[currentItemSelector] = tempCont - 1;
        SetInvSelectorVisible(currentItemSelector);
    }

    public string RetrieveItemName()
    {
        return (string)actualInventory[currentItemSelector];
    }
}
