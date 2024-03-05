using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    int health;
    int delay;
    private float speed;
    private float yVel;
    public GameObject bullet, player;
    public SpriteRenderer charRenderer;
    public Sprite explosion;
    bool isDead;
    bool isRoot;
    bool isBoxed;

    // Start is called before the first frame update
    void Start()
    {
        health = 5;
        delay = 0;
        speed = 0.15f;
        yVel = speed*0.1f;
        charRenderer = transform.GetChild(0).gameObject.GetComponent<SpriteRenderer>();
        isDead = false;
        if (transform.position.x<-10) isRoot = true;
        isBoxed = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (!isRoot) {
            transform.Translate(new Vector3(0,-yVel,0));
            Vector3 targ = player.transform.position;
            targ.z = 0f;

            Vector3 objectPos = transform.position;
            targ.x = targ.x - objectPos.x;
            targ.y = targ.y - objectPos.y;

            float angle = Mathf.Atan2(targ.y, targ.x) * Mathf.Rad2Deg;
            if (!isDead) transform.GetChild(0).rotation = Quaternion.Euler(new Vector3(0, 0, angle+90));

            if (transform.position.y<-8 && transform.position.x>-10 && transform.position.x<10) Destroy(gameObject);
            if (health<=0) {
                Die();
            }
            delay++;
            if (isBoxed && delay >= 60) Shoot();
        }
    }

    void Shoot()
    {
        delay = 0;
        Instantiate(bullet,transform.position,Quaternion.identity);
    }

    void OnTriggerEnter2D(Collider2D col) {
        if (col.gameObject.tag == "PlayerBullet") {
            health--;
        }
        if (col.gameObject.tag == "Player") {
            Die();
        }
        if (col.gameObject.tag == "MainCamera") {
            isBoxed = true;
        }
    }

    void OnTriggerExit2D(Collider2D col) {
        if (col.gameObject.tag == "MainCamera") {
            isBoxed = false;
            Die();
        }
    }

    void Die() {
        isDead = true;
        charRenderer.sprite = explosion;
        Destroy(gameObject,0.2f);
    }
}
