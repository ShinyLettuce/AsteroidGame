#include "Level.h"
#include <stack>

enum class GAME_STATE
{
    MAIN_MENU,
    GAME
};

std::stack <GAME_STATE>game_state;

void main_menu(Level& l)
{
    if (IsKeyPressed(KEY_X))
    {
        l.level_init();
        PlaySoundMulti(Media::menusound);
        game_state.push(GAME_STATE::GAME);
    }
    
    l.update();
    l.render();
    
    DrawText("Survive", 135, 120, 48, RED);
    DrawText("Space", 150, 168, 48, RED);
    DrawText("press x to start", 160, 216, 16, WHITE);

}

void game_screen(Level& l)
{
    l.update();
    l.render();

    if (l.mario.dead == true)
    {
        game_state.pop();
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 450;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Survive in space");
    Media::media_init();
    Level space;
    game_state.push(GAME_STATE::MAIN_MENU);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    { 

        BeginDrawing();

        switch (game_state.top())
        {
            case GAME_STATE::MAIN_MENU:
                main_menu(space);
                break;
            case GAME_STATE::GAME:
                game_screen(space);
                break;
        }

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}