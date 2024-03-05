#include <raylib.h>
#include <raymath.h>

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <cmath>
#include "entt.hpp"

//base init here//
int windowWidth = 600, windowHeight = 450;
float masterVolume = 0.75f, sfxVolume = 0.75f, bgmVolume = 0.50f;
Music musicBGM;
float musicPan;
Sound soundClick, soundCol;

float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

enum class ObjectType
{
    Ball,
    Target,
    Powerup,
    Boundary,
    Platform
};

//entt components
struct PositionComponent
{
    Vector2 position;
};

struct MovementComponent
{
    Vector2 velocity;
};

struct CollisionComponent
{
    /*
    0 = ball
    1 = rectangle targets
    2 = power-up
    3 = boundaries
    4 = platform
    */
   int collisionType;
   Rectangle bounds;
};

struct ExplosionPowerupComponent
{
    int numberOfChildren = 3;
};

void SpawnCircle(entt::registry& registry, Vector2 position, Vector2 velocity)
{
    entt::entity e = registry.create();
    PositionComponent& tempObjPosition = registry.emplace<PositionComponent>(e);
    MovementComponent& tempObjMovement = registry.emplace<MovementComponent>(e);
    CollisionComponent& tempColType = registry.emplace<CollisionComponent>(e);

    tempObjPosition.position = position;
    tempObjMovement.velocity = velocity;
    tempColType.collisionType = 0;
    tempColType.bounds = {position.x, position.y, 10.0f, 10.0f};
}

void SpawnTarget(entt::registry& registry, Vector2 position, Vector2 size)
{
    entt::entity e = registry.create();
    PositionComponent& tempObjPosition = registry.emplace<PositionComponent>(e);
    CollisionComponent& tempColType = registry.emplace<CollisionComponent>(e);

    tempObjPosition.position = position;
    tempColType.collisionType = 1;
    tempColType.bounds = {position.x, position.y, size.x, size.y}; 

    if(GetRandomValue(0, 100) < 10)
    {
        ExplosionPowerupComponent& tempObjExpPowerUp = registry.emplace<ExplosionPowerupComponent>(e);
    }
}

void SpawnPowerup(entt::registry& registry, Vector2 position)
{
    entt::entity e = registry.create();
    PositionComponent& tempObjPosition = registry.emplace<PositionComponent>(e);
    MovementComponent& tempObjMovement = registry.emplace<MovementComponent>(e);
    CollisionComponent& tempColType = registry.emplace<CollisionComponent>(e);

    tempObjPosition.position = position;
    tempObjMovement.velocity = {0.0f, 3.0f};
    tempColType.collisionType = 2;
    tempColType.bounds = {position.x, position.y, 35.0f, 15.0f};
}

void SpawnWall(entt::registry& registry, Vector2 position, Vector2 size)
{
    entt::entity e = registry.create();
    PositionComponent& tempObjPosition = registry.emplace<PositionComponent>(e);
    CollisionComponent& tempColType = registry.emplace<CollisionComponent>(e);

    tempObjPosition.position = position;
    tempColType.collisionType = 3;
    tempColType.bounds = {position.x, position.y, size.x, size.y}; 
}

void SpawnPlatform(entt::registry&registry, Vector2 position)
{
    entt::entity e = registry.create();
    PositionComponent& tempObjPosition = registry.emplace<PositionComponent>(e);
    MovementComponent& tempObjMovement = registry.emplace<MovementComponent>(e);
    CollisionComponent& tempColType = registry.emplace<CollisionComponent>(e);

    tempObjPosition.position = position;
    tempObjMovement.velocity = {0.0f, 0.0f};
    tempColType.collisionType = 4;
    tempColType.bounds = {position.x, position.y, 80.0f, 15.0f};
}

void SpawnBoundary(entt::registry&registry, Vector2 position, Vector2 size)
{
    entt::entity e = registry.create();
    PositionComponent& tempObjPosition = registry.emplace<PositionComponent>(e);
    CollisionComponent& tempColType = registry.emplace<CollisionComponent>(e);

    tempObjPosition.position = position;
    tempColType.collisionType = 3;
    tempColType.bounds = {position.x, position.y, size.x, size.y};
}

//entt components

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
    // Root container
    UIContainer rootContainer;

    // Updates the current UI state
    void Update()
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            rootContainer.HandleClick(GetMousePosition());
        }
    }

    // Draw
    void Draw()
    {
        rootContainer.Draw();
    }
};

class Scene;

class SceneManager
{
    // Mapping between a scene ID and a reference to the scene
    // The m_ before the variable name is just a convention for
    // indicating that the variable is a member variable of the class
    std::unordered_map<int, Scene*> m_scenes;

    // Current active scene
    Scene* m_activeScene = nullptr;

public:
    // Adds the specified scene to the scene manager, and assigns it
    // to the specified scene ID
    void RegisterScene(Scene* scene, int sceneId)
    {
        m_scenes[sceneId] = scene;
    }

