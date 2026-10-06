#pragma once
#include "GameField.h"

class Player {
private:
    GameField _gamefield;
    int _ships_counts[4];
    bool _any_ship_placed;

    static const int _max_ships_counts[4];

public:
    Player();

    void set_ship(const Ship& ship);
    State set_action(int row, char col);
    void show_field(bool hide_ships = false) const;
    bool check_lose() const noexcept;
    bool check_ready() const noexcept;
};