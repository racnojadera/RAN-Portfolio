using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RetrieveFormsScript : MonoBehaviour
{
    public GameObject interactLabel;
    public Transform playerCheck;
    public float playerDistance = 10f;
    public LayerMask playerMask;
    public bool isNearPlayer;
    public InventoryScript SubmitItems;

    // Start is called before the first frame update
    void Start()
    {
        interactLabel.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        isNearPlayer = Physics.CheckSphere(playerCheck.position, playerDistance, playerMask);

        if(isNearPlayer)
        {
            interactLabel.SetActive(true);
            if(Input.GetKeyDown(KeyCode.F))
            {
                //SubmitItems.GetItem();
            }
        }
        else
        {
            interactLabel.SetActive(false);
        }
    }
}
