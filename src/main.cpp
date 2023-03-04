#include "Game.hpp"

int main(void) {
    Game game{1920, 1080, "Game Name"};
    while (!game.Close()) {
        game.Tick();
    }
    game.Close();
    return 0;
}