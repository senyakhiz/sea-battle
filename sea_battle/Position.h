#pragma once
#include <string>

class Position {
private:
    int _row;
    int _col;

    static const int _max_row = 10;
    static const int _max_col = 10;

    bool is_space_char(char c) const noexcept;
    bool is_digit_char(char c) const noexcept;
    char col_to_char(int col) const noexcept;
    int char_to_col(char c) const noexcept;

public:
    Position();
    Position(int row, int col);
    Position(int row, char col);
    Position(const Position& other) noexcept;
    Position(const std::string& str);

    int getRow() const noexcept;
    int getCol() const noexcept;
    char getCharCol() const noexcept;

    void setRow(int row);
    void setCol(int col);
    void setCol(char col);

private:
    friend bool parse(const std::string& str, Position& pos) noexcept;
    friend bool is_row(int row) noexcept;
    friend bool is_col(char col) noexcept;
};
