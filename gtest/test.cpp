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
    EXPECT_TRUE(is_row(p.getRow()));
    EXPECT_TRUE(is_col(p.getCharCol()));
    EXPECT_TRUE(p.getCol() >= 1);
    EXPECT_TRUE(p.getCol() <= 10);
}

TEST(PositionClass, ValidValues) {
    Position p(4, 2);
    EXPECT_EQ(p.getRow(), 4);
    EXPECT_EQ(p.getCol(), 2);
    EXPECT_EQ(p.getCharCol(), 'B');
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
    EXPECT_EQ(p.getRow(), 1);
    EXPECT_EQ(p.getCol(), 1);
}

TEST(PositionClass, ValidLowercase) {
    Position p(10, 'j');
    EXPECT_EQ(p.getRow(), 10);
    EXPECT_EQ(p.getCol(), 10);
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
    EXPECT_EQ(b.getRow(), 3);
    EXPECT_EQ(b.getCol(), 4);
    EXPECT_EQ(b.getCharCol(), 'D');
}


TEST(PositionClass, ParsesSimple) {
    Position p("4B");
    EXPECT_EQ(p.getRow(), 4);
    EXPECT_EQ(p.getCol(), 2);
}

TEST(PositionClass, ParsesWithSpace) {
    Position p("8 F");
    EXPECT_EQ(p.getRow(), 8);
    EXPECT_EQ(p.getCol(), 6);
}

TEST(PositionClass, ParsesLowercase) {
    Position p("4e");
    EXPECT_EQ(p.getRow(), 4);
    EXPECT_EQ(p.getCol(), 5);
}

TEST(PositionClass, ParsesWithSpacesAround) {
    Position p("  1 A  ");
    EXPECT_EQ(p.getRow(), 1);
    EXPECT_EQ(p.getCol(), 1);
}

TEST(PositionClass, ParsesTen) {
    Position p("10 F");
    EXPECT_EQ(p.getRow(), 10);
    EXPECT_EQ(p.getCol(), 6);
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
    EXPECT_EQ(p.getRow(), 4);
    EXPECT_EQ(p.getCol(), 2);
}

TEST(PositionClass, InvalidInputs) {
    Position p(1, 1);
    EXPECT_FALSE(parse("0 A", p));
    EXPECT_FALSE(parse("2 2", p));
    EXPECT_FALSE(parse("", p));
    EXPECT_FALSE(parse("A1", p));
    EXPECT_FALSE(parse("1 K", p));
}