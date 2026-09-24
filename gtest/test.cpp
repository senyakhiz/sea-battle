#include "pch.h"
#include "Position.h"
#include "Ship.h"
#include "GameFiled.h"

TEST(PositionTest, DefaultConstructor) {
    Position p;
    EXPECT_EQ(p.row(), 1);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTest, InitConstructorValid) {
    Position p(3, 4);
    EXPECT_EQ(p.row(), 3);
    EXPECT_EQ(p.col(), 4);
}

TEST(PositionTest, InitConstructorInvalidRow) {
    EXPECT_THROW(Position p(15, 2), std::logic_error);
}

TEST(PositionTest, InitConstructorInvalidCol) {
    EXPECT_THROW(Position p(2, 15), std::logic_error);
}

TEST(PositionTest, InitConstructorBoundaries) {
    Position p1(1, 1);
    Position p2(10, 10);
    EXPECT_EQ(p1.row(), 1);
    EXPECT_EQ(p1.col(), 1);
    EXPECT_EQ(p2.row(), 10);
    EXPECT_EQ(p2.col(), 10);
}

TEST(PositionTest, CopyConstructor) {
    Position a(5, 6);
    Position b(a);
    EXPECT_EQ(b.row(), 5);
    EXPECT_EQ(b.col(), 6);
}

TEST(PositionTest, StringConstructor) {
    Position p("(7, 8)");
    EXPECT_EQ(p.row(), 7);
    EXPECT_EQ(p.col(), 8);
}

TEST(PositionTest, StringConstructorInvalid) {
    EXPECT_THROW(Position p("7 8"), std::logic_error);
}

TEST(PositionTest, SetterRowValid) {
    Position p;
    p.row(5);
    EXPECT_EQ(p.row(), 5);
}

TEST(PositionTest, SetterRowInvalid) {
    Position p;
    EXPECT_THROW(p.row(0), std::logic_error);
}

TEST(PositionTest, SetterColValid) {
    Position p;
    p.col(7);
    EXPECT_EQ(p.col(), 7);
}

TEST(PositionTest, SetterColInvalid) {
    Position p;
    EXPECT_THROW(p.col(11), std::logic_error);
}

TEST(PositionTest, ToString) {
    Position p(3, 4);
    EXPECT_EQ(to_string(p), "(3, 4)");
}

TEST(PositionTest, Parse) {
    Position p = parse("(6, 7)");
    EXPECT_EQ(p.row(), 6);
    EXPECT_EQ(p.col(), 7);
}

TEST(PositionTest, ParseInvalid) {
    EXPECT_THROW(parse("(6 7)"), std::logic_error);
}

TEST(PositionTest, ParseOutOfRange) {
    EXPECT_THROW(parse("(0, 5)"), std::logic_error);
}

TEST(ShipTest, FullConstructorHorizontal) {
    Position p(4, 3);
    Ship s(3, p, Horizontal);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, FullConstructorVertical) {
    Position p(2, 5);
    Ship s(4, p, Vertical);
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s.row(), 2);
    EXPECT_EQ(s.col(), 5);
    EXPECT_TRUE(s.direction() == Vertical);
}

TEST(ShipTest, FullConstructorHorizontalOutOfField) {
    Position p(4, 9);
    EXPECT_THROW(Ship s(3, p, Horizontal), std::logic_error);
}

TEST(ShipTest, FullConstructorVerticalOutOfField) {
    Position p(9, 5);
    EXPECT_THROW(Ship s(3, p, Vertical), std::logic_error);
}

TEST(ShipTest, FullConstructorInvalidSize) {
    Position p(1, 1);
    EXPECT_THROW(Ship s(5, p, Horizontal), std::logic_error);
}

TEST(ShipTest, FullConstructorZeroSize) {
    Position p(1, 1);
    EXPECT_THROW(Ship s(0, p, Horizontal), std::logic_error);
}

TEST(ShipTest, PartialConstructor) {
    Position p(4, 3);
    Ship s(3, p);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, PartialConstructorOutOfField) {
    Position p(4, 9);
    EXPECT_THROW(Ship s(3, p), std::logic_error);
}

