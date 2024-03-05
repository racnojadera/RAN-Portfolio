using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public Rigidbody bulletBody;
    ParticleSystem exp;
    // Start is called before the first frame update
    void Start()
    {
        exp = GetComponent<ParticleSystem>();
        exp.Pause();
        if (gameObject.name == "Bullet(Clone)" )
        {
            Destroy(gameObject,2);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "Wall")
        {
            Explode();
        }

        if (collision.gameObject.tag == "Border")
        {
            Destroy(bulletBody);
            Destroy(gameObject, 0);
        }
        if (collision.gameObject.name == "Terrain")
        {
            Explode();
        }
        /*
        if (collision.gameObject.name == "EnemyCapsule")
        {
            Explode();;
        }

        if (collision.gameObject.name == "BigCapsule")
        {
            Explode();;
        }
        */
        if (collision.gameObject.tag == "Enemy")
        {
            Explode();
        }
        
    }
    void Explode() {
        exp.Play();
        Destroy(bulletBody);
        Destroy(gameObject, exp.main.duration);
    }
}


