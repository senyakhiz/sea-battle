#include "pch.h"
#include "Ship.h"
#include <stdexcept>

bool Ship::is_space_char(char c) const noexcept {
        return c == ' ' || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r';
}

bool Ship::is_digit_char(char c) const noexcept {
        return c >= '0' && c <= '9';
}

bool Ship::direction_from_char(char c, Direction& d) const noexcept {
        if (c == 'H' || c == 'h') { d = Horizontal; return true; }
        if (c == 'V' || c == 'v') { d = Vertical;   return true; }
        return false;
}

bool is_collision(int size, Position position, Direction direction) noexcept {
    if (size < 1 || size > 4) {
        return false;
    }

    const int row = position.get_row();
    const int col = position.get_col();

    if (direction == Horizontal) {
        return col - (size - 1) >= 1;
    }
    else {
        return row - (size - 1) >= 1;
    }
}

Ship::Ship(int size, Position position, Direction direction) {
    if (!is_collision(size, position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
    _position = position;
    _direction = direction;
}

Ship::Ship(int size, char direction, int row, char col) {
    Direction dir;
    if (!direction_from_char(direction, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    Position pos(row, col);
    if (!is_collision(size, pos, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
    _position = pos;
    _direction = dir;
}

Ship::Ship(const std::string& str) {
    if (!parse(str, *this)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}


int Ship::size() const noexcept {
    return _size;
}

int Ship::row() const noexcept {
    return _position.get_row();
}

int Ship::col() const noexcept {
    return _position.get_col();
}

Position Ship::position() const noexcept {
    return _position;
}

Direction Ship::direction() const noexcept {
    return _direction;
}

void Ship::size(int size) {
    if (!is_collision(size, _position, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
}

void Ship::row(int row) {
    Position p(row, _position.get_col());
    if (!is_collision(_size, p, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = p;
}

void Ship::col(int col) {
    Position p(_position.get_row(), col);
    if (!is_collision(_size, p, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = p;
}

void Ship::col(char col) {
    Position p(_position.get_row(), col);
    if (!is_collision(_size, p, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = p;
}

void Ship::direction(Direction direction) {
    if (!is_collision(_size, _position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = direction;
}

void Ship::direction(char direction) {
    Direction dir;
    if (!direction_from_char(direction, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    if (!is_collision(_size, _position, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = dir;
}

void Ship::position(Position position) {
    if (!is_collision(_size, position, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = position;
}

bool parse(const std::string& str, Ship& ship) noexcept {
    std::size_t i = 0;
    const std::size_t n = str.size();

    while (i < n && ship.is_space_char(str[i])) ++i;

    if (i >= n || !ship.is_digit_char(str[i])) return false;
    int size = 0;
    while (i < n && ship.is_digit_char(str[i])) {
        size = size * 10 + (str[i] - '0');
        ++i;
    }

    while (i < n && ship.is_space_char(str[i])) ++i;

    if (i >= n) return false;
    Direction dir;
    if (!ship.direction_from_char(str[i], dir)) return false;
    ++i;

    while (i < n && ship.is_space_char(str[i])) ++i;

    std::string pos_str = str.substr(i);
    Position pos(1, 1);
    if (!parse(pos_str, pos)) return false;

    if (!is_collision(size, pos, dir)) return false;

    ship._size = size;
    ship._position = pos;
    ship._direction = dir;
    return true;
}