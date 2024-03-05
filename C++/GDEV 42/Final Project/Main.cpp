#include <raylib.h>
#include <raymath.h>

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <cmath>

//base init here
int windowWidth = 800, windowHeight = 600;
float masterVolume = 0.75f, sfxVolume = 0.75f, bgmVolume = 0.50f;
Music musicBGM;
float musicPan;
Sound soundClick, soundCol;
bool isSounds = true;
bool hasStarted;
Vector2 mousePosition;

float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}


//https://github.com/Pakz001/Raylib-Examples/blob/master/Collision_-_LinesegCircleCollide.c
bool LineCircleCollision(int x1, int y1, int x2, int y2, int xc, int yc, float r)
{
    float xd = 0.0f;
    float yd = 0.0f;
    float t = 0.0f;
    float d = 0.0f;
    float dx = 0.0f;
    float dy = 0.0f;

    dx = x2 - x1;
    dy = y2 - y1;

    t = ((yc - y1) * dy + (xc - x1) * dx) / (dy * dy + dx * dx);

    if(0 <= t && t <= 1)
    {
        xd = x1 + t * dx;
        yd = y1 + t * dy;

        d = (xd - xc) * (xd - xc) + (yd - yc) * (yd - yc);
        return d <= r*r;
    }
    else
    {
        d = (xc - x1) * (xc - x1) + (yc - y1) * (yc - y1);
        if(d <= r*r)
        {
            return true;
        }
        else
        {
            d = (xc - x2) * (xc - x2) + (yc - y2) * (yc - y2);
            if(d <= r*r)
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
    }

}

struct UIComponent
{
    Rectangle bounds;
    virtual void Draw() = 0;
    virtual bool HandleClick(Vector2 clickPosition) = 0;
};

struct UIContainer : public UIComponent
{
    std::vector<UIComponent*> children;

    void AddChild(UIComponent* child)
    {
        children.push_back(child);
    }

    void Draw() override
    {
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->Draw();
        }
    }

    bool HandleClick(Vector2 clickPosition) override
    {
        for (size_t i = children.size(); i > 0; --i)
        {
            if (children[i-1]->HandleClick(clickPosition))
            {
                return true;
            }
        }
        return false;
    }
};

struct UILibrary
{
    UIContainer rootContainer;

    void Update()
    {
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            rootContainer.HandleClick(GetMousePosition());
        }
    }

    void Draw()
    {
        rootContainer.Draw();
    }
};

class Scene;

class SceneManager
{
    std::unordered_map<int, Scene*> m_scenes;
    Scene* m_activeScene = nullptr;

public:
    void RegisterScene(Scene* scene, int sceneId)
    {
        m_scenes[sceneId] = scene;
    }
    void UnregisterScene(int sceneId)
    {
        m_scenes.erase(sceneId);
    }
    void SwitchScene(int sceneId);

    Scene* GetActiveScene()
    {
        return m_activeScene;
    }
};

class Scene
{
public:
    SceneManager* m_sceneManager;

    virtual void Begin() = 0;
    virtual void End() = 0;

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

void SceneManager::SwitchScene(int sceneId)
{
    if (m_scenes.find(sceneId) == m_scenes.end())
    {
        return;
    }

    if (m_activeScene != nullptr)
    {
        m_activeScene->End();
    }

    m_activeScene = m_scenes[sceneId];

    m_activeScene->Begin();
};

SceneManager sceneManager;

class ResourceManager
{
    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Music> m_music;
    std::unordered_map<std::string, Sound> m_sound;

    ResourceManager()
    {
    }

public:
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    static ResourceManager* GetInstance()
    {
        static ResourceManager instance;
        return &instance;
    }

    Texture GetTexture(const std::string& path)
    {
        if (m_textures.find(path) == m_textures.end())
        {
            std::cout << "Loaded " << path << " from disk" << std::endl;
            m_textures[path] = LoadTexture(path.c_str());
        }
        return m_textures[path];
    }

    Music GetMusic(const std::string& path)
    {
        if (m_music.find(path) == m_music.end())
        {
            std::cout << "Loaded " << path << " from disk" << std::endl;
            m_music[path] = LoadMusicStream(path.c_str());
        }
        
        return m_music[path];
    }

