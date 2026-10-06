#include "pch.h"
#include "Player.h"
#include <iostream>
#include <stdexcept>

const int Player::_max_ships_counts[4] = { 4, 3, 2, 1 };

Player::Player() : _any_ship_placed(false) {
    for (int i = 0; i < 4; ++i) {
        _ships_counts[i] = 0;
    }
}

void Player::set_ship(const Ship& ship) {
    const int size = ship.size();
    if (size < 1 || size > 4) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    if (_ships_counts[size - 1] >= _max_ships_counts[size - 1]) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    _gamefield.set(ship);
    ++_ships_counts[size - 1];
    _any_ship_placed = true;
}


State Player::set_action(int row, char col) {
    State s = _gamefield.set(row, col);

    switch (s) {
    case BoatDestroyed:
        --_ships_counts[0];
        break;
    case DestroyersDestroyed:
        --_ships_counts[1];
        break;
    case CruisersDestroyed:
        --_ships_counts[2];
        break;
    case BattleshipDestroyed:
        --_ships_counts[3];
        break;
    default:
        break;
    }

    return s;
}

void Player::show_field(bool hide_ships) const {
    std::cout << to_string(_gamefield, !hide_ships);
    std::cout << '\n';
    std::cout << "Ships Left:\n";

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::cout << '*';
        }
        std::cout << " - " << _ships_counts[i];
        if (i < 3) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

bool Player::check_lose() const noexcept {
    if (!_any_ship_placed) {
        return false;
    }
    return _ships_counts[0] == 0
        && _ships_counts[1] == 0
        && _ships_counts[2] == 0
        && _ships_counts[3] == 0;
}

bool Player::check_ready() const noexcept {
    return _ships_counts[0] == _max_ships_counts[0]
        && _ships_counts[1] == _max_ships_counts[1]
        && _ships_counts[2] == _max_ships_counts[2]
        && _ships_counts[3] == _max_ships_counts[3];
}