#include "Ship.h"
#include <string>

class GameField {
private:
    char** _field;
    const int _n;
    const int _m;

    int check_destroy(int row, int col) const;

public:
    GameField();
    GameField(int n, int m);
    GameField(const GameField& other);
    ~GameField();

    void set(const Ship& ship);
    State set(int row, char col);

    friend std::string to_string(const GameField& gf, bool show_ships = false);
    friend bool is_collision(const GameField& gf, const Ship& ship);
};