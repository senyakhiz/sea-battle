#include "pch.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Game::Game() : _move_index(0) {}

void Game::user_init(std::string input) {
    std::stringstream ss(input);
    std::string line;

    while (std::getline(ss, line)) {
        if (line.empty()) continue;

        try {
            _user.set_ship(Ship(line));
        }
        catch (const std::exception& e) {
            std::cerr << "[ИГРОК] ошибка на строке \"" << line
                << "\": " << e.what() << '\n';
            throw;
        }
    }

    if (!_user.check_ready()) {
        std::cerr << "[ИГРОК] расстановка неполная. Нужно: 4x1, 3x2, 2x3, 1x4.\n";
        throw std::logic_error("Invalid input: incorrect field");
    }
}

void Game::computer_init(std::string input) {
    std::stringstream ss(input);
    std::string line;

    while (std::getline(ss, line)) {
        if (line.empty()) continue;

        try {
            _computer.set_ship(Ship(line));
        }
        catch (const std::exception& e) {
            std::cerr << "[КОМПЬЮТЕР] ошибка на строке \"" << line
                << "\": " << e.what() << '\n';
            throw;
        }
    }

    if (!_computer.check_ready()) {
        std::cerr << "[КОМПЬЮТЕР] расстановка неполная.\n";
        throw std::logic_error("Invalid input: incorrect field");
    }
}

State Game::user_move(std::string input) {
    Position pos(1, 1);
    if (!parse(input, pos)) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    return _computer.set_action(pos.get_row(), pos.get_char_col());
}

State Game::computer_move() {
    while (_move_index < 100) {
        const int idx = _move_index++;

        int row = 1;
        int col = 1;

        if (idx < 10) {
            row = idx + 1;
            col = idx + 1;
        }
        else if (idx < 20) {
            const int k = idx - 10;
            row = k + 1;
            col = 10 - k;
        }
        else {
            const int k = idx - 20;
            int count = 0;
            bool found = false;
            for (int i = 1; i <= 10 && !found; ++i) {
                for (int j = 1; j <= 10; ++j) {
                    if (i == j || i + j == 11) {
                        continue;
                    }
                    if (count == k) {
                        row = i;
                        col = j;
                        found = true;
                        break;
                    }
                    ++count;
                }
            }
        }

        return _user.set_action(row, static_cast<char>('A' + col - 1));
    }

    throw std::logic_error("Invalid input: incorrect move");
}

bool Game::is_end() const noexcept {
    return _user.check_lose() || _computer.check_lose();
}

void Game::show_game_window() const {
    std::cout << "= COMPUTER GAME FIELD =\n\n";
    _computer.show_field(true);
    std::cout << '\n';

    std::cout << "=== YOUR PLAY FIELD ===\n\n";
    _user.show_field(false);
    std::cout << '\n';
}

void Game::start() {
    std::string line;
    std::string user_ships;
    std::string computer_ships;

    std::cout << "=== Введите корабли ИГРОКА (10 строк, пустая строка — конец) ===\n";
    while (std::getline(std::cin, line) && !line.empty()) {
        user_ships += line + "\n";
    }

    std::cout << "=== Введите корабли КОМПЬЮТЕРА (10 строк, пустая строка — конец) ===\n";
    while (std::getline(std::cin, line) && !line.empty()) {
        computer_ships += line + "\n";
    }

    user_init(user_ships);
    computer_init(computer_ships);

    std::cout << "\n=== Игра началась ===\n";
    show_game_window();

    while (!is_end()) {
        std::getline(std::cin, line);
        State s = user_move(line);
        show_game_window();

        while (s != Missed && !is_end()) {
            std::getline(std::cin, line);
            s = user_move(line);
            show_game_window();
        }

        if (is_end()) break;

        s = computer_move();
        show_game_window();

        while (s != Missed && !is_end()) {
            s = computer_move();
            show_game_window();
        }
    }

    if (_computer.check_lose()) {
        std::cout << "USER WIN!\n";
    }
    else {
        std::cout << "COMPUTER WIN!\n";
    }
}