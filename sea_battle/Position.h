#include <string>

class Position {
private:
    int _row;
    int _col;
    static const int _max_row = 10;
    static const int _max_col = 10;

public:

    Position();
    Position(int row, int col);
    Position(int row, char col);
    Position(const Position& other);
    Position(const std::string& str);

    int row() const noexcept;
    int col() const noexcept;
    char char_col() const noexcept;

    void row(int value);
    void col(int value);
    void col(char value);

    friend bool parse(const std::string& str, Position& pos);
    friend bool is_collision(int row);
    friend bool is_collision(char col);
};
