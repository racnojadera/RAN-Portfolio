using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBullet : MonoBehaviour
{
    private float speed;
    private float yVel;
    public SpriteRenderer charRenderer;
    public Sprite explosion;
    bool isRoot = false;

    // Start is called before the first frame update
    void Start()
    {
        speed = 1;
        yVel = speed*0.1f;
        if (transform.position.x<-20) isRoot = true;
    }

    // Update is called once per frame
    void Update()
    {
        if (!isRoot) transform.Translate(new Vector3(0,yVel,0));
    }

    void OnTriggerEnter2D(Collider2D col) {
        if (col.gameObject.tag == "Enemy") {
            yVel = 0;
            charRenderer.sprite = explosion;
            Destroy(gameObject,0.2f);
        }
    }

    void OnTriggerExit2D(Collider2D col) {
        if (col.gameObject.tag == "MainCamera") {
            Destroy(gameObject);
        }
    }
}
