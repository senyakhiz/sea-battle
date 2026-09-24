#include "Game.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Game game;
        game.start();
    }
    catch (const std::logic_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}