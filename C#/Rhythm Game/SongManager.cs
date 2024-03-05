using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Melanchall.DryWetMidi.Core;
using Melanchall.DryWetMidi.Interaction;
using System.IO;
using UnityEngine.Networking;
using UnityEngine.UI;
using UnityEngine.Audio;
using UnityEngine.SceneManagement;

public class SongManager : MonoBehaviour
{
    public bool areInstructionsVisible;

    public bool toPlay;
    public bool isGameOver;
    public float timeBeforeDespawn;
    public TMPro.TextMeshPro instructionText;
    public ScoreManager healthCheck;
    public static SongManager Instance;
    public AudioSource audioSource;
    public Lane[] lanes;
    public float songDelayInSeconds;
    public double marginOfError;
    public int inputDelayInMilliseconds;

    public string fileLocation;
    public float noteTime;
    public float noteSpawnY;
    public float noteTapY;
    public float noteDespawnY
    {
        get
        {
            return noteTapY - (noteSpawnY - noteTapY);
        }
    }

    public static MidiFile midiFile;

    public GameObject noteLanes, buttonIndicators, arrowPressFX;

    // Start is called before the first frame update
    void Start()
    {
        toPlay = false;
        isGameOver = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (!toPlay)
        {
            if (Input.GetKey(KeyCode.Return))
            {
                toPlay = true;
                Instance = this;
                StartSong();
                instructionText.text = "";
                if (Application.streamingAssetsPath.StartsWith("http://") || Application.streamingAssetsPath.StartsWith("https://"))
                {
                    StartCoroutine(ReadFromWebsite());
                }
                else
                {
                    ReadFromFile();
                }
            }
        }
        else
        {
            CheckConditions();
        }
    }

    private IEnumerator ReadFromWebsite()
    {
        using (UnityWebRequest www = UnityWebRequest.Get(Path.Combine(Application.streamingAssetsPath, fileLocation)))
        {
            yield return www.SendWebRequest();

            if (www.result == UnityWebRequest.Result.ConnectionError || www.result == UnityWebRequest.Result.ProtocolError)
            {
                Debug.LogError(www.error);
            }
            else
            {
                byte[] results = www.downloadHandler.data;
                using (var stream = new MemoryStream(results))
                {
                    midiFile = MidiFile.Read(stream);
                    GetDataFromMidi();
                }
            }
        }
    }

    private void ReadFromFile()
    {
        midiFile = MidiFile.Read(Application.streamingAssetsPath + "/" + fileLocation);
        GetDataFromMidi();
    }

    public void GetDataFromMidi()
    {
        var notes = midiFile.GetNotes();
        var array = new Melanchall.DryWetMidi.Interaction.Note[notes.Count];
        notes.CopyTo(array, 0);

        foreach (var lane in lanes)
        {
            lane.SetTimeStamps(array);
        }

        //this is the trigger to play the song
        Invoke(nameof(StartSong), songDelayInSeconds);
    }

    public void StartSong()
    {
        audioSource.Play();
    }

    public static double GetAudioSourceTime()
    {
        return (double)Instance.audioSource.timeSamples / Instance.audioSource.clip.frequency;
    }

    public void CheckConditions()
    {

        if (!audioSource.isPlaying)
        {
            SceneManager.LoadScene("StoryEndComicScene");
        }
        if (healthCheck.GetHealth() <= 0)
        {
            if (!isGameOver)
            {
                timeBeforeDespawn = Time.time + 2.0f;
                isGameOver = true;
                noteLanes.SetActive(false);
                buttonIndicators.SetActive(false);
                arrowPressFX.SetActive(false);
            }

            if (Time.time >= timeBeforeDespawn)
            {
                SceneManager.LoadScene("LoseScreenScene");
            }
        }
    }

    public bool getPlayStatus()
    {
        return toPlay;
    }
}
