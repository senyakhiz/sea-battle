#include "pch.h"
#include "Position.h"
#include <stdexcept>
#include <random>
#include <string>

bool is_row(int row) noexcept {
    return row >= 1 && row <= Position::_max_row;
}

bool is_col(char col) noexcept {
    if (col >= 'a' && col <= 'z') {
        col = static_cast<char>(col - 'a' + 'A');
    }
    return col >= 'A' && col <= static_cast<char>('A' + Position::_max_col - 1);
}

char Position::col_to_char(int col) const noexcept {
    if (col >= 1 && col <= _max_col) {
        return static_cast<char>('A' + col - 1);
    }
    return '\0';
}

int Position::char_to_col(char c) const noexcept {
    if (c >= 'a' && c <= 'z') {
        c = static_cast<char>(c - 'a' + 'A');
    }
    return c - 'A' + 1;
}


Position::Position() {
    static thread_local std::mt19937 rand{ std::random_device{}() };
    std::uniform_int_distribution<int> row_dist(1, _max_row);
    std::uniform_int_distribution<int> col_dist(1, _max_col);

    _row = row_dist(rand);
    _col = col_dist(rand);
}

Position::Position(int row, int col) {
    if (!is_row(row) || !is_col(col_to_char(col))) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}

Position::Position(int row, char col) {
    if (!is_row(row) || !is_col(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = char_to_col(col);
}

Position::Position(const Position& other) noexcept {
    _row = other._row;
    _col = other._col;
}

Position::Position(const std::string& str) {
    if (!parse(str, *this)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
}

int Position::get_row() const noexcept {
    return _row;
}

int Position::get_col() const noexcept {
    return _col;
}

char Position::get_char_col() const noexcept {
    return col_to_char(_col);
}

void Position::set_row(int row) {
    if (!is_row(row)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
}

void Position::set_col(int col) {
    if (!is_col(col_to_char(col))) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = col;
}

void Position::set_col(char col) {
    if (!is_col(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = char_to_col(col);
}

bool Position::is_space_char(char c) const noexcept {
    return c == ' ' || c == '\t' || c == '\n' ||
        c == '\v' || c == '\f' || c == '\r';
}

bool Position::is_digit_char(char c) const noexcept {
    return c >= '0' && c <= '9';
}

bool parse(const std::string& str, Position& pos) noexcept {
    std::size_t i = 0;

    while (i < str.size() && pos.is_space_char(str[i])) {
        ++i;
    }

    if (i >= str.size() || !pos.is_digit_char(str[i])) {
        return false;
    }

    int row = 0;
    while (i < str.size() && pos.is_digit_char(str[i])) {
        row = row * 10 + (str[i] - '0');
        ++i;
    }

    while (i < str.size() && pos.is_space_char(str[i])) {
        ++i;
    }

    if (i >= str.size()) {
        return false;
    }

    char col = str[i++];

    while (i < str.size() && pos.is_space_char(str[i])) {
        ++i;
    }

    if (i != str.size()) {
        return false;
    }

    if (!is_row(row) || !is_col(col)) {
        return false;
    }

    pos._row = row;
    pos._col = pos.char_to_col(col);
    return true;
}