#include "Position.h"
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cstdlib>

const int Position::_max_row;
const int Position::_max_col;

bool is_collision(int row) {
    return row >= 1 && row <= Position::_max_row;
}

bool is_collision(char col) {
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(col)));
    if (upper < 'A' || upper > 'Z') {
        return false;
    }
    int c = upper - 'A' + 1;
    return c >= 1 && c <= Position::_max_col;
}

bool parse(const std::string& str, Position& pos) {
    std::istringstream ss(str);
    int row;
    char col;

    if (!(ss >> row)) {
        return false;
    }
    ss >> std::ws;
    if (!(ss >> col)) {
        return false;
    }

    if (!is_collision(row) || !is_collision(col)) {
        return false;
    }

    pos._row = row;
    pos._col = std::toupper(static_cast<unsigned char>(col)) - 'A' + 1;
    return true;
}

Position::Position() {
    _row = std::rand() % _max_row + 1;
    _col = std::rand() % _max_col + 1;
}

Position::Position(int row, int col) {
    if (!is_collision(row) || !is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}

Position::Position(int row, char col) {
    if (!is_collision(row) || !is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = std::toupper(static_cast<unsigned char>(col)) - 'A' + 1;
}

Position::Position(const Position& other) {
    _row = other._row;
    _col = other._col;
}

Position::Position(const std::string& str) {
    _row = 1;
    _col = 1;
    if (!parse(str, *this)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
}

int Position::row() const noexcept {
    return _row;
}

int Position::col() const noexcept {
    return _col;
}

char Position::char_col() const noexcept {
    return static_cast<char>('A' + _col - 1);
}

void Position::row(int value) {
    if (!is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = value;
}

void Position::col(int value) {
    if (!is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = value;
}

void Position::col(char value) {
    if (!is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = std::toupper(static_cast<unsigned char>(value)) - 'A' + 1;
}