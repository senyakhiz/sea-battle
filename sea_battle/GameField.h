#pragma once
#include "Ship.h"
#include <string>

enum State {
    Missed,
    BoatDestroyed,
    DestroyersDestroyed,
    CruisersDestroyed,
    BattleshipDestroyed,
    Hit
};

class GameField {
    char** _field;
    const int _n;
    const int _m;

    int check_destroy(int row, int col) const noexcept;

public:
    GameField();
    ~GameField();

    GameField(const GameField&) = delete;
    GameField& operator=(const GameField&) = delete;

    void set(const Ship& ship);
    State set(int row, char col);

private:
    friend std::string to_string(const GameField& field, bool show_ships = false);
    friend bool is_collision(const GameField& field, const Ship& ship);
};