    Sound GetSound(const std::string& path)
    {
        if(m_sound.find(path) == m_sound.end())
        {
            std::cout << "Loaded " << path << " from disk" << std::endl;
            m_sound[path] = LoadSound(path.c_str());
        }
        return m_sound[path];
    }

    void UnloadTextures()
    {
        for (auto it : m_textures)
        {
            UnloadTexture(it.second);
        }

        m_textures.clear();
    }

    void UnloadMusic()
    {
        for (auto it : m_music)
        {
            UnloadMusicStream(it.second);
        }

        m_music.clear();
    }

    void UnloadSound()
    {
        for (auto it : m_sound)
        {
            UnloadSound();
        }

        m_sound.clear();
    }
};

struct Button : public UIComponent
{
    Texture buttonTexture;
    std::string text;
    std::function<void()> clickHandler;
    int textWidth = MeasureText(text.c_str(), 14);

    void Draw() override
    {
        DrawRectangleRec(bounds, CLITERAL(Color){255, 255, 255, 0});
        DrawTexture(buttonTexture, bounds.x, bounds.y, WHITE);
    }

    bool HandleClick(Vector2 clickPosition) override
    {
        if (CheckCollisionPointRec(clickPosition, bounds))
        {
            if(clickHandler)
            {
                PlaySound(soundClick);
                clickHandler();
            }
            return true;
        }
        return false;
    }

    void SetTexture(std::string texture)
    {
        buttonTexture = ResourceManager::GetInstance()->GetTexture(texture);
    }
};

struct Label : public UIComponent
{
    std::string text;

    void Draw() override
    {
        DrawText(text.c_str(), bounds.x, bounds.y, 14, BLACK);
    }

    bool HandleClick(Vector2 clickPosition) override
    {
        return false;
    }  
};

void ToMainMenuScene()
{
    sceneManager.SwitchScene(0);
}

void ToLevelSelectScene()
{
    sceneManager.SwitchScene(1);
}

void ToLevel1Scene()
{
    sceneManager.SwitchScene(2);
}

void ToLevel2Scene()
{
    sceneManager.SwitchScene(3);
}

void ToLevel3Scene()
{
    sceneManager.SwitchScene(4);
}

void QuitGame()
{
    CloseWindow();
}

void ToCongratulationsScene()
{
    sceneManager.SwitchScene(5);
}

void AdjustSound()
{
    if(isSounds)
    {
        SetSoundVolume(soundClick, 0.0f);
    }
    else
    {
        SetSoundVolume(soundClick, sfxVolume);
    }
    isSounds = !isSounds;
}

void StartLevel()
{
    hasStarted = true;
}

class MainMenuScene : public Scene
{
    UILibrary uiLibrary;
    Button playButton, soundButton, quitButton;
    Texture mainMenuLabel;

public:
    void Begin() override
    {
        mainMenuLabel = ResourceManager::GetInstance()->GetTexture("textures/mainMenuTitle.png");

        uiLibrary.rootContainer.bounds = {0, 0, (float)windowWidth, (float)windowHeight};

        playButton.text = "Play";
        playButton.bounds = { (float)(windowWidth/2 - 150), (float)(windowHeight/2 - 150), 300, 300 };
        playButton.SetTexture("textures/mainMenuPlay.png");
        playButton.clickHandler = ToLevelSelectScene;
        uiLibrary.rootContainer.AddChild(&playButton);

        soundButton.text = "Sound";
        soundButton.bounds = { (float)(windowWidth/2 - 80), (float)(windowHeight/2 + 160), 60, 60 };
        soundButton.SetTexture("textures/mainMenuSound.png");
        soundButton.clickHandler = AdjustSound;
        uiLibrary.rootContainer.AddChild(&soundButton);

        quitButton.text = "Quit";
        quitButton.bounds = { (float)(windowWidth/2 + 20), (float)(windowHeight/2 + 160), 60, 60 };
        quitButton.SetTexture("textures/mainMenuQuit.png");
        quitButton.clickHandler = QuitGame;
        uiLibrary.rootContainer.AddChild(&quitButton);
    }
    
    void End() override
    {
        ResourceManager::GetInstance()->UnloadTextures();
    }

    void Update() override
    {
        uiLibrary.Update();
    }

