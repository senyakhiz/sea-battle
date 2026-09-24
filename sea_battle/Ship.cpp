#include "Ship.h"
#include <sstream>
#include <cctype>
#include <stdexcept>

bool is_collision(int size, Position position, Direction direction) {
    if (size < 1 || size > 4) {
        return false;
    }
    if (!is_collision(position.row())) {
        return false;
    }
    if (!is_collision(position.char_col())) {
        return false;
    }
    if (direction == Horizontal) {
        return is_collision(position.col() + size - 1);
    }
    return is_collision(position.row() + size - 1);
}

bool parse(const std::string& str, Ship& ship) {
    std::istringstream ss(str);
    int size;
    char direction;
    std::string pos_str;

    if (!(ss >> size)) {
        return false;
    }
    if (!(ss >> direction)) {
        return false;
    }
    if (!(ss >> pos_str)) {
        return false;
    }

    Direction dir;
    if (direction == 'H' || direction == 'h') {
        dir = Horizontal;
    }
    else if (direction == 'V' || direction == 'v') {
        dir = Vertical;
    }
    else {
        return false;
    }

    Position pos(1, 1);
    if (!parse(pos_str, pos)) {
        return false;
    }

    if (!is_collision(size, pos, dir)) {
        return false;
    }

    ship._size = size;
    ship._position = pos;
    ship._direction = dir;
    return true;
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
    if (direction == 'H' || direction == 'h') {
        dir = Horizontal;
    }
    else if (direction == 'V' || direction == 'v') {
        dir = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    if (!is_collision(row) || !is_collision(col)) {
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
    _size = 1;
    _position = Position(1, 1);
    _direction = Horizontal;
    if (!parse(str, *this)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

int Ship::size() const noexcept {
    return _size;
}

int Ship::row() const noexcept {
    return _position.row();
}

int Ship::col() const noexcept {
    return _position.col();
}

Position Ship::position() const noexcept {
    return _position;
}

Direction Ship::direction() const noexcept {
    return _direction;
}

void Ship::size(int value) {
    if (!is_collision(value, _position, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = value;
}

void Ship::row(int value) {
    if (!is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    Position p(value, _position.col());
    if (!is_collision(_size, p, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = p;
}

void Ship::col(int value) {
    if (!is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    Position p(_position.row(), value);
    if (!is_collision(_size, p, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = p;
}

void Ship::col(char value) {
    if (!is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    int c = std::toupper(static_cast<unsigned char>(value)) - 'A' + 1;
    Position p(_position.row(), c);
    if (!is_collision(_size, p, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = p;
}

void Ship::direction(Direction value) {
    if (!is_collision(_size, _position, value)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = value;
}

void Ship::direction(char value) {
    Direction dir;
    if (value == 'H' || value == 'h') {
        dir = Horizontal;
    }
    else if (value == 'V' || value == 'v') {
        dir = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    if (!is_collision(_size, _position, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = dir;
}

void Ship::position(Position value) {
    if (!is_collision(_size, value, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = value;
}