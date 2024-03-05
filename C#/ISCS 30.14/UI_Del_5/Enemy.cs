using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    MeshRenderer enemyBody;
    int enemyHealth = 8;
    ParticleSystem exp;
    public Transform player;

    // Start is called before the first frame update
    void Start()
    {
        exp = GetComponent<ParticleSystem>();
        enemyBody = GetComponent<MeshRenderer>();
        exp.Pause();
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(player);
        transform.position = Vector3.MoveTowards(transform.position,player.position,0.02f);
        if (name=="BigCapsule") transform.position = new Vector3(transform.position.x,3.3f,transform.position.z);
    }
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "Bullet(Clone)")
        {
            enemyHealth -=1;
        }
        
        if (enemyHealth <= 0 || collision.gameObject.name == "Capsule")
        {
            Explode();
        }
    }

    void Explode() {
        for (int i=transform.childCount-1; i>=0; i--) {
            Destroy(transform.GetChild(i).gameObject);
        }
        exp.Play();
        Destroy(enemyBody);
        Destroy(gameObject, exp.main.duration);
    }

    
}
