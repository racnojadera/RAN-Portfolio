using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPCIndicator : MonoBehaviour
{
    Camera cameraToLookAt;

    // Start is called before the first frame update
    void Start()
    {
        cameraToLookAt = Camera.main;
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(cameraToLookAt.transform);
        transform.rotation = Quaternion.LookRotation(cameraToLookAt.transform.forward);
    }
}
