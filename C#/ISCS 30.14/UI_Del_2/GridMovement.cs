using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

// https://www.youtube.com/watch?v=AiZ4z4qKy44
public class GridMovement : MonoBehaviour
{
    [SerializeField]
    private Tilemap groundTilemap;
    [SerializeField]
    private Tilemap collisionTilemap;
    [SerializeField]
    private Tilemap stickyTilemap;
    [SerializeField]
    private Tilemap slipperyTilemap;
    [SerializeField]
    private Tilemap grassTilemap;
    public Canvas jrpgUI;
    public GameObject itemMenu, attackMenu, optionsMenu, monsterMenu, attackText;
    public SpriteRenderer charRenderer;
    public Sprite upCharSprite, downCharSprite, leftCharSprite, rightCharSprite;
    public Sprite upWalkSprite1, upWalkSprite2, downWalkSprite1, downWalkSprite2, leftWalkSprite1, leftWalkSprite2, rightWalkSprite1, rightWalkSprite2;
    private bool isMoving;
    private Vector3 origPos, targetPos;
    private float timeToMove = 0.2f;
    private bool altStep = false;

    void Start()
    {
        jrpgUI.gameObject.SetActive(false);
        charRenderer = gameObject.GetComponent<SpriteRenderer>();
    }
    // Update is called once per frame
    void Update()
    {
        //Speed Buttons
        if(Input.GetKeyDown(KeyCode.Space)){
            timeToMove = 0.1f;
        }
        if(Input.GetKeyUp(KeyCode.Space)){
            timeToMove = 0.2f;
        }

        if (!isMoving) {
            //UI integration
            if(IsGrass())
            {
                jrpgUI.gameObject.SetActive(true);
            }else
            {
                itemMenu.SetActive(false); 
                attackMenu.SetActive(false); 
                optionsMenu.SetActive(false);
                monsterMenu.SetActive(false);
                attackText.SetActive(false);
                jrpgUI.gameObject.SetActive(false);
            }

            if(IsSticky(new Vector3(0.0f, 0.0f, 0.0f)))
            {
                if (Input.GetKeyDown(KeyCode.W))
                {
                    ChangeSprite(upCharSprite);
                    StartCoroutine(MovePlayer(Vector3.up));
                }
                else if (Input.GetKeyDown(KeyCode.A))
                {
                    ChangeSprite(leftCharSprite);
                    StartCoroutine(MovePlayer(Vector3.left));
                }
                else if (Input.GetKeyDown(KeyCode.S))
                {
                    ChangeSprite(downCharSprite);
                    StartCoroutine(MovePlayer(Vector3.down));
                }
                else if (Input.GetKeyDown(KeyCode.D))
                {
                    ChangeSprite(rightCharSprite);
                    StartCoroutine(MovePlayer(Vector3.right));
                }
            }
            else
            {
                if (Input.GetKey(KeyCode.W))
                {
                    ChangeSprite(upCharSprite);
                    StartCoroutine(MovePlayer(Vector3.up));
                }
                else if (Input.GetKey(KeyCode.A))
                {
                    ChangeSprite(leftCharSprite);
                    StartCoroutine(MovePlayer(Vector3.left));
                }
                else if (Input.GetKey(KeyCode.S))
                {
                    ChangeSprite(downCharSprite);
                    StartCoroutine(MovePlayer(Vector3.down));
                }
                else if (Input.GetKey(KeyCode.D))
                {
                    ChangeSprite(rightCharSprite);
                    StartCoroutine(MovePlayer(Vector3.right));
                }
            }
        }
    }

    void ChangeSprite(Sprite newSprite)
    {
        charRenderer.sprite = newSprite;
    }

    private IEnumerator MovePlayer(Vector3 direction)
    {
        if(CanMoveTo(direction) && isMoving == false)
        {
            isMoving = true;
            float elapsedTime = 0;
            origPos = transform.position;
            targetPos = origPos + direction;

            if (altStep) {
                if (direction==Vector3.up) ChangeSprite(upWalkSprite1);
                if (direction==Vector3.left) ChangeSprite(leftWalkSprite1);
                if (direction==Vector3.down) ChangeSprite(downWalkSprite1);
                if (direction==Vector3.right) ChangeSprite(rightWalkSprite1);
            }
            else {
                if (direction==Vector3.up) ChangeSprite(upWalkSprite2);
                if (direction==Vector3.left) ChangeSprite(leftWalkSprite2);
                if (direction==Vector3.down) ChangeSprite(downWalkSprite2);
                if (direction==Vector3.right) ChangeSprite(rightWalkSprite2);
            }
            altStep = !altStep;

            while (elapsedTime < timeToMove)
            {
                transform.position = Vector3.Lerp(origPos, targetPos, (elapsedTime / timeToMove));
                elapsedTime += Time.deltaTime;
                yield return null;
            }

            transform.position = targetPos;
            isMoving = false;

            if (direction==Vector3.up) ChangeSprite(upCharSprite);
            if (direction==Vector3.left) ChangeSprite(leftCharSprite);
            if (direction==Vector3.down) ChangeSprite(downCharSprite);
            if (direction==Vector3.right) ChangeSprite(rightCharSprite);

            if (IsSlippery() && IsColliding(direction))
            {
                StartCoroutine(MovePlayer(direction));
            }
        }
    }

    private bool CanMoveTo(Vector2 direction)
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction);
        if (collisionTilemap.HasTile(gridPosition))
            return false;
        return true;
    }
     private bool IsGrass(){
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position);
        if (grassTilemap.HasTile(gridPosition))
            return true;
        return false;
    }

    private bool IsSticky(Vector3 direction)
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + direction);

        if (stickyTilemap.HasTile(gridPosition))
            return true;
        return false;
    }

    private bool IsColliding(Vector3 direction)
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + direction);
        if (collisionTilemap.HasTile(gridPosition))
            return false;
        return true;
    }

    private bool IsSlippery()
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position);
        if (slipperyTilemap.HasTile(gridPosition))
            return true;
        return false;
    }
}
