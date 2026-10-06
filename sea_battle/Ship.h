#pragma once
#pragma once
#include <string>
#include "Position.h"

enum Direction { Horizontal, Vertical };

class Ship {
private:
    int _size;
    Position _position;
    Direction _direction;

    bool is_space_char(char c) const noexcept;
    bool is_digit_char(char c) const noexcept;
    bool direction_from_char(char c, Direction& d) const noexcept;

public:
    Ship(int size, Position position, Direction direction);
    Ship(int size, char direction, int row, char col);
    Ship(const std::string& str);

    int size() const noexcept;
    int row() const noexcept;
    int col() const noexcept;
    Position position() const noexcept;
    Direction direction() const noexcept;

    void size(int size);
    void row(int row);
    void col(int col);
    void col(char col);
    void direction(Direction direction);
    void direction(char direction);
    void position(Position position);

private:
    friend bool parse(const std::string& str, Ship& ship) noexcept;
    friend bool is_collision(int size, Position position, Direction direction) noexcept;
};