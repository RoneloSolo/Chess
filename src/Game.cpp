#include "Game.hpp"
#include <raylib.h>

Game::Game(int width, int height, const char* title) {
    SetTargetFPS(60);
    InitWindow(width, height, title);
}

Game::~Game() noexcept {
    CloseWindow();
}

bool Game::Close() const {
    return WindowShouldClose();
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}

void Game::Update() {
}

void Game::PhysicsUpdate(){
}

void Game::Tick() {
    Update();
    PhysicsUpdate();
    Draw();
}