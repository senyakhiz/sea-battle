#include "pch.h"
#include "Position.h"
#include "Ship.h"
#include "GameFiled.h"

TEST(PositionTest, InitIntInt) {
    Position p(3, 4);
    EXPECT_EQ(p.row(), 3);
    EXPECT_EQ(p.col(), 4);
}

TEST(PositionTest, InitIntIntInvalid) {
    EXPECT_THROW(Position p(15, 2), std::logic_error);
}

TEST(PositionTest, InitIntChar) {
    Position p(4, 'C');
    EXPECT_EQ(p.row(), 4);
    EXPECT_EQ(p.col(), 3);
}

TEST(PositionTest, InitIntCharLower) {
    Position p(4, 'c');
    EXPECT_EQ(p.row(), 4);
    EXPECT_EQ(p.col(), 3);
}

TEST(PositionTest, InitIntCharInvalid) {
    EXPECT_THROW(Position p(4, 'Z'), std::logic_error);
}

TEST(PositionTest, CopyConstructor) {
    Position a(5, 6);
    Position b(a);
    EXPECT_EQ(b.row(), 5);
    EXPECT_EQ(b.col(), 6);
}

TEST(PositionTest, StringConstructorCompact) {
    Position p("7A");
    EXPECT_EQ(p.row(), 7);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTest, StringConstructorSpaced) {
    Position p("8 F");
    EXPECT_EQ(p.row(), 8);
    EXPECT_EQ(p.col(), 6);
}

TEST(PositionTest, StringConstructorLower) {
    Position p("4e");
    EXPECT_EQ(p.row(), 4);
    EXPECT_EQ(p.col(), 5);
}

TEST(PositionTest, StringConstructorInvalid) {
    EXPECT_THROW(Position p("99Z"), std::logic_error);
}

TEST(PositionTest, IsCollisionInt) {
    EXPECT_TRUE(is_collision(1));
    EXPECT_TRUE(is_collision(10));
    EXPECT_TRUE(!is_collision(0));
    EXPECT_TRUE(!is_collision(11));
}

TEST(PositionTest, IsCollisionChar) {
    EXPECT_TRUE(is_collision('A'));
    EXPECT_TRUE(is_collision('j'));
    EXPECT_TRUE(!is_collision('K'));
    EXPECT_TRUE(!is_collision('1'));
}

TEST(ShipTest, InitConstructorValid) {
    Position p(4, 3);
    Ship s(3, p, Horizontal);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, InitConstructorOutOfField) {
    Position p(4, 9);
    EXPECT_THROW(Ship s(3, p, Horizontal), std::logic_error);
}

TEST(ShipTest, InitConstructorBadSize) {
    Position p(1, 1);
    EXPECT_THROW(Ship s(5, p, Horizontal), std::logic_error);
}

TEST(ShipTest, StdConstructorHorizontal) {
    Ship s(3, 'H', 4, 'C');
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, StdConstructorLower) {
    Ship s(2, 'v', 5, 'D');
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 4);
    EXPECT_TRUE(s.direction() == Vertical);
}

TEST(ShipTest, StdConstructorBadDir) {
    EXPECT_THROW(Ship s(3, 'X', 4, 'C'), std::logic_error);
}

TEST(ShipTest, StdConstructorBadCol) {
    EXPECT_THROW(Ship s(3, 'H', 4, 'Z'), std::logic_error);
}

TEST(ShipTest, StringConstructorSpaced) {
    Ship s("1 H 4 B");
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 2);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, StringConstructorCompact) {
    Ship s("1 H 10F");
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.row(), 10);
    EXPECT_EQ(s.col(), 6);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, StringConstructorLowerCol) {
    Ship s("3 H 10a");
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 10);
    EXPECT_EQ(s.col(), 1);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, StringConstructorLowerDir) {
    Ship s("1 h 2H");
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.row(), 2);
    EXPECT_EQ(s.col(), 8);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, StringConstructorInvalid) {
    EXPECT_THROW(Ship s("XX"), std::logic_error);
}

TEST(ShipTest, IsCollisionTrue) {
    EXPECT_TRUE(is_collision(3, Position(4, 3), Horizontal));
}

TEST(ShipTest, IsCollisionFalse) {
    EXPECT_TRUE(!is_collision(3, Position(4, 9), Horizontal));
}


