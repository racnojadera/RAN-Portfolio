#include <raylib.h>
#include <raymath.h>

int main()
{
    int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Audio");

    InitAudioDevice();

    Music music1 = LoadMusicStream("music01.mp3");
    Music music2 = LoadMusicStream("music02.mp3");
    float musicPan1 = 0.5f;
    float musicPan2 = 0.5f;

    Sound sound1 = LoadSound("sound01.wav");
    Sound sound2 = LoadSound("sound02.wav");

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE))
        {
            if (!IsMusicStreamPlaying(music1))
            {
                PlayMusicStream(music1);
            }
            else
            {
                PauseMusicStream(music1);
            }
        }

        if (IsKeyPressed(KEY_TWO))
        {
            if (!IsMusicStreamPlaying(music2))
            {
                PlayMusicStream(music2);
            }
            else
            {
                PauseMusicStream(music2);
            }
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            musicPan1 = Clamp(musicPan1 - 0.1f, 0.0f, 1.0f);
            SetMusicPan(music1, musicPan1);
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            musicPan1 = Clamp(musicPan1 + 0.1f, 0.0f, 1.0f);
            SetMusicPan(music1, musicPan1);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(sound1);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            PlaySound(sound2);
        }

        if (IsMusicStreamPlaying(music1))
        {
            UpdateMusicStream(music1);
        }
        if (IsMusicStreamPlaying(music2))
        {
            UpdateMusicStream(music2);
        }

        ClearBackground(WHITE);
        BeginDrawing();

        DrawText("1 key - Play/pause music01.mp3", 10, 500, 16, RED);
        DrawText("2 key - Play/pause music02.mp3", 10, 520, 18, RED);
        DrawText("Left/right mouse button - Play sound01.wav and sound02.wav", 10, 540, 18, RED);
        DrawText("Left/right arrow keys - Set music1 panning", 10, 560, 18, RED);
        EndDrawing();
    }

    UnloadMusicStream(music1);
    UnloadMusicStream(music2);

    UnloadSound(sound1);
    UnloadSound(sound2);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}

