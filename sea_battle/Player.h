#pragma once
#include "GameField.h"
#include <string>

class Player {
private:
    GameField _gamefield;
    int _ships_counts[4];
    static const int _max_ships_counts[4] = { 4, 3, 2, 1 };

public:
    Player();

    void set_ship(const Ship& ship);
    State set_action(int row, char col);

    std::string show_field(bool hide_ships = false) const;
    bool check_lose() const noexcept;
    bool check_ready() const noexcept;

};

#endif // PLAYER_H