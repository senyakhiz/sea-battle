#include "Ship.h"
#include <stdexcept>
#include <cctype>

bool Ship::Correct_Input(int size, const Position& coord, Direction dir) noexcept {
    if (size < 1 || size > 4) {
        return false;
    }
    int r = coord.row();
    int c = coord.col();
    if (dir == Horizontal) {
        return (c + size - 1 <= 10) && (r >= 1 && r <= 10);
    }
    else {
        return (r + size - 1 <= 10) && (c >= 1 && c <= 10);
    }
}

Ship::Ship(int size, const Position& coord, Direction direction) {
    if (!isValid(size, coord, direction)) {
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }
    _size = size;
    _coord = coord;
    _direction = direction;
}

Ship::Ship(int size, const Position& coord) {
    if (!Correct_Input(size, coord, Horizontal)) {
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }
    _size = size;
    _coord = coord;
    _direction = Horizontal;
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
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }

    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(col)));
    if (upper < 'A' || upper > 'J') {
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }
    int c = upper - 'A' + 1;

    if (row < 1 || row > 10 || c < 1 || c > 10) {
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }

    Position coord(row, c);
    if (!Correct_Input(size, coord, dir)) {
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }

    _size = size;
    _coord = coord;
    _direction = dir;
}

int Ship::size() const noexcept {
    return _size;
}

Direction Ship::direction() const noexcept {
    return _direction;
}

int Ship::row() const noexcept {
    return _coord.row();
}

int Ship::col() const noexcept {
    return _coord.col();
}

void Ship::rotate() {
    Direction new_dir = (_direction == Horizontal) ? Vertical : Horizontal;
    if (Correct_Input(_size, _coord, new_dir)) {
        throw std::logic_error("Invalid input: incorrect ship parameters");
    }
    _direction = new_dir;
}