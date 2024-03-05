using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class cursorResetScript : MonoBehaviour
{
    PointerEventData pointerData;
    // Start is called before the first frame update
    void Awake()
    {
        Cursor.visible = true;
    }

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(pointerData.pointerEnter);
    }
}
