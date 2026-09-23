#include "Position.h"
#include <stdexcept>
#include <sstream>

const int Position::_max_row;
const int Position::_max_col;

bool Position::Correct_Input(int row, int col) noexcept {
    return row >= 1 && row <= _max_row && col >= 1 && col <= _max_col;
}

Position::Position() {
    _row = 1;
    _col = 1;
}

Position::Position(int row, int col) {
    if (!Correct_Input(row, col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}

Position::Position(const Position& other) {
    _row = other._row;
    _col = other._col;
}

Position::Position(const std::string& str) : Position(parse(str)) {}

int Position::row() const noexcept { 
    return _row; 
}
int Position::col() const noexcept { 
    return _col; 
}

void Position::row(int value) {

    if (value < 1 || value > _max_row) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = value;
}

void Position::col(int value) {
    if (value < 1 || value > _max_col) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = value;
}

std::string to_string(const Position& pos) noexcept {
    return "(" + std::to_string(pos._row) + ", " + std::to_string(pos._col) + ")";
}

Position parse(const std::string& str) {
    std::stringstream ss(str);
    char ch;
    int r, c;

    if (!(ss >> ch) || ch != '(') {
        throw std::logic_error("Invalid input: incorrect position");
    }
    if (!(ss >> r)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    if (!(ss >> ch) || ch != ',') {
        throw std::logic_error("Invalid input: incorrect position");
    }
    if (!(ss >> c)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    if (!(ss >> ch) || ch != ')') {
        throw std::logic_error("Invalid input: incorrect position");
    }

    return Position(r, c);
}