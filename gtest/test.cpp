#include "pch.h"
#include "Position.h"

TEST(PositionClass, IsRowValid) {
    EXPECT_TRUE(is_row(1));
    EXPECT_TRUE(is_row(10));
}

TEST(PositionClass, IsRowInvalid) {
    EXPECT_FALSE(is_row(0));
    EXPECT_FALSE(is_row(-1));
    EXPECT_FALSE(is_row(11));
    EXPECT_FALSE(is_row(100));
}

TEST(PositionClass, IsColValid) {
    EXPECT_TRUE(is_col('A'));
    EXPECT_TRUE(is_col('a'));
}

TEST(PositionClass, IsColInvalid) {
    EXPECT_FALSE(is_col('@'));
    EXPECT_FALSE(is_col('K'));
    EXPECT_FALSE(is_col('k'));
    EXPECT_FALSE(is_col('1'));
    EXPECT_FALSE(is_col(' '));
}

TEST(PositionClass, GeneratesValidPosition) {
    Position p;
    EXPECT_TRUE(is_row(p.get_col()));
    EXPECT_TRUE(is_col(p.get_char_col()));
    EXPECT_TRUE(p.get_col() >= 1);
    EXPECT_TRUE(p.get_col() <= 10);
}

TEST(PositionClass, ValidValues) {
    Position p(4, 2);
    EXPECT_EQ(p.get_row(), 4);
    EXPECT_EQ(p.get_col(), 2);
    EXPECT_EQ(p.get_char_col(), 'B');
}

TEST(PositionClass, RowTooSmall) {
    EXPECT_THROW(Position p(0, 1), std::logic_error);
}

TEST(PositionClass, RowTooBig) {
    EXPECT_THROW(Position p(11, 1), std::logic_error);
}

TEST(PositionClass, ColTooSmall) {
    EXPECT_THROW(Position p(1, 0), std::logic_error);
}

TEST(PositionClass, ColTooBig) {
    EXPECT_THROW(Position p(1, 11), std::logic_error);
}

TEST(PositionClass, ValidUppercase) {
    Position p(1, 'A');
    EXPECT_EQ(p.get_col(), 1);
    EXPECT_EQ(p.get_col(), 1);
}

TEST(PositionClass, ValidLowercase) {
    Position p(10, 'j');
    EXPECT_EQ(p.get_col(), 10);
    EXPECT_EQ(p.get_col(), 10);
}

TEST(PositionClass, InvalidCol) {
    EXPECT_THROW(Position p(1, 'K'), std::logic_error);
}

TEST(PositionClass, InvalidRow) {
    EXPECT_THROW(Position p(0, 'A'), std::logic_error);
}

TEST(PositionClass, CopiesValues) {
    Position a(3, 'D');
    Position b(a);
    EXPECT_EQ(b.get_row(), 3);
    EXPECT_EQ(b.get_col(), 4);
    EXPECT_EQ(b.get_char_col(), 'D');
}


TEST(PositionClass, ParsesSimple) {
    Position p("4B");
    EXPECT_EQ(p.get_row(), 4);
    EXPECT_EQ(p.get_col(), 2);
}

TEST(PositionClass, ParsesWithSpace) {
    Position p("8 F");
    EXPECT_EQ(p.get_row(), 8);
    EXPECT_EQ(p.get_col(), 6);
}

TEST(PositionClass, ParsesLowercase) {
    Position p("4e");
    EXPECT_EQ(p.get_row(), 4);
    EXPECT_EQ(p.get_col(), 5);
}

TEST(PositionClass, ParsesWithSpacesAround) {
    Position p("  1 A  ");
    EXPECT_EQ(p.get_row(), 1);
    EXPECT_EQ(p.get_col(), 1);
}

TEST(PositionClass, ParsesTen) {
    Position p("10 F");
    EXPECT_EQ(p.get_row(), 10);
    EXPECT_EQ(p.get_col(), 6);
}

TEST(PositionClass, InvalidRowZero) {
    EXPECT_THROW(Position p("0 A"), std::logic_error);
}

TEST(PositionClass, InvalidColl) {
    EXPECT_THROW(Position p("1 K"), std::logic_error);
}

TEST(PositionClass, InvalidFormatDigits) {
    EXPECT_THROW(Position p("2 2"), std::logic_error);
}

