#include "Position.h"

enum Direction { Horizontal, Vertical };

class Ship {
private:
    int _size;
    Position _position;
    Direction _direction;

public:

    Ship(int size, Position position, Direction direction);
    Ship(int size, char direction, int row, char col);
    Ship(const std::string& str);

    int size() const noexcept;
    int row() const noexcept;
    int col() const noexcept;
    Position position() const noexcept;
    Direction direction() const noexcept;

    void size(int value);
    void row(int value);
    void col(int value);
    void col(char value);
    void direction(Direction value);
    void direction(char value);
    void position(Position value);

    friend bool parse(const std::string& str, Ship& ship);
    friend bool is_collision(int size, Position position, Direction direction);
};