    void Draw() override
    {
        DrawTexture(mainMenuLabel, windowWidth/2 - 172, 40, WHITE);
        uiLibrary.Draw();
    }
};

class LevelSelectionScene : public Scene
{
    UILibrary uiLibrary;
    Button level1Button, level2Button, level3Button;
    Button backToMainMenu;
    Texture levelSelectLabel;

public:
    void Begin() override
    {
        levelSelectLabel = ResourceManager::GetInstance()->GetTexture("textures/levelSelectLabel.png");

        uiLibrary.rootContainer.bounds = { 0, 0, (float)windowWidth, (float)windowHeight };

        level1Button.text = "Level 1";
        level1Button.bounds = { (float)(windowWidth/2 - 350), (float)(windowHeight/2-100), 200, 200 };
        level1Button.SetTexture("textures/level1Button.png");
        level1Button.clickHandler = ToLevel1Scene;
        uiLibrary.rootContainer.AddChild(&level1Button);

        level2Button.text = "Level 2";
        level2Button.bounds = { (float)(windowWidth/2 - 100), (float)(windowHeight/2-100), 200, 200 };
        level2Button.SetTexture("textures/level2Button.png");
        level2Button.clickHandler = ToLevel2Scene;
        uiLibrary.rootContainer.AddChild(&level2Button);

        level3Button.text = "Level 3";
        level3Button.bounds = { (float)(windowWidth/2 + 150), (float)(windowHeight/2-100), 200, 200 };
        level3Button.SetTexture("textures/level3Button.png");
        level3Button.clickHandler = ToLevel3Scene;
        uiLibrary.rootContainer.AddChild(&level3Button);

        backToMainMenu.text = "Back Main";
        backToMainMenu.bounds = { (float)(windowWidth - 100), (float)(windowHeight - 100), 60, 60 };
        backToMainMenu.SetTexture("textures/backMain.png");
        backToMainMenu.clickHandler = ToMainMenuScene;
        uiLibrary.rootContainer.AddChild(&backToMainMenu);
    }

    void End() override
    {
        ResourceManager::GetInstance()->UnloadTextures();
    }

    void Update() override
    {
        uiLibrary.Update();
    }

    void Draw() override
    {
        DrawTexture(levelSelectLabel, windowWidth/2 - 226, 40, WHITE);
        uiLibrary.Draw();
    }
};

struct Point
{
    Vector2 position;
    Vector2 velocity;
    Vector2 direction;
    float speed;
    float radius;
    Color color;
};

struct Goal
{
    Rectangle bounds;
    Color color;
};

struct Platform
{
    Rectangle bounds;
    Color color;
};

Vector2 LerpQuad(Vector2 pointA, Vector2 pointB, Vector2 pointC, float tValue)
{
    Vector2 ret;
    Vector2 firstComp, secondComp, thirdComp;
    float aConst = (1-tValue);
    firstComp = Vector2Scale(pointA, aConst*aConst);
    secondComp = Vector2Scale(pointB, 2*aConst*tValue);
    thirdComp = Vector2Scale(pointC, tValue*tValue);
    ret = Vector2Add(Vector2Add(firstComp, secondComp), thirdComp);
    return ret;
}

class Level1Scene : public Scene
{
    UILibrary uiLibrary;
    Button backToMainMenu, playLevel, restartLevel;
    Point ball;
    Goal goal;
    Platform ground;
    std::vector<Platform> listOfPlatforms;
    std::vector<Point> listOfPoints;
    std::vector<std::vector<Point>> listOfDrawnLines;

public:
    void Begin() override
    {
        hasStarted = false;
        uiLibrary.rootContainer.bounds = { 0, 0, (float)(windowWidth/2), 100 };

        backToMainMenu.text = "back";
        backToMainMenu.bounds = { 20, 20, 60, 60 };
        backToMainMenu.SetTexture("textures/backMain.png");
        backToMainMenu.clickHandler = ToLevelSelectScene;
        uiLibrary.rootContainer.AddChild(&backToMainMenu);

        playLevel.text = "play";
        playLevel.bounds = {100, 20, 60, 60};
        playLevel.SetTexture("textures/levelPlay.png");
        playLevel.clickHandler = StartLevel;
        uiLibrary.rootContainer.AddChild(&playLevel);

        restartLevel.text = "restart";
        restartLevel.bounds = {180, 20, 60, 60};
        restartLevel.SetTexture("textures/levelRestart.png");
        restartLevel.clickHandler = ToLevel1Scene;
        uiLibrary.rootContainer.AddChild(&restartLevel);

        ball.position = {100, 100};
        ball.velocity = {0, 0};
        ball.direction = {0, 1};
        ball.speed = 0.0f;
        ball.radius = 15;
        ball.color =CLITERAL(Color){0, 0, 255, 128};

        goal.bounds = {500, 500, 300, 100};
        goal.color = CLITERAL(Color){255, 0, 0, 128};

        ground.bounds = {0, (float)(windowHeight-20), (float)windowWidth, 20};
        ground.color = BLACK;
        listOfPlatforms.push_back(ground);

        mousePosition = GetMousePosition();
    }
    
