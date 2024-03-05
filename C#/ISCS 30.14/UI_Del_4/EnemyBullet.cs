using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBullet : MonoBehaviour
{
    private float speed;
    private float yVel;
    public SpriteRenderer charRenderer;
    public Sprite explosion;
    public GameObject player;
    bool isRoot;

    // Start is called before the first frame update
    void Start()
    {
        if (transform.position.x<-10) isRoot = true;
        if (!isRoot)
        {
            speed = 1;
            yVel = speed*0.1f;
            Vector3 targ = player.transform.position;
            targ.z = 0f;

            Vector3 objectPos = transform.position;
            targ.x = targ.x - objectPos.x;
            targ.y = targ.y - objectPos.y;

            float angle = Mathf.Atan2(targ.y, targ.x) * Mathf.Rad2Deg;
            transform.rotation = Quaternion.Euler(new Vector3(0, 0, angle+90));
        }
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(new Vector3(0,-yVel,0));
    }

    void OnTriggerEnter2D(Collider2D col) {
        if (col.gameObject.tag == "Player") {
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
