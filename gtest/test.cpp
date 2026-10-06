#include "pch.h"
#include "Position.h"
#include "Ship.h"
#include "GameField.h"
#include "Player.h"
#include "Game.h"

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
    EXPECT_TRUE(is_collision(4, Position(1, 7), Horizontal));   
}

TEST(ShipClass, IsCollisionHorizontalDoesNotFit) {
    EXPECT_FALSE(is_collision(4, Position(1, 8), Horizontal));  
}

TEST(ShipClass, IsCollisionVerticalFits) {
    EXPECT_TRUE(is_collision(4, Position(7, 1), Vertical));     
}

TEST(ShipClass, IsCollisionVerticalDoesNotFit) {
    EXPECT_FALSE(is_collision(4, Position(8, 1), Vertical));    
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
    EXPECT_THROW(Ship s(4, Position(1, 8), Horizontal), std::logic_error);
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
    EXPECT_THROW(Ship s(4, 'H', 1, 'H'), std::logic_error);
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
    EXPECT_EQ(s.col(), 1);
    EXPECT_EQ(s.direction(), Horizontal);
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
    EXPECT_THROW(Ship s("4 H 1 H"), std::logic_error);
}

TEST(ShipClass, ParseInvalidFormat) {
    EXPECT_THROW(Ship s(""), std::logic_error);
    EXPECT_THROW(Ship s("H 1 4B"), std::logic_error);
    EXPECT_THROW(Ship s("1 H"), std::logic_error);
}

TEST(GameFieldClass, DefaultEmptyField) {
    GameField f;
    std::string s = to_string(f, true);
    EXPECT_TRUE(s.find("  |A B C D E F G H I J|") != std::string::npos);
    EXPECT_TRUE(s.find("  +-------------------+") != std::string::npos);
    EXPECT_TRUE(s.find("1 | | | | | | | | | | |") != std::string::npos);
    EXPECT_TRUE(s.find("10 | | | | | | | | | | |") != std::string::npos);
}

TEST(GameFieldClass, PlaceShipAndShow) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    std::string s = to_string(f, true);
    EXPECT_TRUE(s.find("1 |*| | | | | | | | | |") != std::string::npos);
}

TEST(GameFieldClass, PlaceShipHidden) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    std::string s = to_string(f);
    EXPECT_TRUE(s.find("1 | | | | | | | | | | |") != std::string::npos);
}

TEST(GameFieldClass, MissReturnsMissed) {
    GameField f;
    EXPECT_EQ(f.set(1, 'A'), Missed);
}

TEST(GameFieldClass, MissRendersDot) {
    GameField f;
    f.set(1, 'A');
    std::string s = to_string(f);
    EXPECT_TRUE(s.find("1 |.| | | | | | | | | |") != std::string::npos);
}

TEST(GameFieldClass, LowercaseMoveValid) {
    GameField f;
    EXPECT_EQ(f.set(1, 'a'), Missed);
}


TEST(GameFieldClass, HitSingleShipDestroyed) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    EXPECT_EQ(f.set(1, 'A'), BoatDestroyed);
}

TEST(GameFieldClass, HitTwoShipNotDestroyed) {
    GameField f;
    f.set(Ship(2, Position(1, 'B'), Horizontal));
    EXPECT_EQ(f.set(1, 'B'), Hit);
}

TEST(GameFieldClass, HitTwoShipDestroyed) {
    GameField f;
    f.set(Ship(2, Position(1, 'B'), Horizontal));
    f.set(1, 'B');
    EXPECT_EQ(f.set(1, 'C'), DestroyersDestroyed);
}

TEST(GameFieldClass, HitThreeShipDestroyed) {
    GameField f;
    f.set(Ship(3, Position(1, 'B'), Horizontal));
    f.set(1, 'B');
    f.set(1, 'C');
    EXPECT_EQ(f.set(1, 'D'), CruisersDestroyed);
}

TEST(GameFieldClass, HitFourShipDestroyed) {
    GameField f;
    f.set(Ship(4, Position(1, 'B'), Horizontal));
    f.set(1, 'B');
    f.set(1, 'C');
    f.set(1, 'D');
    EXPECT_EQ(f.set(1, 'E'), BattleshipDestroyed);
}