    void End() override
    {
        ResourceManager::GetInstance()->UnloadTextures();
        listOfPlatforms.clear();
        listOfPoints.clear();
        listOfDrawnLines.clear();
    }

    void Update() override
    {
        uiLibrary.Update();
        if(hasStarted)
        {
            if(ball.speed < 0.1f)
            {
                ball.speed += 0.0002f;
            }

            for(size_t i = 0; i < listOfPlatforms.size(); ++i)
            {
                if(CheckCollisionCircleRec(ball.position, ball.radius, listOfPlatforms[i].bounds))
                {
                    ball.speed = 0;
                }
            }

            bool isColliding;
            int counter;

            for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
            {
                isColliding = false;
                if(listOfDrawnLines[i].size() >= 2)
                {
                    for(size_t j = 0; j < listOfDrawnLines[i].size() -1; ++j)
                    {
                        Point tempPoint1 = listOfDrawnLines[i][j];
                        Point tempPoint2 = listOfDrawnLines[i][j+1];
                        isColliding = LineCircleCollision(tempPoint1.position.x, tempPoint1.position.y, tempPoint2.position.x, tempPoint2.position.y, ball.position.x, ball.position.y, ball.radius);
                        if(isColliding)
                        {
                            counter = 0;
                            ball.direction.y = tempPoint2.position.y - tempPoint1.position.y;
                            ball.direction.x = tempPoint2.position.x - tempPoint1.position.x;
                        }
                    }
                }
                if(isColliding)
                {
                    counter++;
                }
            }
            if(counter >= 100000000)
            {
                if(ball.direction.y < 1)
                {
                    ball.direction.y += 0.01f;
                }
                if(abs(ball.direction.x) > 0)
                {
                    ball.direction.x *= 0.9992f;
                    if(abs(ball.direction.x) < 0.2)
                    {
                        ball.direction.x = 0.0f;
                    }
                }
            }

            if(ball.direction.x*ball.speed >= 0.1f)
            {
                ball.position.x += 0.1f;
            }
            else
            {
                ball.position.x += ball.direction.x*ball.speed;
            }
            
            if(ball.direction.y*ball.speed >= 0.1f)
            {
                ball.position.y += 0.1f;
            }
            else
            {
                ball.position.y += ball.direction.y*ball.speed;
            }

            if(CheckCollisionPointRec(ball.position, goal.bounds))
            {
                ToCongratulationsScene();
            }
        }
        else
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (mousePosition.x != GetMousePosition().x && mousePosition.y != GetMousePosition().y))
            {
                Point newPoint;
                newPoint.position = GetMousePosition();
                newPoint.velocity = {0, 0};
                newPoint.radius = 1;
                newPoint.color = BLACK;
                listOfPoints.push_back(newPoint);
                mousePosition = GetMousePosition();
            }
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                listOfDrawnLines.push_back(listOfPoints);
                listOfPoints.clear();
            }
        }
    }

    void Draw() override
    {
        uiLibrary.Draw();
        DrawCircleV(ball.position, ball.radius, ball.color);
        DrawRectangleRec(goal.bounds, goal.color);
        
        for(size_t i = 0; i < listOfPlatforms.size(); ++i)
        {
            DrawRectangleRec(listOfPlatforms[i].bounds, listOfPlatforms[i].color);
        }
        
        for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
        {
            for(size_t j = 0; j < listOfDrawnLines[i].size(); ++j)
            {
                Point tempPoint = listOfDrawnLines[i][j];
                DrawCircleV(tempPoint.position, tempPoint.radius, tempPoint.color);
            }
        }

        if(listOfPoints.size() != 0)
        {
            for(size_t i = 0; i < listOfPoints.size(); ++i)
            {
                DrawCircleV(listOfPoints[i].position, listOfPoints[i].radius, listOfPoints[i].color);
            }
        }

        for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
        {
            if(listOfDrawnLines[i].size() >= 2)
            {
                for(size_t j = 0; j < listOfDrawnLines[i].size() - 1; ++j)
                {
                    Point tempPoint1 = listOfDrawnLines[i][j];
                    Point tempPoint2 = listOfDrawnLines[i][j+1];
                    DrawLineV(tempPoint1.position, tempPoint2.position, BLACK);
                }
            }
        }
        if(listOfPoints.size() >= 2)
        {
            for(size_t i = 0; i < listOfPoints.size() - 1; ++i)
            {
                DrawLineV(listOfPoints[i].position, listOfPoints[i+1].position, BLACK);
            }
        }
    }
};

