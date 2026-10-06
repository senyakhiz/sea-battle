#include "pch.h"
#include "APP.h"
#include "Game.h"
#include <iostream>
#include <limits>
#include <exception>

APP::APP() : _exit_requested(false) {}

void APP::print() const {
    std::cout << "========================================\n";
    std::cout << "         SEA BATTLE (МОРСКОЙ БОЙ)       \n";
    std::cout << "========================================\n\n";

    std::cout << "Введите расстановку кораблей.\n";
    std::cout << "Формат: <размер> <направление H/V> <строка> <столбец>\n";
    std::cout << "Пример: 4 H 7 A\n";
    std::cout << "Нужно расставить: 4x1, 3x2, 2x3, 1x4.\n";
    std::cout << "Пустая строка — конец расстановки.\n";
    std::cout << "После расстановки обоих игроков вводите ходы.\n\n";
}

int APP::run() {
    setlocale(LC_ALL, "Russian");
    print();

    Game game;

    try {
        game.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    _exit_requested = true;
    return 0;
}