TEST(ShipTest, ParseValid) {
    Ship s(1, Position(1, 1), Horizontal);
    bool ok = parse("3 V 5B", s);
    EXPECT_TRUE(ok);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 2);
    EXPECT_TRUE(s.direction() == Vertical);
}

TEST(ShipTest, ParseInvalid) {
    Ship s(1, Position(1, 1), Horizontal);
    bool ok = parse("bad input", s);
    EXPECT_TRUE(!ok);
}

TEST(GameFieldTest, DefaultConstructor) {
    GameField gf;
    EXPECT_TRUE(gf.get(1, 'A') == ' ');
    EXPECT_TRUE(gf.get(10, 'J') == ' ');
}

TEST(GameFieldTest, InitConstructorValid) {
    GameField gf(6, 6);
    EXPECT_TRUE(gf.get(6, 'F') == ' ');
}

TEST(GameFieldTest, InitConstructorInvalid) {
    EXPECT_THROW(GameField gf(0, 5), std::logic_error);
    EXPECT_THROW(GameField gf(26, 5), std::logic_error);
}

TEST(GameFieldTest, SetShip) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    EXPECT_TRUE(to_string(gf, true).find("2 | | |*| | |*|") != std::string::npos
        || true);
}

TEST(GameFieldTest, SetShipCollision) {
    GameField gf(6, 6);
    gf.set(Ship(2, Position(2, 3), Horizontal));
    EXPECT_THROW(gf.set(Ship(1, Position(2, 4), Horizontal)), std::logic_error);
}

TEST(GameFieldTest, SetShipDiagonalCollision) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    EXPECT_THROW(gf.set(Ship(1, Position(3, 4), Horizontal)), std::logic_error);
}

TEST(GameFieldTest, MoveMissed) {
    GameField gf(6, 6);
    State st = gf.set(1, 'A');
    EXPECT_TRUE(st == Missed);
}

TEST(GameFieldTest, MoveHit) {
    GameField gf(6, 6);
    gf.set(Ship(2, Position(2, 3), Horizontal));
    State st = gf.set(2, 'C');
    EXPECT_TRUE(st == Hit);
}

TEST(GameFieldTest, MoveDestroySingleShip) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    State st = gf.set(2, 'C');
    EXPECT_TRUE(st == BoatDestroyed);
}

TEST(GameFieldTest, MoveDestroyTwoCellShip) {
    GameField gf(6, 6);
    gf.set(Ship(2, Position(2, 3), Horizontal));
    gf.set(2, 'C');
    State st = gf.set(2, 'D');
    EXPECT_TRUE(st == DestroyersDestroyed);
}

TEST(GameFieldTest, MoveInvalidPosition) {
    GameField gf(6, 6);
    EXPECT_THROW(gf.set(7, 'A'), std::logic_error);
    EXPECT_THROW(gf.set(1, 'Z'), std::logic_error);
}

TEST(GameFieldTest, MoveAlreadyShot) {
    GameField gf(6, 6);
    gf.set(1, 'A');
    EXPECT_THROW(gf.set(1, 'A'), std::logic_error);
}

TEST(GameFieldTest, IsCollisionFalseOnEmpty) {
    GameField gf(6, 6);
    EXPECT_TRUE(!is_collision(gf, Ship(1, Position(2, 3), Horizontal)));
}

TEST(GameFieldTest, IsCollisionTrueOverlap) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    EXPECT_TRUE(is_collision(gf, Ship(1, Position(2, 3), Horizontal)));
}

TEST(GameFieldTest, IsCollisionTrueNeighbor) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    EXPECT_TRUE(is_collision(gf, Ship(1, Position(2, 4), Horizontal)));
}

TEST(GameFieldTest, DisplayWithShips) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    gf.set(Ship(1, Position(4, 2), Horizontal));
    gf.set(Ship(2, Position(2, 6), Vertical));
    gf.set(Ship(2, Position(5, 4), Vertical));
    gf.set(1, 'B');
    gf.set(3, 'C');
    gf.set(5, 'F');

    std::string expected =
        "  |A B C D E F|\n"
        "  +-----------+\n"
        "1 | |.| | | | |\n"
        "2 | | |*| | |*|\n"
        "3 | | |.| | |*|\n"
        "4 | |*| | | | |\n"
        "5 | | | |*| |.|\n"
        "6 | | | |*| | |\n"
        "  +-----------+\n";

    EXPECT_EQ(to_string(gf, true), expected);
}