class Level2Scene : public Scene
{
    UILibrary uiLibrary;
    Button backToMainMenu, playLevel, restartLevel;
    Point ball;
    Goal goal;
    Platform ground, platform1;
    std::vector<Platform> listOfPlatforms;
    std::vector<Point> listOfPoints;
    std::vector<std::vector<Point>> listOfDrawnLines;

public:
    void Begin() override
    {
        hasStarted = false;
        uiLibrary.rootContainer.bounds = { 0, 0, (float)(windowWidth/2), 100 };

        backToMainMenu.text = "back";
        backToMainMenu.bounds = { 20, 20, 60, 60 };
        backToMainMenu.SetTexture("textures/backMain.png");
        backToMainMenu.clickHandler = ToLevelSelectScene;
        uiLibrary.rootContainer.AddChild(&backToMainMenu);

        playLevel.text = "play";
        playLevel.bounds = {100, 20, 60, 60};
        playLevel.SetTexture("textures/levelPlay.png");
        playLevel.clickHandler = StartLevel;
        uiLibrary.rootContainer.AddChild(&playLevel);

        restartLevel.text = "restart";
        restartLevel.bounds = {180, 20, 60, 60};
        restartLevel.SetTexture("textures/levelRestart.png");
        restartLevel.clickHandler = ToLevel2Scene;
        uiLibrary.rootContainer.AddChild(&restartLevel);

        ball.position = {100, 100};
        ball.velocity = {0, 0};
        ball.direction = {0, 1};
        ball.speed = 0.0f;
        ball.radius = 15;
        ball.color = CLITERAL(Color){0, 0, 255, 128};

        goal.bounds = {50, 500, 300, 100};
        goal.color = CLITERAL(Color){255, 0, 0, 128};

        ground.bounds = {0, (float)(windowHeight-20), (float)windowWidth, 20};
        ground.color = BLACK;
        listOfPlatforms.push_back(ground);

        platform1.bounds = {50, 350, 300, 30};
        platform1.color = BLACK;
        listOfPlatforms.push_back(platform1);
        

        mousePosition = GetMousePosition();
    }
    
    void End() override
    {
        ResourceManager::GetInstance()->UnloadTextures();
        listOfPlatforms.clear();
        listOfPoints.clear();
        listOfDrawnLines.clear();
    }

