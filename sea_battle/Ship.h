#pragma once
#include "Position.h"

enum Direction { Horizontal, Vertical };

class Ship {
private:
    int _size;
    Position _coord;
    Direction _direction;

    static bool Correct_Input(int size, const Position& coord, Direction dir) noexcept;

public:
    Ship(int size, const Position& coord, Direction direction);
    Ship(int size, const Position& coord);
    Ship(int size, char direction, int row, char col);

    Ship() = delete;
    Ship(const Ship&) = delete;

    int size() const noexcept;
    Direction direction() const noexcept;
    int row() const noexcept;
    int col() const noexcept;

    void rotate();

};
