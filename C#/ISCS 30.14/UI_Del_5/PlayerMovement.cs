using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    CharacterController myCharController;
    [SerializeField] private float speed = 7.5f;
    private Vector3 moving;
    public Transform head, gun, cam;
    ParticleSystem exp;

    float xRotation = 0f;

    private void Start()
    {
        exp = GetComponent<ParticleSystem>();
        myCharController = GetComponent<CharacterController>();
        moving = Vector3.zero;
        Cursor.lockState = CursorLockMode.Locked;
        exp.Pause();
    }

    private void Update()
    {
        Movement();
        Rotation();
        RaycastHit hit;
        if (Physics.Raycast(cam.position,cam.TransformDirection(Vector3.forward), out hit)) {
            gun.LookAt(hit.point);
        }
        else {
        }
        transform.position = new Vector3(transform.position.x,1f,transform.position.z);
    }

    void OnCollisionEnter(Collision col) {
        if (col.gameObject.tag=="Enemy")
        {
            Explode();
        }
    }

    void Explode() {
        /*
        for (int i=transform.childCount-1; i>=0; i--) {
            Destroy(transform.GetChild(i).gameObject);
        }
        */
        //exp.Play();
        //Destroy(gameObject, exp.main.duration);
    }

    void Movement()
    {
        moving = new Vector3(Input.GetAxis("Horizontal"), 0f, Input.GetAxis("Vertical"));
        moving *= speed;
        moving = transform.rotation * moving;
        myCharController.Move(moving * Time.deltaTime);
    }

    void Rotation()
    {
        float mouseY = Input.GetAxis("Mouse Y") * 400f * Time.deltaTime;
        xRotation-=mouseY;
        xRotation = Mathf.Clamp(xRotation,-90f,90f);
        head.localRotation = Quaternion.Euler(xRotation,0f,0f);
        gun.localRotation = Quaternion.Euler(xRotation,0f,0f);
        transform.Rotate(new Vector3(0, Input.GetAxis("Mouse X") * 4.0f, 0));
    }
}