    // Removes the scene identified by the specified scene ID
    // from the scene manager
    void UnregisterScene(int sceneId)
    {
        m_scenes.erase(sceneId);
    }

    // Switches to the scene identified by the specified scene ID.
    // We only declare the function for now since we are going to call the
    // Begin/End functions of the Scene class inside this function, 
    // which haven't been declared yet at this point. 
    void SwitchScene(int sceneId);

    // Gets the active scene
    Scene* GetActiveScene()
    {
        return m_activeScene;
    }
};

// Base class for all scenes
class Scene
{
public:
    // Reference to the scene manager.
    // In practice, you would want to make this private (or protected)
    // and set this via the constructor.
    SceneManager* m_sceneManager;

    // Begins the scene. Loading of resources can go here
    virtual void Begin() = 0;
    // Ends the scene. Unloading of resources can go here
    virtual void End() = 0;

    // Updates the scene's current state
    virtual void Update() = 0;
    // Draw the scene's current state
    virtual void Draw() = 0;
};

// Now that the scene class has been defined (along with its Begin/End functions),
// we can now define the SwitchScene() function of the SceneManager class.
void SceneManager::SwitchScene(int sceneId)
{
    // If the scene ID does not exist in our records,
    // don't do anything (or you can print an error message).
    if (m_scenes.find(sceneId) == m_scenes.end())
    {
        return;
    }

    // If there is already an active scene, end it first
    if (m_activeScene != nullptr)
    {
        m_activeScene->End();
    }

    m_activeScene = m_scenes[sceneId];

    m_activeScene->Begin();
};

SceneManager sceneManager;

// Resource manager implemented as a singleton
// More information about singletons in C++ here:
// 
class ResourceManager
{
    // Mapping between a file path and the texture
    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Music> m_music;
    std::unordered_map<std::string, Sound> m_sound;

    // Make constructor private
    ResourceManager()
    {
    }

public:
    // Delete copy constructor and copy operator (=)
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    // Gets the singleton instance of the class
    static ResourceManager* GetInstance()
    {
        static ResourceManager instance;
        return &instance;
    }

