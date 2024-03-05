using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public GameObject FirstMenu, FightMenu;
    public GameObject OptionsMenu, MonstersMenu, AttackMenu, ItemsMenu;
    public GameObject AttackText;

    public GameObject SlowCast, FastCast;

    public float timerGrowth = 0.0f;
    public float maxGrowthTime = 0.05f;
    public bool isMaxSize = false;

    // Start is called before the first frame update
    void Start()
    {
        ToMenuButton();
        SetSubmenuLocations();
    }

    // Update is called once per frame
    public void ToMenuButton()
    {
        FirstMenu.SetActive(true);
        FightMenu.SetActive(false);
        OptionsMenu.SetActive(false);
        MonstersMenu.SetActive(false);
        ItemsMenu.SetActive(false);
        AttackMenu.SetActive(false);
        AttackText.SetActive(false);
    }

    public void ToFightButton()
    {
        FirstMenu.SetActive(false);
        FightMenu.SetActive(true);
        OptionsMenu.SetActive(false);
        MonstersMenu.SetActive(false);
        ItemsMenu.SetActive(false);
        AttackMenu.SetActive(false);
        AttackText.SetActive(false);
    }

    public void openOptionsButton()
    {
        if (OptionsMenu.activeSelf == true)
        {
            OptionsMenu.SetActive(false);
            StartCoroutine(resetSubMenu(OptionsMenu));
        } else
        {
            OptionsMenu.SetActive(true);
            StartCoroutine(showSubMenu(OptionsMenu));
        }
        
    }

    public void openMonstersButton()
    {
        AttackMenu.SetActive(false);
        StartCoroutine(resetSubMenu(AttackMenu));
        ItemsMenu.SetActive(false);
        StartCoroutine(resetSubMenu(ItemsMenu));
        AttackText.SetActive(false);
        if (MonstersMenu.activeSelf == true)
        {
            MonstersMenu.SetActive(false);
            StartCoroutine(resetSubMenu(MonstersMenu));
        } else
        {
            MonstersMenu.SetActive(true);
            StartCoroutine(showSubMenu(MonstersMenu));
        }
        
    }

    public void openItemsButton()
    {
        AttackMenu.SetActive(false);
        StartCoroutine(resetSubMenu(AttackMenu));
        MonstersMenu.SetActive(false);
        StartCoroutine(resetSubMenu(MonstersMenu));
        AttackText.SetActive(false);
        if (ItemsMenu.activeSelf == true)
        {
            ItemsMenu.SetActive(false);
            StartCoroutine(resetSubMenu(ItemsMenu));
        } else
        {
            ItemsMenu.SetActive(true);
            StartCoroutine(showSubMenu(ItemsMenu));
        }
        
    }

    public void openAttacksButton()
    {
        MonstersMenu.SetActive(false);
        StartCoroutine(resetSubMenu(MonstersMenu));
        ItemsMenu.SetActive(false);
        StartCoroutine(resetSubMenu(ItemsMenu));
        AttackText.SetActive(false);
        if (AttackMenu.activeSelf == true)
        {
            AttackMenu.SetActive(false);
            StartCoroutine(resetSubMenu(AttackMenu));
        } else
        {
            AttackMenu.SetActive(true);
            StartCoroutine(showSubMenu(AttackMenu));
        }
    }

    public void attackUseButton()
    {
        AttackText.SetActive(true);
    }
    public void ExitButton()
    {
        Application.Quit();
    }

    public void setUICastingSlow()
    {
        maxGrowthTime = 1.5f;
    }

    public void setUICastingFast()
    {
        maxGrowthTime = 0.05f;
    }

    public void SetSubmenuLocations()
    {
        OptionsMenu.transform.position = new Vector3(FirstMenu.transform.position.x + 240.0f, FirstMenu.transform.position.y - 80.0f, FirstMenu.transform.position.z);
        MonstersMenu.transform.position = new Vector3(FirstMenu.transform.position.x + 240.0f, FirstMenu.transform.position.y - 80.0f, FirstMenu.transform.position.z);
        ItemsMenu.transform.position = new Vector3(FirstMenu.transform.position.x + 240.0f, FirstMenu.transform.position.y - 160.0f, FirstMenu.transform.position.z);
        AttackMenu.transform.position = new Vector3(FirstMenu.transform.position.x + 240.0f, FirstMenu.transform.position.y, FirstMenu.transform.position.z);
    }

    private IEnumerator showSubMenu(GameObject toModify)
    {
        isMaxSize = false;
        timerGrowth = 0.0f;
        do
        {
            toModify.transform.localScale = Vector3.Lerp(new Vector2(0.0f, 0.0f), new Vector2(1.0f, 1.0f), timerGrowth / maxGrowthTime);
            timerGrowth += Time.deltaTime;
            yield return null;
        }
        while (timerGrowth < maxGrowthTime);

        isMaxSize = true;
    }

    private IEnumerator resetSubMenu(GameObject toModify)
    {
        toModify.transform.localScale = new Vector2(0.0f, 0.0f);
        timerGrowth = 0.0f;
        yield return null;
        isMaxSize = false;
    }
}