    void Update() override
    {
        uiLibrary.Update();
        if(hasStarted)
        {
            if(ball.speed < 0.1f)
            {
                ball.speed += 0.0002f;
            }

            for(size_t i = 0; i < listOfPlatforms.size(); ++i)
            {
                if(CheckCollisionCircleRec(ball.position, ball.radius, listOfPlatforms[i].bounds))
                {
                    ball.speed = 0;
                }
            }

            bool isColliding;
            int counter;
            for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
            {
                isColliding = false;
                if(listOfDrawnLines[i].size() >= 2)
                {
                    for(size_t j = 0; j < listOfDrawnLines[i].size() -1; ++j)
                    {
                        Point tempPoint1 = listOfDrawnLines[i][j];
                        Point tempPoint2 = listOfDrawnLines[i][j+1];
                        isColliding = LineCircleCollision(tempPoint1.position.x, tempPoint1.position.y, tempPoint2.position.x, tempPoint2.position.y, ball.position.x, ball.position.y, ball.radius);
                        if(isColliding)
                        {
                            counter = 0;
                            ball.direction.y = tempPoint2.position.y - tempPoint1.position.y;
                            ball.direction.x = tempPoint2.position.x - tempPoint1.position.x;
                        }
                    }
                }
                if(isColliding)
                {
                    counter++;
                }
            }
            if(counter >= 100000000)
            {
                if(ball.direction.y < 1)
                {
                    ball.direction.y += 0.01f;
                }
                if(abs(ball.direction.x) > 0)
                {
                    ball.direction.x *= 0.9992f;
                    if(abs(ball.direction.x) < 0.2)
                    {
                        ball.direction.x = 0.0f;
                    }
                }
            }

            if(ball.direction.x*ball.speed >= 0.1f)
            {
                ball.position.x += 0.1f;
            }
            else
            {
                ball.position.x += ball.direction.x*ball.speed;
            }
            
            if(ball.direction.y*ball.speed >= 0.1f)
            {
                ball.position.y += 0.1f;
            }
            else
            {
                ball.position.y += ball.direction.y*ball.speed;
            }

            if(CheckCollisionPointRec(ball.position, goal.bounds))
            {
                ToCongratulationsScene();
            }
        }
        else
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (mousePosition.x != GetMousePosition().x && mousePosition.y != GetMousePosition().y))
            {
                Point newPoint;
                newPoint.position = GetMousePosition();
                newPoint.velocity = {0, 0};
                newPoint.radius = 1;
                newPoint.color = BLACK;
                listOfPoints.push_back(newPoint);
                mousePosition = GetMousePosition();
            }
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                listOfDrawnLines.push_back(listOfPoints);
                listOfPoints.clear();
            }
        }
    }

    void Draw() override
    {
        uiLibrary.Draw();
        DrawCircleV(ball.position, ball.radius, ball.color);
        DrawRectangleRec(goal.bounds, goal.color);

        for(size_t i = 0; i < listOfPlatforms.size(); ++i)
        {
            DrawRectangleRec(listOfPlatforms[i].bounds, listOfPlatforms[i].color);
        }
        
        for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
        {
            for(size_t j = 0; j < listOfDrawnLines[i].size(); ++j)
            {
                Point tempPoint = listOfDrawnLines[i][j];
                DrawCircleV(tempPoint.position, tempPoint.radius, tempPoint.color);
            }
        }

        if(listOfPoints.size() != 0)
        {
            for(size_t i = 0; i < listOfPoints.size(); ++i)
            {
                DrawCircleV(listOfPoints[i].position, listOfPoints[i].radius, listOfPoints[i].color);
            }
        }

        for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
        {
            if(listOfDrawnLines[i].size() >= 2)
            {
                for(size_t j = 0; j < listOfDrawnLines[i].size() - 1; ++j)
                {
                    Point tempPoint1 = listOfDrawnLines[i][j];
                    Point tempPoint2 = listOfDrawnLines[i][j+1];
                    DrawLineV(tempPoint1.position, tempPoint2.position, BLACK);
                }
            }
        }
        if(listOfPoints.size() >= 2)
        {
            for(size_t i = 0; i < listOfPoints.size() - 1; ++i)
            {
                DrawLineV(listOfPoints[i].position, listOfPoints[i+1].position, BLACK);
            }
        }
    }
};

class Level3Scene : public Scene
{
    UILibrary uiLibrary;
    Button backToMainMenu, playLevel, restartLevel;
    Point ball;
    Goal goal;
    Platform ground, platform1;
    std::vector<Platform> listOfPlatforms;
    std::vector<Point> listOfPoints;
    std::vector<std::vector<Point>> listOfDrawnLines;

public:
    void Begin() override
    {
        hasStarted = false;
        uiLibrary.rootContainer.bounds = { 0, 0, (float)(windowWidth/2), 100 };

        backToMainMenu.text = "back";
        backToMainMenu.bounds = { 20, 20, 60, 60 };
        backToMainMenu.SetTexture("textures/backMain.png");
        backToMainMenu.clickHandler = ToLevelSelectScene;
        uiLibrary.rootContainer.AddChild(&backToMainMenu);

        playLevel.text = "play";
        playLevel.bounds = {100, 20, 60, 60};
        playLevel.SetTexture("textures/levelPlay.png");
        playLevel.clickHandler = StartLevel;
        uiLibrary.rootContainer.AddChild(&playLevel);

        restartLevel.text = "restart";
        restartLevel.bounds = {180, 20, 60, 60};
        restartLevel.SetTexture("textures/levelRestart.png");
        restartLevel.clickHandler = ToLevel3Scene;
        uiLibrary.rootContainer.AddChild(&restartLevel);

        ball.position = {100, 400};
        ball.velocity = {0, 0};
        ball.direction = {0, 1};
        ball.speed = 0.0f;
        ball.radius = 15;
        ball.color = CLITERAL(Color){0, 0, 255, 128};

        goal.bounds = {300, 150, 100, 100};
        goal.color = CLITERAL(Color){255, 0, 0, 128};

        ground.bounds = {0, (float)(windowHeight-20), (float)windowWidth, 20};
        ground.color = BLACK;
        listOfPlatforms.push_back(ground);

        platform1.bounds = {50, 300, 300, 30};
        platform1.color = BLACK;
        listOfPlatforms.push_back(platform1);
        

        mousePosition = GetMousePosition();
    }
    