    // Gets the texture at the specified file path
    Texture GetTexture(const std::string& path)
    {
        // If the texture does not exist yet in our records,
        // load it and store it in memory.
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
    // Unloads all textures that have been loaded
    void UnloadTextures()
    {
        // Iterate through each key-value pair in the map
        // it.first = path, it.second = texture
        for (auto it : m_textures)
        {
            UnloadTexture(it.second);
        }

        // Clear the map
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

/*
class SplashScene : public Scene
{
    // Ateneo logo texture handle
    Texture ateneoLogoTexture;

    // Timer to switch to the next scene
    float timer = 5.0f;

public:
    void Begin() override
    {
        // Retrieve the ateneo logo texture through the resource manager
        ateneoLogoTexture = ResourceManager::GetInstance()->GetTexture("ateneo_logo.png");
    }

    void End() override
    {
    }

    void Update() override
    {
        // Decrease timer
        timer = timer - GetFrameTime();

        if (timer <= 0.0f) // Time to switch scenes
        {
            // Make sure scene manager is not null
            if (m_sceneManager != nullptr)
            {
                m_sceneManager->SwitchScene(1);
            }
        }
    }

    void Draw() override
    {
        DrawTexture(ateneoLogoTexture, 50, 225, WHITE);
        DrawText("Ateneo Productions", 220, 275, 50, BLACK);
    }
};
*/

struct Button : public UIComponent
{
    //Texture ateneoLogoTexture = ResourceManager::GetInstance()->GetTexture("ateneo_logo.png");
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

    bool HandleClick(Vector2 clikcPosition) override
    {
        return false;
    }
};

void ToMainGameScene()
{
    //std::cout << "Main Game" << std::endl;
    sceneManager.SwitchScene(2);
}

void ToOptionsScene()
{
    //std::cout << "Options" << std::endl;
    sceneManager.SwitchScene(1);
}

void ToMainMenuScene()
{
    //std::cout << "Main Menu" << std::endl;
    sceneManager.SwitchScene(0);
}

void QuitGame()
{
    std::cout << "Quit" << std::endl;
    CloseWindow();
}

void MasterVolume0()
{
    masterVolume = 0.0f;
    SetMasterVolume(masterVolume);
    std::cout << "Master Volume: " << masterVolume << std::endl;
}

void MasterVolume25()
{
    masterVolume = 0.25f;
    SetMasterVolume(masterVolume);
    std::cout << "Master Volume: " << masterVolume << std::endl;
}

void MasterVolume50()
{
    masterVolume = 0.50f;
    SetMasterVolume(masterVolume);
    std::cout << "Master Volume: " << masterVolume << std::endl;
}

void MasterVolume75()
{
    masterVolume = 0.75f;
    SetMasterVolume(masterVolume);
    std::cout << "Master Volume: " << masterVolume << std::endl;
}

void MasterVolume100()
{
    masterVolume = 1.0f;
    SetMasterVolume(masterVolume);
    std::cout << "Master Volume: " << masterVolume << std::endl;
}

void SFXVolume0()
{
    sfxVolume = 0.0f;
    SetSoundVolume(soundClick, sfxVolume);
    SetSoundVolume(soundCol, sfxVolume);
    std::cout << "SFX Volume: " << sfxVolume << std::endl;
}

void SFXVolume25()
{
    sfxVolume = 0.25f;
    SetSoundVolume(soundClick, sfxVolume);
    SetSoundVolume(soundCol, sfxVolume);
    std::cout << "SFX Volume: " << sfxVolume << std::endl;
}

void SFXVolume50()
{
    sfxVolume = 0.50f;
    SetSoundVolume(soundClick, sfxVolume);
    SetSoundVolume(soundCol, sfxVolume);
    std::cout << "SFX Volume: " << sfxVolume << std::endl;
}

void SFXVolume75()
{
    sfxVolume = 0.75f;
    SetSoundVolume(soundClick, sfxVolume);
    SetSoundVolume(soundCol, sfxVolume);
    std::cout << "SFX Volume: " << sfxVolume << std::endl;
}

void SFXVolume100()
{
    sfxVolume = 1.0f;
    SetSoundVolume(soundClick, sfxVolume);
    SetSoundVolume(soundCol, sfxVolume);
    std::cout << "SFX Volume: " << sfxVolume << std::endl;
}

void BGMVolume0()
{
    bgmVolume = 0.0f;
    SetMusicVolume(musicBGM, bgmVolume);
    std::cout << "BGM Volume: " << bgmVolume << std::endl;
}

void BGMVolume25()
{
    bgmVolume = 0.25f;
    SetMusicVolume(musicBGM, bgmVolume);
    std::cout << "BGM Volume: " << bgmVolume << std::endl;
}

void BGMVolume50()
{
    bgmVolume = 0.50f;
    SetMusicVolume(musicBGM, bgmVolume);
    std::cout << "BGM Volume: " << bgmVolume << std::endl;
}

void BGMVolume75()
{
    bgmVolume = 0.75f;
    SetMusicVolume(musicBGM, bgmVolume);
    std::cout << "BGM Volume: " << bgmVolume << std::endl;
}

void BGMVolume100()
{
    bgmVolume = 1.0f;
    SetMusicVolume(musicBGM, bgmVolume);
    std::cout << "BGM Volume: " << bgmVolume << std::endl;
}

bool CheckIfColliding(Rectangle &objA, Rectangle &objB)
{
    //https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
    bool arg1 = objA.x < objB.x + objB.width;
    bool arg2 = objA.x + objA.width > objB.x;
    bool arg3 = objA.y < objB.y + objB.height;
    bool arg4 = objA.y + objA.height > objB.y;

    if( arg1 && arg2 && arg3 && arg4)
        {
            return true;
        }
    return false;
}

Vector2 GetClosestPointToAABB(Vector2 P, Vector2 aabbMin, Vector2 aabbSize)
{
    Vector2 ret;
    ret.x = Clamp(P.x, aabbMin.x, aabbMin.x + aabbSize.x);
    ret.y = Clamp(P.y, aabbMin.y, aabbMin.y + aabbSize.y);
    return ret;
}

bool CheckForCollision(Vector2 &objPosA, Vector2 &objVelA, Rectangle &objBdsA, Vector2 &objPosB, Rectangle &objBdsB)
{
    Vector2 Q = GetClosestPointToAABB(objPosA, objPosB, {objBdsB.width, objBdsB.height});
    float distSqr = Vector2Distance(objPosA, Q);
    float radiusSqr = objBdsA.width / 2.0f;
    radiusSqr *= radiusSqr;

    if (distSqr <= radiusSqr)
    {
        Vector2 collisionNormal = Vector2Subtract(objPosA, Q);
        Vector2 relativeVelocity = Vector2Subtract(objVelA, {0, 0});
        float normalRelVelocityDot = Vector2DotProduct(collisionNormal, relativeVelocity);

        if(normalRelVelocityDot < 0.0f)
        {
            return true;
        }
    }
    return false;
}

bool HandleAABBCollision(Vector2 &objPosA, Vector2 &objVelA, Rectangle &objBdsA, Vector2 &objPosB, Rectangle &objBdsB)
{
    Vector2 Q = GetClosestPointToAABB(objPosA, objPosB, {objBdsB.width, objBdsB.height});
    float distSqr = Vector2Distance(objPosA, Q);
    float radiusSqr = objBdsA.width / 2.0f;
    radiusSqr *= radiusSqr;

    if (distSqr <= radiusSqr)
    {
        Vector2 collisionNormal = Vector2Subtract(objPosA, Q);
        Vector2 relativeVelocity = Vector2Subtract(objVelA, {0, 0});
        float normalRelVelocityDot = Vector2DotProduct(collisionNormal, relativeVelocity);

        if(normalRelVelocityDot < 0.0f)
        {
            /*if(collisionNormal.x < 0.0f)
            {
                objVelA.x *= -1.0f;
            }
            objVelA.y *= -1.0f;*/
            /*if(collisionNormal.y < 0.0f)
            {
                objVelA.y *= -1.0f;
            }*/
            objVelA = Vector2Add(objVelA, Vector2Scale(collisionNormal, 0.4f));
        }
    }
    return false;
}

class MainMenuScene : public Scene
{
    UILibrary uiLibrary;
    Button mainGameButton, optionsButton, quitButton, mainMenuButtonLabel;
    Texture mainMenuLabel;
    float timer = 5.0f;

public:
    void Begin() override
    {
        mainMenuLabel = ResourceManager::GetInstance()->GetTexture("textures/mainMenuTitle.png");

        uiLibrary.rootContainer.bounds = { 0, 0, (float)windowWidth, (float)windowHeight };

        mainGameButton.text = "Play";
        mainGameButton.bounds = { (float)(windowWidth/2 - 40), (float)(windowHeight/2 + 10), 80, 40 };
        mainGameButton.SetTexture("textures/mainMenuPlay.png");
        mainGameButton.clickHandler = ToMainGameScene;
        uiLibrary.rootContainer.AddChild(&mainGameButton);

        optionsButton.text = "Options";
        optionsButton.bounds = { (float)(windowWidth/2 - 70), (float)(windowHeight/2 + 60), 140, 40 };
        optionsButton.SetTexture("textures/mainMenuOptions.png");
        optionsButton.clickHandler = ToOptionsScene;
        uiLibrary.rootContainer.AddChild(&optionsButton);

        quitButton.text = "Quit";
        quitButton.bounds = { (float)(windowWidth/2 - 40), (float)(windowHeight/2 + 110), 80, 40 };
        quitButton.SetTexture("textures/mainMenuQuit.png");
        quitButton.clickHandler = QuitGame;
        uiLibrary.rootContainer.AddChild(&quitButton);
    }

    void End() override
    {
    }

    void Update() override
    {
        uiLibrary.Update();
    }

    void Draw() override
    {
        DrawTexture(mainMenuLabel, windowWidth/2-160, 60, WHITE);
        uiLibrary.Draw();
    }
};

class OptionsScene : public Scene
{
    UILibrary uiLibrary;
    Button masterSet0, masterSet25, masterSet50, masterSet75, masterSet100;
    Button sfxSet0, sfxSet25, sfxSet50, sfxSet75, sfxSet100;
    Button bgmSet0, bgmSet25, bgmSet50, bgmSet75, bgmSet100;
    Texture masterVolumeLabel, sfxVolumeLabel, bgmVolumeLabel, optionsMenuLabel;
    Button mainMenuButton;


public:
    void Begin() override
    {
        masterVolumeLabel = ResourceManager::GetInstance()->GetTexture("textures/optionsMaster.png");
        sfxVolumeLabel = ResourceManager::GetInstance()->GetTexture("textures/optionsSFX.png");
        bgmVolumeLabel = ResourceManager::GetInstance()->GetTexture("textures/optionsMusic.png");
        optionsMenuLabel = ResourceManager::GetInstance()->GetTexture("textures/optionsMenuLabel.png");

        uiLibrary.rootContainer.bounds = { 0, 0, (float)windowWidth, (float)windowHeight };

        masterSet0.text = "0";
        masterSet0.bounds = {150, 130, 80, 40};
        masterSet0.SetTexture("textures/options0.png");
        masterSet0.clickHandler = MasterVolume0;
        uiLibrary.rootContainer.AddChild(&masterSet0);

        masterSet25.text = "25";
        masterSet25.bounds = {240, 130, 80, 40};
        masterSet25.SetTexture("textures/options25.png");
        masterSet25.clickHandler = MasterVolume25;
        uiLibrary.rootContainer.AddChild(&masterSet25);

        masterSet50.text = "50";
        masterSet50.bounds = {330, 130, 80, 40};
        masterSet50.SetTexture("textures/options50.png");
        masterSet50.clickHandler = MasterVolume50;
        uiLibrary.rootContainer.AddChild(&masterSet50);

        masterSet75.text = "75";
        masterSet75.bounds = {420, 130, 80, 40};
        masterSet75.SetTexture("textures/options75.png");
        masterSet75.clickHandler = MasterVolume75;
        uiLibrary.rootContainer.AddChild(&masterSet75);

        masterSet100.text = "100";
        masterSet100.bounds = {510, 130, 80, 40};
        masterSet100.SetTexture("textures/options100.png");
        masterSet100.clickHandler = MasterVolume100;
        uiLibrary.rootContainer.AddChild(&masterSet100);

        //sfx
        sfxSet0.text = "0";
        sfxSet0.bounds = {150, 180, 80, 40};
        sfxSet0.SetTexture("textures/options0.png");
        sfxSet0.clickHandler = SFXVolume0;
        uiLibrary.rootContainer.AddChild(&sfxSet0);

        sfxSet25.text = "25";
        sfxSet25.bounds = {240, 180, 80, 40};
        sfxSet25.SetTexture("textures/options25.png");
        sfxSet25.clickHandler = SFXVolume25;
        uiLibrary.rootContainer.AddChild(&sfxSet25);

        sfxSet50.text = "50";
        sfxSet50.bounds = {330, 180, 80, 40};
        sfxSet50.SetTexture("textures/options50.png");
        sfxSet50.clickHandler = SFXVolume50;
        uiLibrary.rootContainer.AddChild(&sfxSet50);

        sfxSet75.text = "75";
        sfxSet75.bounds = {420, 180, 80, 40};
        sfxSet75.SetTexture("textures/options75.png");
        sfxSet75.clickHandler = SFXVolume75;
        uiLibrary.rootContainer.AddChild(&sfxSet75);

        sfxSet100.text = "100";
        sfxSet100.bounds = {510, 180, 80, 40};
        sfxSet100.SetTexture("textures/options100.png");
        sfxSet100.clickHandler = SFXVolume100;
        uiLibrary.rootContainer.AddChild(&sfxSet100);

        //bgm
        bgmSet0.text = "0";
        bgmSet0.bounds = {150, 230, 80, 40};
        bgmSet0.SetTexture("textures/options0.png");
        bgmSet0.clickHandler = BGMVolume0;
        uiLibrary.rootContainer.AddChild(&bgmSet0);

        bgmSet25.text = "25";
        bgmSet25.bounds = {240, 230, 80, 40};
        bgmSet25.SetTexture("textures/options25.png");
        bgmSet25.clickHandler = BGMVolume25;
        uiLibrary.rootContainer.AddChild(&bgmSet25);

        bgmSet50.text = "50";
        bgmSet50.bounds = {330, 230, 80, 40};
        bgmSet50.SetTexture("textures/options50.png");
        bgmSet50.clickHandler = BGMVolume50;
        uiLibrary.rootContainer.AddChild(&bgmSet50);

        bgmSet75.text = "75";
        bgmSet75.bounds = {420, 230, 80, 40};
        bgmSet75.SetTexture("textures/options75.png");
        bgmSet75.clickHandler = BGMVolume75;
        uiLibrary.rootContainer.AddChild(&bgmSet75);

        bgmSet100.text = "100";
        bgmSet100.bounds = {510, 230, 80, 40};
        bgmSet100.SetTexture("textures/options100.png");
        bgmSet100.clickHandler = BGMVolume100;
        uiLibrary.rootContainer.AddChild(&bgmSet100);

        mainMenuButton.text = "Back";
        mainMenuButton.bounds = { (float)(windowWidth/2 - 40), (float)(windowHeight/2 + 130), 80, 40 };
        mainMenuButton.SetTexture("textures/optionsBack.png");
        mainMenuButton.clickHandler = ToMainMenuScene;
        uiLibrary.rootContainer.AddChild(&mainMenuButton);

    }

    void End() override
    {

    }
    void Update() override
    {
        uiLibrary.Update();
    }
    void Draw() override
    {
        DrawTexture(masterVolumeLabel, 10, 128, WHITE);
        DrawTexture(sfxVolumeLabel, 10, 178, WHITE);
        DrawTexture(bgmVolumeLabel, 10, 228, WHITE);
        DrawTexture(optionsMenuLabel, (float)(windowWidth/2 - 70), 40, WHITE);
        //DrawText("Options Scene", (float)(windowWidth/2 - 65), 40, 20, WHITE);
        uiLibrary.Draw();
    }
};

class MainGameScene : public Scene
{
    float timer;

    const float timestep = 1.0f / 60;;

    bool noMovingBalls;
    
    int ballNumber, targetNumber, attemptNumber;

    entt::registry registry;

public:
    void Begin() override
    {
        noMovingBalls = true;
        ballNumber = 1;
        targetNumber = 0;
        attemptNumber = 1;
        int randomMusic = GetRandomValue(0, 1);
        if(randomMusic == 0)
        {
            musicBGM = ResourceManager::GetInstance()->GetMusic("soundbgm/bgm1.mp3");
        }
        else
        {
            musicBGM = ResourceManager::GetInstance()->GetMusic("soundbgm/bgm2.mp3");
        }
        SetMusicVolume(musicBGM, bgmVolume);
        SetSoundVolume(soundClick, 0.0f);
        timer = 5.0f;

        for(int i = 0; i < 6; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                SpawnTarget(registry, {10.0f + 1.0f*(j+1) + (j*35), 40.0f + 1.0f*(i+1) + (i*15)}, {35, 15});
                targetNumber++;
            }
        }
        SpawnPlatform(registry, {(float)windowWidth/2 - 40.0f, (float)windowHeight - 45.0f});
        SpawnCircle(registry, {(float)windowWidth/2, (float)windowHeight - 60.0f}, {0.0f, 0.0f});

        //boundary
        SpawnBoundary(registry, {0, 0}, {10.0f, (float)windowHeight});
        SpawnBoundary(registry, {0, 0}, {(float)windowWidth, 10.0f});
        SpawnBoundary(registry, {(float)windowWidth - 10.0f, 0}, {10.0f, (float)windowHeight});
    }

    void End() override
    {
        auto allEnt = registry.view<PositionComponent>();
        for(auto entity : allEnt)
        {
            registry.destroy(entity);
        }

        musicBGM = ResourceManager::GetInstance()->GetMusic("soundbgm/mainmenubgm.mp3");
        SetMusicVolume(musicBGM, bgmVolume);
        SetSoundVolume(soundClick, sfxVolume);
    }

    void Update() override
    {
        timer = timer - GetFrameTime();

        auto platformObj = registry.view<MovementComponent, CollisionComponent>();
        for(auto entity : platformObj)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            MovementComponent& tempObjMovement = registry.get<MovementComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);

            if(tempColType.collisionType == 4)
            {
                if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && !(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)))
                {
                    tempObjMovement.velocity.x = -2.5f;
                }
                else if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && !(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)))
                {
                    tempObjMovement.velocity.x = 2.5f;
                }
                else
                {
                    tempObjMovement.velocity.x = 0.0f;
                }
                if((tempObjPosition.position.x+tempObjMovement.velocity.x > 12.5f) && (tempObjPosition.position.x+ tempColType.bounds.width + tempObjMovement.velocity.x <= windowWidth-12.5f))
                {
                    tempObjPosition.position.x += tempObjMovement.velocity.x;
                }
                tempColType.bounds.x = tempObjPosition.position.x;
                tempColType.bounds.y = tempObjPosition.position.y;
            }
        }

        auto ballObj = registry.view<MovementComponent, CollisionComponent>();
        for (auto entity : ballObj)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            MovementComponent& tempObjMovement = registry.get<MovementComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);

            if(tempColType.collisionType == 0)
            {
                if(IsKeyPressed(KEY_SPACE) && noMovingBalls)
                {
                    noMovingBalls = false;
                    tempObjMovement.velocity.y = -4.5f;
                }

                if(noMovingBalls)
                {
                    if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && !(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)))
                    {
                        tempObjMovement.velocity.x = -2.5f;
                    }
                    else if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && !(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)))
                    {
                        tempObjMovement.velocity.x = 2.5f;
                    }
                    else
                    {
                        tempObjMovement.velocity.x = 0.0f;
                    }
                    if((tempObjPosition.position.x+tempObjMovement.velocity.x > 10.0f) && (tempObjPosition.position.x + tempColType.bounds.width + tempObjMovement.velocity.x <= windowWidth-10.0f))
                    {
                        tempObjPosition.position.x += tempObjMovement.velocity.x;
                    }
                    tempColType.bounds.x = tempObjPosition.position.x;
                    tempColType.bounds.y = tempObjPosition.position.y;
                }
                else
                {
                    tempObjPosition.position = Vector2Add(tempObjPosition.position, tempObjMovement.velocity);
                    tempColType.bounds.x = tempObjPosition.position.x;
                    tempColType.bounds.y = tempObjPosition.position.y;
                }
            }
        }

        for (auto entityA : ballObj)
        {
            PositionComponent& tempObjPositionA = registry.get<PositionComponent>(entityA);
            MovementComponent& tempObjMovementA = registry.get<MovementComponent>(entityA);
            CollisionComponent& tempColTypeA = registry.get<CollisionComponent>(entityA);

            auto boundaryObj = registry.view<CollisionComponent>();
            for (auto entityB : boundaryObj)
            {
                PositionComponent& tempObjPositionB = registry.get<PositionComponent>(entityB);
                CollisionComponent& tempColTypeB = registry.get<CollisionComponent>(entityB);

                if(((tempColTypeA.collisionType == 0) && (tempColTypeB.collisionType == 3)))
                {
                    HandleAABBCollision(tempObjPositionA.position, tempObjMovementA.velocity, tempColTypeA.bounds, tempObjPositionB.position, tempColTypeB.bounds);
                }
            }

            auto targetObjSpec = registry.view<ExplosionPowerupComponent>();
            for (auto entityB : targetObjSpec)
            {
                PositionComponent& tempObjPositionB = registry.get<PositionComponent>(entityB);
                CollisionComponent& tempColTypeB = registry.get<CollisionComponent>(entityB);
                if(((tempColTypeA.collisionType == 0) && (tempColTypeB.collisionType == 1)))
                {
                    if(CheckForCollision(tempObjPositionA.position, tempObjMovementA.velocity, tempColTypeA.bounds, tempObjPositionB.position, tempColTypeB.bounds))
                    {
                        HandleAABBCollision(tempObjPositionA.position, tempObjMovementA.velocity, tempColTypeA.bounds, tempObjPositionB.position, tempColTypeB.bounds);
                        SpawnPowerup(registry, tempObjPositionB.position);
                        registry.destroy(entityB);
                    }
                }
            }

            auto targetObj = registry.view<CollisionComponent>();
            for (auto entityB : targetObj)
            {
                PositionComponent& tempObjPositionB = registry.get<PositionComponent>(entityB);
                CollisionComponent& tempColTypeB = registry.get<CollisionComponent>(entityB);
                if(((tempColTypeA.collisionType == 0) && (tempColTypeB.collisionType == 1)))
                {
                    if(CheckForCollision(tempObjPositionA.position, tempObjMovementA.velocity, tempColTypeA.bounds, tempObjPositionB.position, tempColTypeB.bounds))
                    {
                        HandleAABBCollision(tempObjPositionA.position, tempObjMovementA.velocity, tempColTypeA.bounds, tempObjPositionB.position, tempColTypeB.bounds);
                        registry.destroy(entityB);
                    }
                }
            }

            auto platformObj = registry.view<CollisionComponent>();
            for (auto entityB : platformObj)
            {
                PositionComponent& tempObjPositionB = registry.get<PositionComponent>(entityB);
                CollisionComponent& tempColTypeB = registry.get<CollisionComponent>(entityB);
                if(((tempColTypeA.collisionType == 0) && (tempColTypeB.collisionType == 4)))
                {
                    HandleAABBCollision(tempObjPositionA.position, tempObjMovementA.velocity, tempColTypeA.bounds, tempObjPositionB.position, tempColTypeB.bounds);
                }
            }

            if(tempObjPositionA.position.y > windowHeight)
            {
                registry.destroy(entityA);
                ballNumber--;
            }

        }

        auto powerupObj = registry.view<MovementComponent, CollisionComponent>();
        for(auto entityA : powerupObj)
        {
            PositionComponent& tempObjPositionA = registry.get<PositionComponent>(entityA);
            MovementComponent& tempObjMovementA = registry.get<MovementComponent>(entityA);
            CollisionComponent& tempColTypeA = registry.get<CollisionComponent>(entityA);

            tempObjPositionA.position = Vector2Add(tempObjPositionA.position, tempObjMovementA.velocity);
            tempColTypeA.bounds.x = tempObjPositionA.position.x;
            tempColTypeA.bounds.y = tempObjPositionA.position.y;

            for(auto entityB : platformObj)
            {
                PositionComponent& tempObjPositionB = registry.get<PositionComponent>(entityB);
                MovementComponent& tempObjMovementB = registry.get<MovementComponent>(entityB);
                CollisionComponent& tempColTypeB = registry.get<CollisionComponent>(entityB);
                if((tempColTypeA.collisionType == 2) && (tempColTypeB.collisionType == 4))
                {
                    if(CheckIfColliding(tempColTypeA.bounds, tempColTypeB.bounds))
                    {
                        for(auto entityC : ballObj)
                        {
                            PositionComponent& tempObjPositionC = registry.get<PositionComponent>(entityC);
                            CollisionComponent& tempColTypeC = registry.get<CollisionComponent>(entityC);
                            
                            if(tempColTypeC.collisionType == 0 && !noMovingBalls)
                            {
                                ballNumber += 3;
                                SpawnCircle(registry, tempObjPositionC.position, {RandomNumber(3.0f, 5.0f), RandomNumber(3.0f, 5.0f)});
                                SpawnCircle(registry, tempObjPositionC.position, {RandomNumber(3.0f, 5.0f), RandomNumber(3.0f, 5.0f)});
                                SpawnCircle(registry, tempObjPositionC.position, {RandomNumber(3.0f, 5.0f), RandomNumber(3.0f, 5.0f)});
                            }
                        }
                        registry.destroy(entityA);
                    }
                }
            }

        }

        if(ballNumber == 0)
        {
            noMovingBalls = true;
            for(auto entity : platformObj)
            {
                PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
                MovementComponent& tempObjMovement = registry.get<MovementComponent>(entity);
                CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);

                if(tempColType.collisionType == 4)
                {
                    SpawnCircle(registry, {(float)tempObjPosition.position.x + (tempColType.bounds.width/2.0f), (float)(windowHeight - 60.0f)}, {0.0f, 0.0f} );
                    ballNumber++;
                    attemptNumber++;
                }

            }
        }

        std::cout << "Ball Number: " << ballNumber << std::endl;
        if(IsKeyPressed(KEY_F1))
        {
            m_sceneManager->SwitchScene(0);
        }
        /*if( timer <= 0.0f)
        {
            if(m_sceneManager != nullptr)
            {
                m_sceneManager->SwitchScene(0);
            }
        }*/
    }

    void Draw() override
    {

        auto targetObjNormal = registry.view<CollisionComponent>();
        for(auto entity : targetObjNormal)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);
            if (tempColType.collisionType == 1)
            {
                DrawRectangle(tempColType.bounds.x, tempColType.bounds.y, tempColType.bounds.width, tempColType.bounds.height, GRAY);
            }
        }

        auto targetObjPower = registry.view<ExplosionPowerupComponent>();
        for(auto entity : targetObjPower)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);
            if (tempColType.collisionType == 1)
            {
                DrawRectangle(tempColType.bounds.x, tempColType.bounds.y, tempColType.bounds.width, tempColType.bounds.height, BLUE);
            }
        }

        auto boundaryObj = registry.view<CollisionComponent>();
        for(auto entity : boundaryObj)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);
            if(tempColType.collisionType == 3)
            {
                DrawRectangle(tempColType.bounds.x, tempColType.bounds.y, tempColType.bounds.width, tempColType.bounds.height, GREEN);
            }
        }

        auto platformObj = registry.view<CollisionComponent>();
        for(auto entity : platformObj)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);
            if (tempColType.collisionType == 4)
            {
                DrawRectangle(tempColType.bounds.x, tempColType.bounds.y, tempColType.bounds.width, tempColType.bounds.height, RED);
            }
        }

        auto ballObj = registry.view<CollisionComponent>();
        for(auto entity : ballObj)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);
            if (tempColType.collisionType == 0)
            {
                DrawCircle(tempObjPosition.position.x, tempObjPosition.position.y, tempColType.bounds.width, WHITE);
            }
        }

        auto powerupObj = registry.view<CollisionComponent>();
        for(auto entity : powerupObj)
        {
            PositionComponent& tempObjPosition = registry.get<PositionComponent>(entity);
            CollisionComponent& tempColType = registry.get<CollisionComponent>(entity);
            if (tempColType.collisionType == 2)
            {
                DrawRectangle(tempColType.bounds.x, tempColType.bounds.y, tempColType.bounds.width, tempColType.bounds.height, RED);
            }
        }

        DrawText("Attempt Number: ", 20, windowHeight - 25.0f, 20, BLUE);
        DrawText(std::to_string(attemptNumber).c_str(), 200, windowHeight - 25.0f, 20, BLUE);
    }
};