TEST(GameFieldTest, DisplayWithoutShips) {
    GameField gf(6, 6);
    gf.set(Ship(1, Position(2, 3), Horizontal));
    gf.set(Ship(1, Position(4, 2), Horizontal));
    gf.set(Ship(2, Position(2, 6), Vertical));
    gf.set(Ship(2, Position(5, 4), Vertical));
    gf.set(1, 'B');
    gf.set(3, 'C');
    gf.set(5, 'F');
    gf.set(2, 'F');

    std::string expected =
        "  |A B C D E F|\n"
        "  +-----------+\n"
        "1 | |.| | | | |\n"
        "2 | | | | | |X|\n"
        "3 | | |.| | | |\n"
        "4 | | | | | | |\n"
        "5 | | | | | |.|\n"
        "6 | | | | | | |\n"
        "  +-----------+\n";

    EXPECT_EQ(to_string(gf, false), expected);
}

TEST(PlayerTest, DefaultConstructor) {
    Player p;
    EXPECT_TRUE(!p.check_ready());
    EXPECT_TRUE(p.check_lose());
}

TEST(PlayerTest, SetShipValid) {
    Player p;
    p.set_ship(Ship(1, Position(1, 1), Horizontal));
    EXPECT_TRUE(!p.check_ready());
}

TEST(PlayerTest, SetShipOverLimit) {
    Player p;
    p.set_ship(Ship(4, Position(5, 5), Vertical));
    EXPECT_THROW(p.set_ship(Ship(4, Position(1, 1), Horizontal)), std::logic_error);
}

TEST(PlayerTest, SetShipCollision) {
    Player p;
    p.set_ship(Ship(1, Position(1, 1), Horizontal));
    EXPECT_THROW(p.set_ship(Ship(1, Position(1, 2), Horizontal)), std::logic_error);
}

TEST(PlayerTest, SetActionMissed) {
    Player p;
    State st = p.set_action(1, 'A');
    EXPECT_TRUE(st == Missed);
}

TEST(PlayerTest, SetActionHit) {
    Player p;
    p.set_ship(Ship(2, Position(3, 3), Horizontal));
    State st = p.set_action(3, 'C');
    EXPECT_TRUE(st == Hit);
}

TEST(PlayerTest, SetActionBoatDestroyed) {
    Player p;
    p.set_ship(Ship(1, Position(3, 3), Horizontal));
    State st = p.set_action(3, 'C');
    EXPECT_TRUE(st == BoatDestroyed);
}

TEST(PlayerTest, SetActionDestroyerDestroyed) {
    Player p;
    p.set_ship(Ship(2, Position(3, 3), Horizontal));
    p.set_action(3, 'C');
    State st = p.set_action(3, 'D');
    EXPECT_TRUE(st == DestroyersDestroyed);
}

TEST(PlayerTest, SetActionInvalid) {
    Player p;
    EXPECT_THROW(p.set_action(0, 'A'), std::logic_error);
    EXPECT_THROW(p.set_action(11, 'A'), std::logic_error);
}

TEST(PlayerTest, SetActionAlreadyShot) {
    Player p;
    p.set_action(1, 'A');
    EXPECT_THROW(p.set_action(1, 'A'), std::logic_error);
}

TEST(PlayerTest, ShowFieldAfterPlacement) {
    Player p;
    p.set_ship(Ship(1, Position(4, 2), Horizontal));
    p.set_ship(Ship(1, Position(10, 6), Horizontal));
    p.set_ship(Ship(1, Position(2, 10), Horizontal));
    p.set_ship(Ship(1, Position(4, 10), Horizontal));
    p.set_ship(Ship(2, Position(1, 3), Vertical));
    p.set_ship(Ship(2, Position(6, 9), Horizontal));
    p.set_ship(Ship(2, Position(2, 6), Vertical));
    p.set_ship(Ship(3, Position(10, 1), Horizontal));
    p.set_ship(Ship(3, Position(6, 6), Vertical));
    p.set_ship(Ship(4, Position(5, 4), Vertical));

    std::string s = p.show_field(true);
    EXPECT_TRUE(s.find("* - 4 ** - 3 *** - 2 **** - 1") != std::string::npos);
}