    void End() override
    {
        ResourceManager::GetInstance()->UnloadTextures();
        listOfPlatforms.clear();
        listOfPoints.clear();
        listOfDrawnLines.clear();
    }

    void Update() override
    {
        uiLibrary.Update();
        if(hasStarted)
        {
            if(ball.speed < 0.1f)
            {
                ball.speed += 0.0002f;
            }

            for(size_t i = 0; i < listOfPlatforms.size(); ++i)
            {
                if(CheckCollisionCircleRec(ball.position, ball.radius, listOfPlatforms[i].bounds))
                {
                    ball.speed = 0;
                }
            }

            bool isColliding;
            int counter;
            for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
            {
                isColliding = false;
                if(listOfDrawnLines[i].size() >= 2)
                {
                    for(size_t j = 0; j < listOfDrawnLines[i].size() -1; ++j)
                    {
                        Point tempPoint1 = listOfDrawnLines[i][j];
                        Point tempPoint2 = listOfDrawnLines[i][j+1];
                        isColliding = LineCircleCollision(tempPoint1.position.x, tempPoint1.position.y, tempPoint2.position.x, tempPoint2.position.y, ball.position.x, ball.position.y, ball.radius);
                        if(isColliding)
                        {
                            counter = 0;
                            ball.direction.y = tempPoint2.position.y - tempPoint1.position.y;
                            ball.direction.x = tempPoint2.position.x - tempPoint1.position.x;
                        }
                    }
                }
                if(isColliding)
                {
                    counter++;
                }
            }
            if(counter >= 100000000)
            {
                if(ball.direction.y < 1)
                {
                    ball.direction.y += 0.01f;
                }
                if(abs(ball.direction.x) > 0)
                {
                    ball.direction.x *= 0.9992f;
                    if(abs(ball.direction.x) < 0.2)
                    {
                        ball.direction.x = 0.0f;
                    }
                }
            }
            
            if(ball.direction.x*ball.speed >= 0.1f)
            {
                ball.position.x += 0.1f;
            }
            else
            {
                ball.position.x += ball.direction.x*ball.speed;
            }
            
            if(ball.direction.y*ball.speed >= 0.1f)
            {
                ball.position.y += 0.1f;
            }
            else
            {
                ball.position.y += ball.direction.y*ball.speed;
            }

            if(CheckCollisionPointRec(ball.position, goal.bounds))
            {
                ToCongratulationsScene();
            }
        }
        else
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (mousePosition.x != GetMousePosition().x && mousePosition.y != GetMousePosition().y))
            {
                Point newPoint;
                newPoint.position = GetMousePosition();
                newPoint.velocity = {0, 0};
                newPoint.radius = 1;
                newPoint.color = BLACK;
                listOfPoints.push_back(newPoint);
                mousePosition = GetMousePosition();
            }
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                listOfDrawnLines.push_back(listOfPoints);
                listOfPoints.clear();
            }
        }
    }

    void Draw() override
    {
        uiLibrary.Draw();
        DrawCircleV(ball.position, ball.radius, ball.color);
        DrawRectangleRec(goal.bounds, goal.color);

        for(size_t i = 0; i < listOfPlatforms.size(); ++i)
        {
            DrawRectangleRec(listOfPlatforms[i].bounds, listOfPlatforms[i].color);
        }
        
        for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
        {
            for(size_t j = 0; j < listOfDrawnLines[i].size(); ++j)
            {
                Point tempPoint = listOfDrawnLines[i][j];
                DrawCircleV(tempPoint.position, tempPoint.radius, tempPoint.color);
            }
        }

        if(listOfPoints.size() != 0)
        {
            for(size_t i = 0; i < listOfPoints.size(); ++i)
            {
                DrawCircleV(listOfPoints[i].position, listOfPoints[i].radius, listOfPoints[i].color);
            }
        }

        for(size_t i = 0; i < listOfDrawnLines.size(); ++i)
        {
            if(listOfDrawnLines[i].size() >= 2)
            {
                for(size_t j = 0; j < listOfDrawnLines[i].size() - 1; ++j)
                {
                    Point tempPoint1 = listOfDrawnLines[i][j];
                    Point tempPoint2 = listOfDrawnLines[i][j+1];
                    DrawLineV(tempPoint1.position, tempPoint2.position, BLACK);
                }
            }
        }
        if(listOfPoints.size() >= 2)
        {
            for(size_t i = 0; i < listOfPoints.size() - 1; ++i)
            {
                DrawLineV(listOfPoints[i].position, listOfPoints[i+1].position, BLACK);
            }
        }
    }
};