TEST(GameFieldClass, RepeatedMoveThrows) {
    GameField f;
    f.set(1, 'A');
    EXPECT_THROW(f.set(1, 'A'), std::logic_error);
}

TEST(GameFieldClass, MoveOutOfBoundsThrows) {
    GameField f;
    EXPECT_THROW(f.set(0, 'A'), std::logic_error);
    EXPECT_THROW(f.set(11, 'A'), std::logic_error);
    EXPECT_THROW(f.set(1, 'K'), std::logic_error);
}

TEST(GameFieldClass, CollisionWithNeighbor) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    EXPECT_TRUE(is_collision(f, Ship(1, Position(1, 'B'), Horizontal)));
}

TEST(GameFieldClass, CollisionWithDiagonal) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    EXPECT_TRUE(is_collision(f, Ship(1, Position(2, 'A'), Horizontal)));
    EXPECT_TRUE(is_collision(f, Ship(1, Position(2, 'B'), Horizontal)));
}

TEST(GameFieldClass, CollisionSameCell) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    EXPECT_TRUE(is_collision(f, Ship(1, Position(1, 'A'), Horizontal)));
}

TEST(GameFieldClass, NoCollisionFar) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    EXPECT_FALSE(is_collision(f, Ship(1, Position(1, 'C'), Horizontal)));
    EXPECT_FALSE(is_collision(f, Ship(1, Position(3, 'A'), Horizontal)));
}

TEST(GameFieldClass, SetCollidingShipThrows) {
    GameField f;
    f.set(Ship(1, Position(1, 'A'), Horizontal));
    EXPECT_THROW(f.set(Ship(1, Position(1, 'B'), Horizontal)), std::logic_error);
}

TEST(PlayerClass, DefaultNotReady) {
    Player p;
    EXPECT_FALSE(p.check_ready());
}

TEST(PlayerClass, DefaultNotLose) {
    Player p;
    EXPECT_FALSE(p.check_lose());
}

TEST(PlayerClass, SetOneShipOk) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    EXPECT_FALSE(p.check_ready());
}

TEST(PlayerClass, SetAllShipsReady) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    p.set_ship(Ship("1 H 1 C"));
    p.set_ship(Ship("1 H 1 E"));
    p.set_ship(Ship("1 H 1 G"));
    p.set_ship(Ship("2 H 3 A"));
    p.set_ship(Ship("2 H 3 D"));
    p.set_ship(Ship("2 H 3 G"));
    p.set_ship(Ship("3 H 5 A"));
    p.set_ship(Ship("3 H 5 E"));
    p.set_ship(Ship("4 H 8 A"));
    EXPECT_TRUE(p.check_ready());
}

TEST(PlayerClass, SetTooManyOneDeckers) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    p.set_ship(Ship("1 H 1 C"));
    p.set_ship(Ship("1 H 1 E"));
    p.set_ship(Ship("1 H 1 G"));
    EXPECT_THROW(p.set_ship(Ship("1 H 1 I")), std::logic_error);
}

TEST(PlayerClass, SetTooManyTwoDeckers) {
    Player p;
    p.set_ship(Ship("2 H 1 A"));
    p.set_ship(Ship("2 H 3 A"));
    p.set_ship(Ship("2 H 5 A"));
    EXPECT_THROW(p.set_ship(Ship("2 H 7 A")), std::logic_error);
}

TEST(PlayerClass, SetCollidingShipThrows) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    EXPECT_THROW(p.set_ship(Ship("1 H 1 B")), std::logic_error);
}

TEST(PlayerClass, SetActionMiss) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    EXPECT_EQ(p.set_action(1, 'C'), Missed);
}

TEST(PlayerClass, SetActionHitFirst) {
    Player p;
    p.set_ship(Ship("2 H 1 A"));
    EXPECT_EQ(p.set_action(1, 'A'), Hit);
}

TEST(PlayerClass, SetActionDestroyTwoDeck) {
    Player p;
    p.set_ship(Ship("2 H 1 A"));
    p.set_action(1, 'A');
    EXPECT_EQ(p.set_action(1, 'B'), DestroyersDestroyed);
}

TEST(PlayerClass, SetActionDestroyOneDeck) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    EXPECT_EQ(p.set_action(1, 'A'), BoatDestroyed);
}

TEST(PlayerClass, SetActionInvalidMove) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    p.set_action(1, 'A');
    EXPECT_THROW(p.set_action(1, 'A'), std::logic_error);
}