TEST(PositionClass, InvalidEmpty) {
    EXPECT_THROW(Position p(""), std::logic_error);
}

TEST(PositionClass, ValidInputs) {
    Position p(1, 1);
    EXPECT_TRUE(parse("4B", p));
    EXPECT_EQ(p.get_row(), 4);
    EXPECT_EQ(p.get_col(), 2);
}

TEST(PositionClass, InvalidInputs) {
    Position p(1, 1);
    EXPECT_FALSE(parse("0 A", p));
    EXPECT_FALSE(parse("2 2", p));
    EXPECT_FALSE(parse("", p));
    EXPECT_FALSE(parse("A1", p));
    EXPECT_FALSE(parse("1 K", p));
}

TEST(ShipClass, IsCollisionValidSingleCell) {
    EXPECT_TRUE(is_collision(1, Position(1, 1), Horizontal));
    EXPECT_TRUE(is_collision(1, Position(10, 10), Vertical));
}

TEST(ShipClass, IsCollisionSizeOutOfRange) {
    EXPECT_FALSE(is_collision(0, Position(5, 5), Horizontal));
    EXPECT_FALSE(is_collision(5, Position(5, 5), Horizontal));
}

TEST(ShipClass, IsCollisionHorizontalFits) {
    EXPECT_TRUE(is_collision(4, Position(1, 4), Horizontal));
}

TEST(ShipClass, IsCollisionHorizontalDoesNotFit) {
    EXPECT_FALSE(is_collision(4, Position(1, 3), Horizontal));
}

TEST(ShipClass, IsCollisionVerticalFits) {
    EXPECT_TRUE(is_collision(4, Position(4, 1), Vertical));
}

TEST(ShipClass, IsCollisionVerticalDoesNotFit) {
    EXPECT_FALSE(is_collision(4, Position(3, 1), Vertical));
}

TEST(ShipClass, InitCtorValidValues) {
    Ship s(3, Position(5, 5), Horizontal);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 5);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipClass, InitCtorInvalidSize) {
    EXPECT_THROW(Ship s(0, Position(5, 5), Horizontal), std::logic_error);
    EXPECT_THROW(Ship s(5, Position(5, 5), Horizontal), std::logic_error);
}

TEST(ShipClass, InitCtorInvalidPlacement) {
    EXPECT_THROW(Ship s(4, Position(1, 2), Horizontal), std::logic_error);
}

TEST(ShipClass, StandardCtorValidUppercase) {
    Ship s(3, 'H', 5, 'E');
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 5);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipClass, StandardCtorValidLowercase) {
    Ship s(2, 'v', 5, 'A');
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipClass, StandardCtorInvalidDirectionChar) {
    EXPECT_THROW(Ship s(2, 'X', 5, 'A'), std::logic_error);
}

TEST(ShipClass, StandardCtorInvalidPlacement) {
    EXPECT_THROW(Ship s(4, 'V', 3, 'A'), std::logic_error);
}

TEST(ShipClass, ParseValidSimple) {
    Ship s("1 H 4 B");
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 2);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipClass, ParseValidTenF) {
    Ship s("1 H 10F");
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.row(), 10);
    EXPECT_EQ(s.col(), 6);
}

TEST(ShipClass, ParseValidTenA) {
    Ship s("3 H 10a");
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 10);
    EXPECT_EQ(s.col(), 10);
}

TEST(ShipClass, ParseValidLowercaseDirection) {
    Ship s("1 h 2H");
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.row(), 2);
    EXPECT_EQ(s.col(), 8);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipClass, ParseInvalidSize) {
    EXPECT_THROW(Ship s("5 H 4 B"), std::logic_error);
    EXPECT_THROW(Ship s("0 H 4 B"), std::logic_error);
}

TEST(ShipClass, ParseInvalidDirection) {
    EXPECT_THROW(Ship s("1 X 4 B"), std::logic_error);
}

TEST(ShipClass, ParseInvalidPlacement) {
    EXPECT_THROW(Ship s("4 H 1 B"), std::logic_error);
}

TEST(ShipClass, ParseInvalidFormat) {
    EXPECT_THROW(Ship s(""), std::logic_error);
    EXPECT_THROW(Ship s("H 1 4B"), std::logic_error);
    EXPECT_THROW(Ship s("1 H"), std::logic_error);
}