using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Generator : MonoBehaviour
{
    public GameObject enemy;
    public GameObject obstacle;
    public Camera cam;
    public BoxCollider2D boundary;
    
    // Start is called before the first frame update
    void Start()
    {
        SpawnEnemy();
        SpawnObstacles();
        cam = GetComponent<Camera>();
        Vector3 bottomLeft = cam.ViewportToWorldPoint(new Vector3(0,0,0));
        Vector3 topRight = cam.ViewportToWorldPoint(new Vector3(1,1,0));
        boundary = GetComponent<BoxCollider2D>();
        boundary.size = new Vector2(topRight.x-bottomLeft.x, topRight.y-bottomLeft.y);
    }

    // Update is called once per frame
    void Update()
    {

    }

    void SpawnEnemy() {
        Instantiate(enemy,transform.position-new Vector3(3,-18,-10),Quaternion.identity);
        Instantiate(enemy,transform.position-new Vector3(-4,-17,-10),Quaternion.identity);
        Instantiate(enemy,transform.position-new Vector3(2,-21,-10),Quaternion.identity);
        Instantiate(enemy,transform.position-new Vector3(-5,-25,-10),Quaternion.identity);
        Instantiate(enemy,transform.position-new Vector3(-4,-33,-10),Quaternion.identity);
    }

    void SpawnObstacles() {
        Instantiate(obstacle,transform.position-new Vector3(6,-7,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(-6,-9,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(-4,-12,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(6,-17,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(-6,-19,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(-4,-22,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(4,-28,-10),Quaternion.identity);
        Instantiate(obstacle,transform.position-new Vector3(-5,-31,-10),Quaternion.identity);
    }
}