class CongratulationsScene : public Scene
{
    UILibrary uiLibrary;
    Button returnButton, quitButton;
    Texture congratulationsLabel;

public:
    void Begin() override
    {
        congratulationsLabel = ResourceManager::GetInstance()->GetTexture("textures/congratulationsTitle.png");

        uiLibrary.rootContainer.bounds = {0, 0, (float)windowWidth, (float)windowHeight};

        returnButton.text = "return";
        returnButton.bounds = { (float)(windowWidth/2 - 80), (float)(windowHeight/2 + 80), 60, 60 };
        returnButton.SetTexture("textures/backMain.png");
        returnButton.clickHandler = ToLevelSelectScene;
        uiLibrary.rootContainer.AddChild(&returnButton);

        quitButton.text = "Quit";
        quitButton.bounds = { (float)(windowWidth/2 + 20), (float)(windowHeight/2 + 80), 60, 60 };
        quitButton.SetTexture("textures/mainMenuQuit.png");
        quitButton.clickHandler = QuitGame;
        uiLibrary.rootContainer.AddChild(&quitButton);
    }

    void End() override
    {
        ResourceManager::GetInstance()->UnloadTextures();
    }

    void Update() override
    {
        uiLibrary.Update();
    }

    void Draw() override
    {
        DrawTexture(congratulationsLabel, windowWidth/2 - 275, windowHeight/2 - 120, WHITE);
        uiLibrary.Draw();
    }
};

int main()
{
    InitWindow(windowWidth, windowHeight, "GDEV 42 Final Project");
    SetTargetFPS(30000);

    InitAudioDevice();
    
    soundClick = ResourceManager::GetInstance()->GetSound("soundbgm/mouseClick.wav");
    SetSoundVolume(soundClick, sfxVolume);

    MainMenuScene MainMenuScene;
    MainMenuScene.m_sceneManager = &sceneManager;

    LevelSelectionScene LevelSelectionScene;
    LevelSelectionScene.m_sceneManager = &sceneManager;

    Level1Scene Level1Scene;
    Level1Scene.m_sceneManager = &sceneManager;

    Level2Scene Level2Scene;
    Level2Scene.m_sceneManager = &sceneManager;

    Level3Scene Level3Scene;
    Level3Scene.m_sceneManager = &sceneManager;

    CongratulationsScene CongratulationsScene;
    CongratulationsScene.m_sceneManager = &sceneManager;

    sceneManager.RegisterScene(&MainMenuScene, 0);
    sceneManager.RegisterScene(&LevelSelectionScene, 1);
    sceneManager.RegisterScene(&Level1Scene, 2);
    sceneManager.RegisterScene(&Level2Scene, 3);
    sceneManager.RegisterScene(&Level3Scene, 4);
    sceneManager.RegisterScene(&CongratulationsScene, 5);

    sceneManager.SwitchScene(0);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Scene* activeScene = sceneManager.GetActiveScene();

        if (activeScene != nullptr)
        {
            activeScene->Update();
            activeScene->Draw();
        }

        EndDrawing();
    }

    Scene* activeScene = sceneManager.GetActiveScene();
    if(activeScene != nullptr)
    {
        activeScene->End();
    }

    ResourceManager::GetInstance()->UnloadSound();
    CloseAudioDevice();

    ResourceManager::GetInstance()->UnloadTextures();

    CloseWindow();
    return 0;
}