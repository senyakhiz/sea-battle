#include "pch.h"
#include "Position.h"

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