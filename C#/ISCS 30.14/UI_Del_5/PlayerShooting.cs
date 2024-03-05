using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerShooting : MonoBehaviour
{
    public GameObject spawnPoint;
    public Rigidbody bullet;

    float speed = 30;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Rigidbody bulletForward;
        if(Input.GetMouseButtonDown(0))
        {
            bulletForward = Instantiate(bullet, spawnPoint.transform.position, spawnPoint.transform.rotation) as Rigidbody;
            bulletForward.velocity = transform.TransformDirection(Vector3.forward * speed);
        }


    }

    
}
