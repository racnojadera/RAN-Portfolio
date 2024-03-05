using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spinny : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.Rotate(0,10,0);
        //transform.rotation = new Quaternion(transform.rotation.x,transform.rotation.y+0.2f,transform.rotation.z,0);
        //transform.rotation.y = transform.rotation.y+new Vector3(0,1f,0);
    }
}