TEST(ShipTest, CharConstructorHorizontal) {
    Ship s(3, 'H', 4, 'C');
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, CharConstructorVertical) {
    Ship s(3, 'V', 4, 'C');
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
    EXPECT_TRUE(s.direction() == Vertical);
}

TEST(ShipTest, CharConstructorLowerCaseDirection) {
    Ship s(2, 'h', 5, 'D');
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 4);
    EXPECT_TRUE(s.direction() == Horizontal);
}

TEST(ShipTest, CharConstructorInvalidDirection) {
    EXPECT_THROW(Ship s(3, 'X', 4, 'C'), std::logic_error);
}

TEST(ShipTest, CharConstructorInvalidCol) {
    EXPECT_THROW(Ship s(3, 'H', 4, 'Z'), std::logic_error);
}

TEST(ShipTest, CharConstructorOutOfField) {
    EXPECT_THROW(Ship s(3, 'H', 4, 'I'), std::logic_error);
}

TEST(ShipTest, RotateHorizontalToVertical) {
    Position p(2, 5);
    Ship s(4, p, Horizontal);
    s.rotate();
    EXPECT_TRUE(s.direction() == Vertical);
    EXPECT_EQ(s.row(), 2);
    EXPECT_EQ(s.col(), 5);
}

TEST(ShipTest, RotateVerticalToHorizontal) {
    Position p(5, 2);
    Ship s(4, p, Vertical);
    s.rotate();
    EXPECT_TRUE(s.direction() == Horizontal);
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 2);
}

TEST(ShipTest, RotateOutOfField) {
    Position p(4, 9);
    Ship s(2, p, Vertical);
    EXPECT_THROW(s.rotate(), std::logic_error);
}

TEST(GameFieldTest, DefaultConstructor) {
    GameField gf;
    EXPECT_TRUE(gf.get(1, 'A') == ' ');
    EXPECT_TRUE(gf.get(10, 'J') == ' ');
}

TEST(GameFieldTest, InitConstructorValid) {
    GameField gf(6, 6);
    EXPECT_TRUE(gf.get(1, 'A') == ' ');
    EXPECT_TRUE(gf.get(6, 'F') == ' ');
}

TEST(GameFieldTest, InitConstructorNegative) {
    EXPECT_THROW(GameField gf(-2, 5), std::logic_error);
}

TEST(GameFieldTest, InitConstructorTooBig) {
    EXPECT_THROW(GameField gf(26, 5), std::logic_error);
}

TEST(GameFieldTest, InitConstructorZero) {
    EXPECT_THROW(GameField gf(0, 5), std::logic_error);
}

TEST(GameFieldTest, CopyConstructor) {
    GameField a(6, 6);
    a.set(2, 'C');
    GameField b(a);
    EXPECT_TRUE(b.get(2, 'C') == '*');
    EXPECT_TRUE(b.get(1, 'A') == ' ');
}

TEST(GameFieldTest, SetGetValid) {
    GameField gf(6, 6);
    gf.set(4, 'B');
    EXPECT_TRUE(gf.get(4, 'B') == '*');
}

TEST(GameFieldTest, SetOutOfBounds) {
    GameField gf(6, 6);
    EXPECT_THROW(gf.set(2, 'J'), std::logic_error);
}

TEST(GameFieldTest, GetOutOfBounds) {
    GameField gf(6, 6);
    EXPECT_THROW(gf.get(7, 'A'), std::logic_error);
}

TEST(GameFieldTest, ToStringFormat) {
    GameField gf(6, 6);
    gf.set(2, 'C');
    gf.set(4, 'B');
    gf.set(5, 'D');
    gf.set(6, 'D');
    gf.set(2, 'F');
    gf.set(3, 'F');
    std::string expected =
        "  |A B C D E F|\n"
        "  +-----------+\n"
        "1 | | | | | | |\n"
        "2 | | |*| | |*|\n"
        "3 | | | | | |*|\n"
        "4 | |*| | | | |\n"
        "5 | | | |*| | |\n"
        "6 | | | |*| | |\n"
        "  +-----------+\n";
    EXPECT_EQ(to_string(gf), expected);
}