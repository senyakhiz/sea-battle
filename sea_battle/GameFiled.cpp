#include "GameField.h"
#include <stdexcept>
#include <cctype>
#include <string>

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
    if (n <= 0 || n > 25 || m <= 0 || m > 25) {
        throw std::logic_error("Invalid input: incorrect field");
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

void GameField::set(const Ship& ship) {
    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    int row = ship.row();
    int col = ship.col();
    int size = ship.size();
    Direction dir = ship.direction();
    for (int i = 0; i < size; ++i) {
        int r = row + (dir == Vertical ? i : 0);
        int c = col + (dir == Horizontal ? i : 0);
        _field[r - 1][c - 1] = '*';
    }
}

State GameField::set(int row, char col) {
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(col)));
    int c = upper - 'A' + 1;
    if (row < 1 || row > _n || c < 1 || c > _m) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    char cell = _field[row - 1][c - 1];
    if (cell == '.' || cell == 'X') {
        throw std::logic_error("Invalid input: incorrect move");
    }
    if (cell == ' ') {
        _field[row - 1][c - 1] = '.';
        return Missed;
    }
    _field[row - 1][c - 1] = 'X';
    int destroyed = check_destroy(row, c);
    switch (destroyed) {
    case 1: return BoatDestroyed;
    case 2: return DestroyersDestroyed;
    case 3: return CruisersDestroyed;
    case 4: return BattleshipDestroyed;
    default: return Hit;
    }
}

int GameField::check_destroy(int row, int col) const {
    int left = col;
    while (left > 1) {
        char ch = _field[row - 1][left - 2];
        if (ch != '*' && ch != 'X') break;
        --left;
    }
    int right = col;
    while (right < _m) {
        char ch = _field[row - 1][right];
        if (ch != '*' && ch != 'X') break;
        ++right;
    }
    int h_size = right - left + 1;

    int up = row;
    while (up > 1) {
        char ch = _field[up - 2][col - 1];
        if (ch != '*' && ch != 'X') break;
        --up;
    }
    int down = row;
    while (down < _n) {
        char ch = _field[down][col - 1];
        if (ch != '*' && ch != 'X') break;
        ++down;
    }
    int v_size = down - up + 1;

    if (h_size >= v_size) {
        for (int c = left; c <= right; ++c) {
            if (_field[row - 1][c - 1] != 'X') return 0;
        }
        return h_size;
    }
    for (int r = up; r <= down; ++r) {
        if (_field[r - 1][col - 1] != 'X') return 0;
    }
    return v_size;
}

bool is_collision(const GameField& gf, const Ship& ship) {
    int row = ship.row();
    int col = ship.col();
    int size = ship.size();
    Direction dir = ship.direction();

    for (int i = 0; i < size; ++i) {
        int r = row + (dir == Vertical ? i : 0);
        int c = col + (dir == Horizontal ? i : 0);
        if (r < 1 || r > gf._n || c < 1 || c > gf._m) return true;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                int nr = r + dr;
                int nc = c + dc;
                if (nr >= 1 && nr <= gf._n && nc >= 1 && nc <= gf._m) {
                    if (gf._field[nr - 1][nc - 1] == '*') return true;
                }
            }
        }
    }
    return false;
}

std::string to_string(const GameField& gf, bool show_ships) {
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
        std::string label = std::to_string(i + 1);
        while (label.length() < 2) label += ' ';
        result += label;
        for (int j = 0; j < gf._m; ++j) {
            char ch = gf._field[i][j];
            if (!show_ships && ch == '*') ch = ' ';
            result += '|';
            result += ch;
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