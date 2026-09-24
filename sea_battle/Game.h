#pragma once
#include "Player.h"
#include <string>

class Game {
private:
    Player _user;
    Player _computer;

    void user_init(std::string input);
    void computer_init(std::string input);
    State user_move(std::string input);
    State computer_move();
    bool is_end() const noexcept;
    void show_game_window() const;

public:
    Game();
    void start();
};