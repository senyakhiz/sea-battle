#include "GameField.h"
#include <stdexcept>

bool GameField::Correct_Input(int n, int m) noexcept {
    return n > 0 && n <= 25 && m > 0 && m <= 25;
}

GameField::GameField() : _n(10), _m(10) {
    _field = new char* [10];
    for (int i = 0; i < 10; ++i) {
        _field[i] = new char[10];
        for (int j = 0; j < 10; ++j) {
            _field[i][j] = ' ';
        }
    }
}

GameField::GameField(int n, int m) : _n(n), _m(m) {
    if (!Correct_Input(n, m)) {
        throw std::logic_error("Invalid input: incorrect field parameters");
    }
    _field = new char* [n];
    for (int i = 0; i < n; ++i) {
        _field[i] = new char[m];
        for (int j = 0; j < m; ++j) {
            _field[i][j] = ' ';
        }
    }
}

GameField::GameField(const GameField& other) : _n(other._n), _m(other._m) {
    _field = new char* [_n];
    for (int i = 0; i < _n; ++i) {
        _field[i] = new char[_m];
        for (int j = 0; j < _m; ++j) {
            _field[i][j] = other._field[i][j];
        }
    }
}

GameField::~GameField() {
    for (int i = 0; i < _n; ++i) {
        delete[] _field[i];
    }
    delete[] _field;
}

void GameField::set(int row, char col) {
    if (row < 1 || row > _n || col < 'A' || col >= 'A' + _m) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _field[row - 1][col - 'A'] = '*';
}

char GameField::get(int row, char col) const {
    if (row < 1 || row > _n || col < 'A' || col >= 'A' + _m) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    return _field[row - 1][col - 'A'];
}

std::string to_string(const GameField& gf) {
    std::string result;

    result += "  |";
    for (int j = 0; j < gf._m; ++j) {
        result += static_cast<char>('A' + j);
        if (j < gf._m - 1) result += ' ';
    }
    result += "|\n";

    result += "  +";
    for (int j = 0; j < gf._m; ++j) {
        result += '-';
        if (j < gf._m - 1) result += '-';
    }
    result += "+\n";

    for (int i = 0; i < gf._n; ++i) {
        result += std::to_string(i + 1);
        result += ' ';
        for (int j = 0; j < gf._m; ++j) {
            result += '|';
            result += gf._field[i][j];
        }
        result += "|\n";
    }

    result += "  +";
    for (int j = 0; j < gf._m; ++j) {
        result += '-';
        if (j < gf._m - 1) result += '-';
    }
    result += "+\n";

    return result;
}