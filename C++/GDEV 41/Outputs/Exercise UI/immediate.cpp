#include <raylib.h>
#include <raymath.h>
//#include "D:\Raymond Nojadera\Coding\GDEV 41\raylib\raymath.h"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Struct to encapsulate our UI library
struct UiLibrary
{
    // ID of the currently hot widget
    int hot = -1;

    // ID of the currently active widget
    int active = -1;

    // Creates a button with the specified text and bounds
    // Returns true if this button was clicked in this frame
    bool Button(int id, const std::string& text, const Rectangle& bounds, const Color color)
    {
        bool result = false;

        // If this button is the currently active widget, that means
        // the user is currently interacting with this widget
        if (id == active)
        {
            // If the user released the mouse button while we are active,
            // register as a click
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                // Make sure that we are still the hot widget
                // (User might have dragged mouse to another widget, in which case we will not count as a button click)
                if (id == hot)
                {
                    result = true;
                }

                // Set ourselves to not be active anymore
                active = -1;
            }
        }

        // If we are currently the hot widget
        if (id == hot)
        {
            // If the user pressed the left mouse button, that means the user started
            // interacting with this widget, so we set this widget as active
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                active = id;
            }
        }

        DrawRectangleRec(bounds, GRAY);

        // If the mouse cursor is hovering within our boundaries
        if (CheckCollisionPointRec(GetMousePosition(), bounds))
        {
            // Set this widget to be the hot widget
            hot = id;
            DrawRectangleRec(bounds, RED);
        }
        // If the mouse cursor is not on top of this widget, and this widget
        // was previously the hot widget, set the hot widget to -1
        // We check if this widget was the previously hot widget since there is a possibility that
        // the hot widget is now a different widget, and we don't want to overwrite that with -1
        else if (hot == id)
        {
            hot = -1;
        }

        // Draw our button regardless of what happens
        if (result)
        {
            DrawText(text.c_str(), bounds.x, bounds.y, 14, color);
        }
        else
        {
            DrawText(text.c_str(), bounds.x, bounds.y, 14, BLACK);
        }

        return result;
    }
    bool CheckBox(int id, bool activeStatus, const Rectangle& checkboxBounds)
    {
        bool result = false;
        bool isActive = activeStatus;
        std::string activeText = "Disable Save";
        std::string inactiveText = "Enable Save";

        if (id == active)
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (id == hot)
                {
                    result = true;
                }
                active = -1;
            }
        }

        if (id == hot)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                active = id;
            }
        }

        if (CheckCollisionPointRec(GetMousePosition(), checkboxBounds))
        {
            hot = id;
        }

        else if (hot == id)
        {
            hot = -1;
        }

        if (isActive)
        {
            DrawRectangleRec(checkboxBounds, GRAY);
            DrawText(activeText.c_str(), checkboxBounds.x + checkboxBounds.width + 10, checkboxBounds.y + 15, 14, BLACK);
        }
        else
        {
            DrawRectangleRec(checkboxBounds, WHITE);
            DrawText(inactiveText.c_str(), checkboxBounds.x + checkboxBounds.width + 10, checkboxBounds.y + 15, 14, BLACK);
        }
        DrawRectangleLines(checkboxBounds.x, checkboxBounds.y, checkboxBounds.width, checkboxBounds.height, BLACK);

        return result;
    }
};

int main()
{
    int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Immediate Mode");
    SetTargetFPS(60);
    bool isActive = false;

    UiLibrary uiLibrary;

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();
        if (uiLibrary.Button(0, "Hello!", { 10, 10, 80, 40 }, LIME))
        {
            ClearBackground(SKYBLUE);
        }
        if (uiLibrary.Button(1, "Hi!", { 100, 10, 80, 40 }, SKYBLUE))
        {
            ClearBackground(LIME);
        }
        if (uiLibrary.CheckBox(2, isActive, { 10, 60, 80, 40 }))
        {
            isActive = !isActive;
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
