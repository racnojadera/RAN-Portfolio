using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// https://answers.unity.com/questions/48482/camera-following-an-object.html
public class CenterCamera : MonoBehaviour
{
    public GameObject player;
    // public float smooth = 5;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = player.transform.position - new Vector3(0,0,10);
        //transform.position.x = Mathf.Lerp(transform.position.x,player.transform.position.x,Time.deltaTime*smooth);
        //transform.position.y = Mathf.Lerp(transform.position.y,player.transform.position.y,Time.deltaTime*smooth);
    }
}
