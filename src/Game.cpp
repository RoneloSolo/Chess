#include "Game.hpp"

#include "Board.hpp"
#include <raylib.h>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

static RenderTexture2D target;
static Vector2 windowSize;
static Vector2 gameSize;

static float scale;

Game::Game(int width, int height, const char* title) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);
    InitWindow(width, height, title);
    SetWindowMinSize(320, 240);

    pieceTexture = LoadTexture("sprite/pieces.png"); 

    windowSize = Vector2{(float)width, (float)height};
    gameSize = windowSize;

    target = LoadRenderTexture(gameSize.x, gameSize.y);

    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    scale = MIN(windowSize.x/gameSize.x, windowSize.y/gameSize.y);
    
    GenerateBoard(gameSize.x, gameSize.y);
}

Game::~Game() noexcept {
    UnloadRenderTexture(target);
    CloseWindow();
}

bool Game::Close() const {
    return WindowShouldClose();
}

void Game::Draw() {
    BeginTextureMode(target);
        ClearBackground(BLACK);
    
        DrawBoard();
        DrawPieces();

    EndTextureMode();
    
    BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                        (Rectangle){ (windowSize.x - (gameSize.x*scale))*0.5f, (windowSize.y - (gameSize.y*scale))*0.5f,
                        gameSize.x*scale, gameSize.y*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}

void Game::Update() {
    if(IsWindowResized()) {
        windowSize = Vector2{(float)GetScreenWidth(), (float)GetScreenHeight()};
        scale = MIN(windowSize.x/gameSize.x, windowSize.y/gameSize.y);
    }
}

void Game::PhysicsUpdate(){
}

void Game::Tick() {
    Update();
    PhysicsUpdate();
    Draw();
}