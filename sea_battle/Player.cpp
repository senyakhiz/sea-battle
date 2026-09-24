#include "Player.h"
#include <stdexcept>
#include <string>

const int Player::_max_ships_counts[4];

Player::Player() {
    for (int i = 0; i < 4; ++i) {
        _ships_counts[i] = 0;
    }
}

void Player::set_ship(const Ship& ship) {
    int idx = ship.size() - 1;
    if (idx < 0 || idx > 3) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    if (_ships_counts[idx] >= _max_ships_counts[idx]) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    _gamefield.set(ship);
    _ships_counts[idx]++;
}

State Player::set_action(int row, char col) {
    State st = _gamefield.set(row, col);
    switch (st) {
    case BoatDestroyed:
        _ships_counts[0]--;
        break;
    case DestroyersDestroyed:
        _ships_counts[1]--;
        break;
    case CruisersDestroyed:
        _ships_counts[2]--;
        break;
    case BattleshipDestroyed:
        _ships_counts[3]--;
        break;
    default:
        break;
    }
    return st;
}

std::string Player::show_field(bool hide_ships) const {
    std::string result = to_string(_gamefield, hide_ships);
    result += "\nShips Left:\n";
    result += "* - " + std::to_string(_ships_counts[0]);
    result += " ** - " + std::to_string(_ships_counts[1]);
    result += " *** - " + std::to_string(_ships_counts[2]);
    result += " **** - " + std::to_string(_ships_counts[3]);
    result += "\n";
    return result;
}

bool Player::check_lose() const noexcept {
    for (int i = 0; i < 4; ++i) {
        if (_ships_counts[i] != 0) return false;
    }
    return true;
}

bool Player::check_ready() const noexcept {
    for (int i = 0; i < 4; ++i) {
        if (_ships_counts[i] != _max_ships_counts[i]) return false;
    }
    return true;
}