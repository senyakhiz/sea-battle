#include <string>

class Position {
private:
    int _row;
    int _col;
    static const int _max_row = 10;
    static const int _max_col = 10;

    static bool Correct_Input(int row, int col) noexcept;

public:

    Position();
    Position(int row, int col);
    Position(const Position& other);
    Position(const std::string& str);

    int row() const noexcept;
    int col() const noexcept;
    void row(int value);
    void col(int value);

    friend std::string to_string(const Position& pos) noexcept;
    friend Position parse(const std::string& str);

};