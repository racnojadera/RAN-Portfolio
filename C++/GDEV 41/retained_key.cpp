#include <raylib.h>
#include <raymath.h>

#include <functional> // Required for std::function
#include <iostream>
#include <string>
#include <vector>

bool lockScreenSize = false;

// Generic UI component
struct UIComponent
{
    // Rectangle reprsenting the bounds of the UI component
    Rectangle bounds;

    // Draws this particular UI component
    // Set as abstract so that child widgets will implement this for us
    virtual void Draw() = 0;

    // Handles a mouse click event
    // Set as abstract so that child widgets will implement this for us
    // Returns a boolean indicating whether this UI component successfully handled the event
    virtual bool HandleClick(Vector2 clickPosition) = 0;
};

// Generic UI component that can contain other UI components as children
struct UIContainer : public UIComponent
{
    std::vector<UIComponent*> children;

    // Adds a child to the container
    void AddChild(UIComponent* child)
    {
        children.push_back(child);
    }

    // Draw
    void Draw() override
    {
        // Since we are just a container for other widgets, we simply
        // call the draw function of other widgets.
        // As a side effect, this results in a pre-order traversal when we also draw child widgets that are also containers
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->Draw();
        }
    }

    // Handles a mouse click event
    // Returns a boolean indicating whether this UI component successfully handled the event
    bool HandleClick(Vector2 clickPosition) override
    {
        for (size_t i = children.size(); i > 0; --i)
        {
            if (children[i - 1]->HandleClick(clickPosition))
            {
                return true;
            }
        }

        return false;
    }
};

// Button widget
struct Button : public UIComponent
{
    // Text displayed by the button
    std::string text;

    // Function to call when the button is clicked
    std::function<void()> clickHandler;

    // Draw
    void Draw() override
    {
        DrawRectangleRec(bounds, GRAY);
        DrawText(text.c_str(), bounds.x, bounds.y, 14, BLACK);
    }

    // Handle mouse click
    // Returns a boolean indicating whether this UI component successfully handled the event
    bool HandleClick(Vector2 clickPosition) override
    {
        // Check if the mouse click position is within our bounds
        if (CheckCollisionPointRec(clickPosition, bounds))
        {
            // Call the function assigned to this button
            if (clickHandler)
            {
                clickHandler();
            }

            return true;
        }

        return false;
    }
};

// Text display widget
struct Label : public UIComponent
{
    // Text to be displayed
    std::string text;

    // Draw
    void Draw() override
    {
        DrawText(text.c_str(), bounds.x, bounds.y, 14, BLACK);
    }

    // Handle mouse click
    // Returns a boolean indicating whether this UI component successfully handled the event
    bool HandleClick(Vector2 clickPosition) override
    {
        // Always return false since we're not going to handle click events for this particular widget
        // (unless you have to)
        return false;
    }
};

struct CheckBox : public UIComponent
{
    bool isChecked;
    std::string descriptionText;

    // Draw
    void Draw() override
    {
        int fontSize = 14;

        DrawRectangle(bounds.x, bounds.y, bounds.height, bounds.height, BLACK);
        DrawRectangle(bounds.x + 1, bounds.y + 1, bounds.height - 2, bounds.height - 2, WHITE);
        if (isChecked)
        {
            DrawRectangle(bounds.x + 2, bounds.y + 2, bounds.height - 4, bounds.height - 4, BLACK);
        }

        DrawText(descriptionText.c_str(), bounds.x + bounds.height + 4, bounds.y + (bounds.height - fontSize) / 2, fontSize, BLACK);
    }

    // Handle mouse click
    // Returns a boolean indicating whether this UI component successfully handled the event
    bool HandleClick(Vector2 clickPosition) override
    {
        if (CheckCollisionPointRec(clickPosition, bounds))
        {
            isChecked = !isChecked;
            return true;
        }

        return false;
    }
};

// Struct to encapsulate our UI library
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

void ChangeResolution1()
{
    if (lockScreenSize)
    {
        return;
    }

    SetWindowSize(800, 600);
}

void ChangeResolution2()
{
    if (lockScreenSize)
    {
        return;
    }

    SetWindowSize(1280, 720);
}

void ChangeResolution3()
{
    if (lockScreenSize)
    {
        return;
    }
    SetWindowSize(1366, 768);
}

int main()
{
    int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Retained Mode");
    SetTargetFPS(60);

    UILibrary uiLibrary;

    uiLibrary.rootContainer.bounds = { 10, 10, 600, 500 };

    Button button;
    button.text = "800 x 600";
    button.bounds = { 120, 10, 80, 40 };
    button.clickHandler = ChangeResolution1;
    uiLibrary.rootContainer.AddChild(&button);

    Button button2;
    button2.text = "1280 x 720";
    button2.bounds = { 210, 10, 80, 40 };
    button2.clickHandler = ChangeResolution2;
    uiLibrary.rootContainer.AddChild(&button2);

    Button button3;
    button3.text = "1366 x 768";
    button3.bounds = { 300, 10, 80, 40 };
    button3.clickHandler = ChangeResolution3;
    uiLibrary.rootContainer.AddChild(&button3);

    Label label;
    label.text = "Resolution";
    label.bounds = { 10, 20, 100, 40 };
    uiLibrary.rootContainer.AddChild(&label);

    CheckBox checkBox;
    checkBox.isChecked = false;
    checkBox.descriptionText = "Lock screen size";
    checkBox.bounds = { 10, 70, 150, 20 };
    uiLibrary.rootContainer.AddChild(&checkBox);

    while (!WindowShouldClose())
    {
        uiLibrary.Update();

        lockScreenSize = checkBox.isChecked;

        ClearBackground(WHITE);
        BeginDrawing();
        uiLibrary.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
