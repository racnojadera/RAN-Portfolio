using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Obstacle : MonoBehaviour
{
    private int health;
    private float speed;
    private float yVel;
    public SpriteRenderer charRenderer;
    public Sprite explosion;
    bool isRoot;
    // Start is called before the first frame update
    void Start()
    {
        health = 5;
        speed = 0.15f;
        yVel = speed*0.1f;
        charRenderer = transform.GetChild(0).gameObject.GetComponent<SpriteRenderer>();
        if (transform.position.x<-13) isRoot = true;
    }

    // Update is called once per frame
    void Update()
    {
        if (!isRoot) {
            transform.Translate(new Vector3(0,-yVel,0));
            if (transform.position.y<-8 && transform.position.x>-10 && transform.position.x<10) Destroy(gameObject);
            if (health<=0) {
                Die();
            }

        }
    }

    void Die() {
        charRenderer.sprite = explosion;
        Destroy(gameObject,0.2f);
    }

    void OnTriggerEnter2D(Collider2D col) {
        if (col.gameObject.tag == "PlayerBullet") {
            health--;
        }
        if (col.gameObject.tag == "Player") {
            Die();
        }
    }

    void OnTriggerExit2D(Collider2D col) {
        if (col.gameObject.tag == "MainCamera") {
            Die();
        }
    }
}