TEST(PlayerClass, ReadyAfterAllPlaced) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    p.set_ship(Ship("1 H 1 C"));
    p.set_ship(Ship("1 H 1 E"));
    p.set_ship(Ship("1 H 1 G"));
    p.set_ship(Ship("2 H 3 A"));
    p.set_ship(Ship("2 H 3 D"));
    p.set_ship(Ship("2 H 3 G"));
    p.set_ship(Ship("3 H 5 A"));
    p.set_ship(Ship("3 H 5 E"));
    p.set_ship(Ship("4 H 8 A"));
    EXPECT_TRUE(p.check_ready());
}

TEST(PlayerClass, NotLoseWhileSomeShipsAlive) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    p.set_ship(Ship("1 H 1 C"));
    p.set_action(1, 'A');
    EXPECT_FALSE(p.check_lose());
}

TEST(PlayerClass, LoseAfterAllDestroyed) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));
    p.set_action(1, 'A');
    EXPECT_TRUE(p.check_lose());
}

TEST(PlayerClass, ShowFieldEmptyHasShipsLeft) {
    Player p;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    p.show_field();
    std::cout.rdbuf(old);

    const std::string s = buffer.str();
    EXPECT_TRUE(s.find("Ships Left:") != std::string::npos);
    EXPECT_TRUE(s.find("* - 0 ** - 0 *** - 0 **** - 0") != std::string::npos);
}

TEST(PlayerClass, ShowFieldAfterOneShipPlaced) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    p.show_field();
    std::cout.rdbuf(old);

    const std::string s = buffer.str();
    EXPECT_TRUE(s.find("* - 1 ** - 0 *** - 0 **** - 0") != std::string::npos);
}

TEST(PlayerClass, ShowFieldHidesShipWhenAsked) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    p.show_field(true);
    std::cout.rdbuf(old);

    const std::string s = buffer.str();
    EXPECT_TRUE(s.find("1 | | | | | | | | | | |") != std::string::npos);
}

TEST(PlayerClass, ShowFieldShowsShipByDefault) {
    Player p;
    p.set_ship(Ship("1 H 1 A"));

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    p.show_field();
    std::cout.rdbuf(old);

    const std::string s = buffer.str();
    EXPECT_TRUE(s.find("1 |*| | | | | | | | | |") != std::string::npos);
}

TEST(GameClass, ConstructsOk) {
    Game g;
    SUCCEED();
}

TEST(GameClass, UserWinsFullFleet) {
    std::stringstream input;

    input << "1 H 1 A\n";
    input << "1 H 1 C\n";
    input << "1 H 1 E\n";
    input << "1 H 1 G\n";
    input << "2 H 3 A\n";
    input << "2 H 3 D\n";
    input << "2 H 3 G\n";
    input << "3 H 5 A\n";
    input << "3 H 5 E\n";
    input << "4 H 7 A\n";
    input << "\n";

    input << "1 H 1 A\n";
    input << "1 H 1 C\n";
    input << "1 H 1 E\n";
    input << "1 H 1 G\n";
    input << "2 H 3 A\n";
    input << "2 H 3 D\n";
    input << "2 H 3 G\n";
    input << "3 H 5 A\n";
    input << "3 H 5 E\n";
    input << "4 H 7 A\n";
    input << "\n";

    input << "1 A\n";
    input << "1 C\n";
    input << "1 E\n";
    input << "1 G\n";
    input << "3 A\n";
    input << "3 B\n";
    input << "3 D\n";
    input << "3 E\n";
    input << "3 G\n";
    input << "3 H\n";
    input << "5 A\n";
    input << "5 B\n";
    input << "5 C\n";
    input << "5 E\n";
    input << "5 F\n";
    input << "5 G\n";
    input << "7 A\n";
    input << "7 B\n";
    input << "7 C\n";
    input << "7 D\n";

    std::streambuf* old_in = std::cin.rdbuf(input.rdbuf());

    std::stringstream output;
    std::streambuf* old_out = std::cout.rdbuf(output.rdbuf());

    Game g;
    g.start();

    std::cin.rdbuf(old_in);
    std::cout.rdbuf(old_out);

    const std::string s = output.str();
    EXPECT_TRUE(s.find("USER WIN!") != std::string::npos);
}