int main()
{
    InitWindow(windowWidth, windowHeight, "GDEV 41 Final Project");
    SetTargetFPS(60);
    


    //sounds and music
    InitAudioDevice();

    musicBGM = ResourceManager::GetInstance()->GetMusic("soundbgm/mainmenubgm.mp3");
    soundClick = ResourceManager::GetInstance()->GetSound("soundbgm/mouseClick.wav");
    soundCol = ResourceManager::GetInstance()->GetSound("soundbgm/ballCollide.wav");

    SetMasterVolume(masterVolume);
    SetMusicVolume(musicBGM, bgmVolume);
    SetSoundVolume(soundClick, sfxVolume);



    //scenes
    MainMenuScene MainMenuScene;
    MainMenuScene.m_sceneManager = &sceneManager;

    OptionsScene OptionsScene;
    OptionsScene.m_sceneManager = &sceneManager;

    MainGameScene MainGameScene;
    MainGameScene.m_sceneManager = &sceneManager;

    sceneManager.RegisterScene(&MainMenuScene, 0);
    sceneManager.RegisterScene(&OptionsScene, 1);
    sceneManager.RegisterScene(&MainGameScene, 2);

    sceneManager.SwitchScene(0);



    //main loop
    while (!WindowShouldClose())
    {
        PlayMusicStream(musicBGM);
        if(IsMusicStreamPlaying(musicBGM))
        {
            UpdateMusicStream(musicBGM);
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        Scene* activeScene = sceneManager.GetActiveScene();

        if (activeScene != nullptr)
        {
            activeScene->Update();
            activeScene->Draw();
        }

        EndDrawing();
    }

    Scene* activeScene = sceneManager.GetActiveScene();
    if (activeScene != nullptr)
    {
        activeScene->End();
    }



    //unloading resources
    ResourceManager::GetInstance()->UnloadMusic();
    ResourceManager::GetInstance()->UnloadSound();
    CloseAudioDevice();

    ResourceManager::GetInstance()->UnloadTextures();


    CloseWindow();
    return 0;
}
