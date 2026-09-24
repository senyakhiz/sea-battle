#pragma once
#include <string>

class GameField {
private:
    char** _field;
    const int _n;
    const int _m;

    static bool Correct_Input(int n, int m) noexcept;

public:
    
    GameField();
    GameField(int n, int m);
    GameField(const GameField& other);
    ~GameField();

    void set(int row, char col);
    char get(int row, char col) const;

    friend std::string to_string(const GameField& gf);

};
