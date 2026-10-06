#include "pch.h"
#include "GameField.h"
#include <stdexcept>

GameField::GameField() : _n(10), _m(10) {
    _field = new char* [_n];
    for (int i = 0; i < _n; ++i) {
        _field[i] = new char[_m];
        for (int j = 0; j < _m; ++j) {
            _field[i][j] = ' ';
        }
    }
}

GameField::~GameField() {
    for (int i = 0; i < _n; ++i) {
        delete[] _field[i];
    }
    delete[] _field;
}


int GameField::check_destroy(int row, int col) const noexcept {
    int h_left = 0;
    while (col - 1 - h_left >= 1) {
        char c = _field[row - 1][col - 2 - h_left];
        if (c != 'X' && c != '*') break;
        ++h_left;
    }
    int h_right = 0;
    while (col + h_right + 1 <= _m) {
        char c = _field[row - 1][col + h_right];
        if (c != 'X' && c != '*') break;
        ++h_right;
    }
    int h_len = h_left + h_right + 1;

    int v_up = 0;
    while (row - 1 - v_up >= 1) {
        char c = _field[row - 2 - v_up][col - 1];
        if (c != 'X' && c != '*') break;
        ++v_up;
    }
    int v_down = 0;
    while (row + v_down + 1 <= _n) {
        char c = _field[row + v_down][col - 1];
        if (c != 'X' && c != '*') break;
        ++v_down;
    }
    int v_len = v_up + v_down + 1;

    if (h_len > 1 && v_len > 1) return 0;

    if (h_len > 1) {
        for (int i = col - h_left; i <= col + h_right; ++i) {
            if (_field[row - 1][i - 1] == '*') return 0;
        }
        return h_len;
    }
    if (v_len > 1) {
        for (int i = row - v_up; i <= row + v_down; ++i) {
            if (_field[i - 1][col - 1] == '*') return 0;
        }
        return v_len;
    }
    return 1;
}

void GameField::set(const Ship& ship) {
    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    const int row = ship.row();
    const int col = ship.col();
    const int size = ship.size();
    const Direction dir = ship.direction();

    for (int i = 0; i < size; ++i) {
        int r, c;
        if (dir == Horizontal) {
            r = row;
            c = col + i;         
        }
        else {
            r = row + i;         
            c = col;
        }
        if (r < 1 || r > _n || c < 1 || c > _m) {
            throw std::logic_error("Invalid input: incorrect field");
        }
        _field[r - 1][c - 1] = '*';
    }
}

State GameField::set(int row, char col) {
    if (row < 1 || row > _n) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    char upper = col;
    if (upper >= 'a' && upper <= 'z') {
        upper = static_cast<char>(upper - 'a' + 'A');
    }
    if (upper < 'A' || upper > static_cast<char>('A' + _m - 1)) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    const int c = upper - 'A' + 1;

    const char current = _field[row - 1][c - 1];
    if (current == '.' || current == 'X') {
        throw std::logic_error("Invalid input: incorrect move");
    }
    if (current == ' ') {
        _field[row - 1][c - 1] = '.';
        return Missed;
    }

    _field[row - 1][c - 1] = 'X';
    const int size = check_destroy(row, c);
    if (size == 0) return Hit;
    if (size == 1) return BoatDestroyed;
    if (size == 2) return DestroyersDestroyed;
    if (size == 3) return CruisersDestroyed;
    return BattleshipDestroyed;
}


std::string to_string(const GameField& field, bool show_ships) {
    std::string result;

    result += "  |";
    for (int j = 0; j < field._m; ++j) {
        if (j > 0) result += ' ';
        result += static_cast<char>('A' + j);
    }
    result += "|\n";

    result += "  +";
    for (int j = 0; j < 2 * field._m - 1; ++j) result += '-';
    result += "+\n";

    for (int i = 0; i < field._n; ++i) {
        result += std::to_string(i + 1);
        result += " |";
        for (int j = 0; j < field._m; ++j) {
            char c = field._field[i][j];
            if (c == '*' && !show_ships) c = ' ';
            result += c;
            result += '|';
        }
        result += '\n';
    }

    result += "  +";
    for (int j = 0; j < 2 * field._m - 1; ++j) result += '-';
    result += "+\n";

    return result;
}

bool is_collision(const GameField& field, const Ship& ship) {
    const int row = ship.row();
    const int col = ship.col();
    const int size = ship.size();
    const Direction dir = ship.direction();

    for (int i = 0; i < size; ++i) {
        int r, c;
        if (dir == Horizontal) {
            r = row;
            c = col + i;         
        }
        else {
            r = row + i;         
            c = col;
        }
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                const int nr = r + dr;
                const int nc = c + dc;
                if (nr < 1 || nr > field._n || nc < 1 || nc > field._m) continue;
                if (field._field[nr - 1][nc - 1] == '*') return true;
            }
        }
    }
    return false;
}