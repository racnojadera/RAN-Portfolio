using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float speed = 5;
    private Rigidbody2D body;
    public SpriteRenderer charRenderer;
    public Sprite leftStandSprite, rightStandSprite;
    public Sprite leftWalkSprite1, leftWalkSprite2, rightWalkSprite1, rightWalkSprite2;
    public Sprite leftJumpSprite, rightJumpSprite;
    public Sprite downSprite1, downSprite2;
    public bool isGrounded;
    public bool facingLeft;
    public bool altStep;
    public bool isWater;
    public float markX;
    public float jumpHeight = 2.2f;
    public float timeInversed = 1.0f;
    public bool invertedAxis = false;
    // Start is called before the first frame update
    void Start()
    {
        body = GetComponent<Rigidbody2D>();
        charRenderer = GetComponent<SpriteRenderer>();
        isGrounded = false;
        facingLeft = false;
        altStep = false;
        markX = transform.position.x;
        isWater = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (invertedAxis) body.velocity = new Vector2(Input.GetAxis("Horizontal") * speed*(-0.5f), body.velocity.y);
        else body.velocity = new Vector2(Input.GetAxis("Horizontal") * speed, body.velocity.y);
        isWater = (transform.position.x>8 && transform.position.y<0);
        if (isGrounded) {
            if (facingLeft) charRenderer.sprite = leftStandSprite;
            else charRenderer.sprite = rightStandSprite;
        }
        if (Mathf.Abs(markX-transform.position.x)>1.0f) {
            markX = transform.position.x;
            altStep = !altStep;
        }
        if (isWater) body.gravityScale = 0;
        else body.gravityScale = 2.0f;
        if (Input.GetKey(KeyCode.W)) {
            if (isGrounded) {
                body.velocity = new Vector2(body.velocity.x, speed*jumpHeight);
            }
        }
        if (Input.GetKey(KeyCode.A)) {
            if (altStep) charRenderer.sprite = leftWalkSprite1;
            else charRenderer.sprite = leftWalkSprite2;
            facingLeft = true;
        }
        if (Input.GetKey(KeyCode.D)) {
            if (altStep) charRenderer.sprite = rightWalkSprite1;
            else charRenderer.sprite = rightWalkSprite2;
            facingLeft = false;
        }
        if (!isGrounded) {
            if (body.velocity.y>0) {
                if(!invertedAxis)
                {
                    if (facingLeft) charRenderer.sprite = leftJumpSprite;
                    else charRenderer.sprite = rightJumpSprite;
                }
                else
                {
                    if (facingLeft) charRenderer.sprite = rightJumpSprite;
                    else charRenderer.sprite = leftJumpSprite;
                }
            }
            if (body.velocity.y<0) {
                if (facingLeft) charRenderer.sprite = leftStandSprite;
                else charRenderer.sprite = rightStandSprite;
            }
            if (Input.GetKey(KeyCode.S)) {
                charRenderer.sprite = downSprite2;
                body.gravityScale = 5;
            }
            else if (!isWater) body.gravityScale = 2;
        }
    }

    void OnCollisionStay2D(Collision2D col)
    {
        // isGrounded = true;

        if (col.gameObject.tag=="Wall")
        {
            if (Input.GetKey(KeyCode.W))
            {
                body.velocity = new Vector2(body.velocity.x, speed * jumpHeight);
                //insert movement to other direction here
                if (facingLeft)
                {
                    charRenderer.sprite = rightJumpSprite;
                    facingLeft = false;
                }
                else if(!facingLeft)
                {
                    charRenderer.sprite = leftJumpSprite;
                    facingLeft = true;
                }
                StartCoroutine(WallJumping());
            }
        }
        foreach (ContactPoint2D contact in col.contacts)
        {
            if (contact.normal == new Vector2(0,1)) isGrounded = true;
        }
        if (col.gameObject.tag == "Ground") isGrounded = true;
        if (col.gameObject.tag == "Spike") body.velocity = new Vector2(body.velocity.x, speed);
        if (col.gameObject.tag == "Sticky") speed = 1.5f;
        if (col.gameObject.tag == "MovingPlatform")
        {
            body.transform.parent=col.gameObject.transform;
        }
    }

    void OnCollisionExit2D(Collision2D col)
    {
        isGrounded = false;
        speed = 5.0f;
        if (col.gameObject.tag == "MovingPlatform")
        {
            body.transform.parent=null;
        }
    }

    private IEnumerator WallJumping()
    {
        float elapsedTime = 0.0f;
        while (elapsedTime < timeInversed)
        {
            invertedAxis = true;
            elapsedTime += Time.deltaTime;
            Debug.Log("Time currently: " + elapsedTime);
            yield return null;
        }
        invertedAxis = false;
    }
}
