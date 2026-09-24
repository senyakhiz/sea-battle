#include "Game.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Game::Game() {}

void Game::user_init(std::string input) {
    std::istringstream ss(input);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty()) continue;
        Ship ship(line);
        _user.set_ship(ship);
    }
    if (!_user.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

void Game::computer_init(std::string input) {
    std::istringstream ss(input);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty()) continue;
        Ship ship(line);
        _computer.set_ship(ship);
    }
    if (!_computer.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

State Game::user_move(std::string input) {
    std::istringstream ss(input);
    int row;
    char col;
    if (!(ss >> row >> col)) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    return _computer.set_action(row, col);
}

State Game::computer_move() {
    for (int i = 1; i <= 10; ++i) {
        char col = static_cast<char>('A' + i - 1);
        try {
            return _user.set_action(i, col);
        }
        catch (const std::logic_error&) {
        }
    }
    for (int i = 1; i <= 10; ++i) {
        char col = static_cast<char>('A' + (10 - i));
        try {
            return _user.set_action(i, col);
        }
        catch (const std::logic_error&) {
        }
    }
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            char col = static_cast<char>('A' + j - 1);
            try {
                return _user.set_action(i, col);
            }
            catch (const std::logic_error&) {
            }
        }
    }
    return Missed;
}

bool Game::is_end() const noexcept {
    return _user.check_lose() || _computer.check_lose();
}

void Game::show_game_window() const {
    std::cout << "= COMPUTER GAME FIELD =" << std::endl;
    std::cout << std::endl;
    std::cout << _computer.show_field(true);
    std::cout << std::endl;
    std::cout << "=== YOUR PLAY FIELD ===" << std::endl;
    std::cout << std::endl;
    std::cout << _user.show_field(false);
}

void Game::start() {
    std::string line, input, user_ships, computer_ships;

    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        user_ships += line + "\n";
    }
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        computer_ships += line + "\n";
    }

    user_init(user_ships);
    computer_init(computer_ships);

    show_game_window();

    while (!is_end()) {
        State st;

        do {
            if (!std::getline(std::cin, input)) {
                return;
            }
            if (input.empty()) continue;
            st = user_move(input);
        } while (st != Missed);

        if (is_end()) break;

        do {
            st = computer_move();
        } while (st != Missed);
    }

    show_game_window();

    if (_computer.check_lose()) {
        std::cout << "USER WIN!" << std::endl;
    }
    else {
        std::cout << "COMPUTER WIN!" << std::endl;
    }
}