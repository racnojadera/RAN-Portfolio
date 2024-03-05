using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour
{

    public static ScoreManager Instance;
    public AudioSource hitSFX;
    public AudioSource missSFX;
    public TMPro.TextMeshPro scoreText;
    static int comboScore;

    public static int health;
    public RhythmGameHealthBarScript healthBar;
    public Image fillColor;

    private float currentTime;
    private bool playerMissed = false;

    // Start is called before the first frame update
    void Start()
    {
        Instance = this;
        comboScore = 0;
        health = 20;
    }

    public static void Hit()
    {
        comboScore += 1;
        Instance.hitSFX.Play();
    }

    public static void Miss()
    {
        comboScore = 0;
        if (health >= 0)
        {
            health -= 5;
        }
        Instance.missSFX.Play();
        Instance.playerMissed = true;
    }

    // Update is called once per frame
    void Update()
    {
        if (comboScore > 1)
        {
            scoreText.text = comboScore.ToString() + "\nCOMBO!";
        }
        else
        {
            scoreText.text = "";
        }
        healthBar.SetHealth(health);
        CheckIfHPFillChangeColor();
    }

    void CheckIfHPFillChangeColor()
    {
        if (health >= 12)
        {
            fillColor.GetComponent<Image>().color = new Color32(0, 255, 0, 255);
        }
        else if (health >= 6)
        {
            fillColor.GetComponent<Image>().color = new Color32(255, 255, 0, 255);
        }
        else
        {
            fillColor.GetComponent<Image>().color = new Color32(255, 0, 0, 255);
        }
    }

    public int GetHealth()
    {
        return health;
    }

    public void SetHealth(int newValue)
    {
        health = newValue;
    }

    public bool GetMiss()
    {
        return playerMissed;
    }

    public void ResetMiss()
    {
        playerMissed = false;
    }
}
