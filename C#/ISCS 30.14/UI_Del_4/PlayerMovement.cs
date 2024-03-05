using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float speed = 7.5f;
    private Rigidbody2D body;
    public SpriteRenderer charRenderer;
    public GameObject bullet;
    public GameObject mainCamera;
    public Camera cam;
    public Sprite explosion;
    int delay = 0;
    int health;
    float angle;
    public float minX, maxX, minY, maxY;
    public Vector3 bottomLeft, topRight;
    public bool invertedAxis = false;
    // Start is called before the first frame update
    void Start()
    {
        health = 10;
        delay = 0;
        angle = 0;
        body = GetComponent<Rigidbody2D>();
        charRenderer = GetComponent<SpriteRenderer>();
        cam = mainCamera.GetComponent<Camera>();
        bottomLeft = cam.ViewportToWorldPoint(new Vector3(0,0,0));
        topRight = cam.ViewportToWorldPoint(new Vector3(1,1,0));
        minX = bottomLeft.x+0.5f;
        maxX = topRight.x-0.5f;
        minY = bottomLeft.y+0.5f;
        maxY = topRight.y-0.5f;
    }

    // Update is called once per frame
    void Update()
    {
        MovePlayer();

        if (Input.GetKey(KeyCode.Space) && delay>10) {
            Shoot();
        }
        delay++;
        if (health<=0) {
            Die();
        }
    }

    void Shoot()
    {
        delay = 0;
        Instantiate(bullet,transform.position,transform.rotation);
    }

    void OnTriggerEnter2D(Collider2D col) {
        if (col.gameObject.tag == "EnemyBullet") {
            health--;
        }
        if (col.gameObject.tag == "Enemy") {
            health-=2;
        }
    }

    void Die() {
        charRenderer.sprite = explosion;
        Destroy(gameObject,0.2f);
    }

    void MovePlayer()
    {
        if (Input.GetAxisRaw("Vertical") > 0.0f)
        {
            Vector3 temp = transform.position;
            temp.y += speed * Time.deltaTime;
            if (temp.y > maxY) temp.y = maxY;
            transform.position = temp;
        }
        else if (Input.GetAxisRaw("Vertical") < 0.0f)
        {
            Vector3 temp = transform.position;
            temp.y -= speed * Time.deltaTime;
            if (temp.y < minY) temp.y = minY;
            transform.position = temp;
        }
         if (Input.GetAxisRaw("Horizontal") > 0.0f)
        {
            Vector3 temp = transform.position;
            temp.x += speed * Time.deltaTime;
            if (temp.x > maxX) temp.x = maxX;
            transform.position = temp;
        }
        else if (Input.GetAxisRaw("Horizontal") < 0.0f)
        {
            Vector3 temp = transform.position;
            temp.x -= speed * Time.deltaTime;
            if (temp.x < minX) temp.x = minX;
            transform.position = temp;
        }
        if (Input.GetKey(KeyCode.E))
        {
            angle -= 2;
            transform.rotation = Quaternion.Euler(new Vector3(0, 0, angle));
        }
        if (Input.GetKey(KeyCode.Q))
        {
            angle += 2;
            transform.rotation = Quaternion.Euler(new Vector3(0, 0, angle));
        }
    }
}
