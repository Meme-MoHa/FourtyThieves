/**
 * \file testBoard.cpp
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/18
 * \date Last modified 2019/03/22
 * \brief Unit testing for GameBoard
 */
//Importation
#include "catch.h"
#include "CardTypes.h"
#include "Stack.h"
#include "CardStack.h"
#include "GameBoard.h"
#include <vector>
#include <stdexcept>



//===============================================================================================================================



//Testing unit for GameBoard
//Test for normal, boundary and exception cases
TEST_CASE("Tests for GameBoard", "[GameBoard]") {
    
    //Variables needed for testing
    std::vector<CardT> deck;
    for (RankT rank = ACE; rank <= KING; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = {static_cast<SuitT>(suit), rank};
            deck.push_back(n);
            deck.push_back(n);
        }
    }
    CardT temp = deck[3];
    deck[3] = deck[15];
    deck[15] = temp;
    temp = deck[103];
    deck[103] = deck[6];
    deck[6] = temp;
    BoardT board(deck);
    std::vector<CardT> tempStack;
    
    SECTION("Constructor, get_tab, get_foundation, get_deck, get_waste - normal") {
        REQUIRE(board.get_waste().size() == 0);
        for (int i = 0; i < FOUND_SIZE; i++)
            REQUIRE(board.get_foundation(i).size() == 0);
        int check[13][4] = {0};
        tempStack = board.get_deck().toSeq();
        for (unsigned int i = 0; i < tempStack.size(); i++)
            check[tempStack[i].r-1][tempStack[i].s] += 1;
        for (int i = 0; i < TAB_SIZE; i++) {
            tempStack = board.get_tab(i).toSeq();
            for (unsigned int j = 0; j < tempStack.size(); j++)
                check[tempStack[j].r-1][tempStack[j].s] += 1;
        }
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4; j++) {
                REQUIRE(check[i][j] == 2);
            }
        }
    }
    
    SECTION("Constructor - exception") {
        std::vector<CardT> badDeck;
        for (RankT rank = ACE; rank <= QUEEN; rank++) {
            for (unsigned int suit = 0; suit < 4; suit++) {
                CardT n = {static_cast<SuitT>(suit), rank};
                badDeck.push_back(n);
                badDeck.push_back(n);
            }
        }
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = {static_cast<SuitT>(suit), ACE};
            badDeck.push_back(n);
            badDeck.push_back(n);
        }
        REQUIRE_THROWS_AS(new BoardT(badDeck), std::invalid_argument);
    }
    
    SECTION("is_valid_tab_mv - normal") {
        REQUIRE(board.is_valid_tab_mv(Tableau, 1, 0));
        REQUIRE(!board.is_valid_tab_mv(Tableau, 0, 1));
        REQUIRE(board.is_valid_tab_mv(Foundation, 1, 0));
        REQUIRE(!board.is_valid_tab_mv(Foundation, 0, 0));
        REQUIRE(!board.is_valid_tab_mv(Deck, 1, 0));
        REQUIRE(!board.is_valid_tab_mv(Waste, 1, 0));
    }
    
    SECTION("is_valid_tab_mv - exception") {
        REQUIRE_THROWS_AS(board.is_valid_tab_mv(Tableau, 59, 99), std::out_of_range);
    }
    
    SECTION("is_valid_waste_mv - normal") {
        board.deck_mv();
        REQUIRE(board.is_valid_waste_mv(Tableau, 0));
        REQUIRE(!board.is_valid_waste_mv(Tableau, 1));
        REQUIRE(board.is_valid_waste_mv(Foundation, 0));
        REQUIRE(!board.is_valid_waste_mv(Deck, 0));
        REQUIRE(!board.is_valid_waste_mv(Waste, 0));
    }
    
    SECTION("is_valid_waste_mv - exception") {
        REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 59), std::out_of_range);
    }
    
    SECTION("is_valid_deck_mv") {
        for (int i = 0; i < 64; i++) {
            REQUIRE(board.is_valid_deck_mv());
            board.deck_mv();
        }
        REQUIRE(!board.is_valid_deck_mv());
    }
    
    SECTION("tab_mv - normal 1") {
        board.tab_mv(Tableau, 1, 0);
        tempStack = board.get_tab(0).toSeq();
        REQUIRE(tempStack.size() == 5);
        REQUIRE(tempStack[4].r == ACE);
        REQUIRE(tempStack[4].s == 3);
        tempStack = board.get_tab(1).toSeq();
        REQUIRE(tempStack.size() == 3);
        REQUIRE(tempStack[2].r == KING);
        REQUIRE(tempStack[2].s == 3);
    }
    
    SECTION("tab_mv - normal 2") {
        board.tab_mv(Foundation, 1, 0);
        tempStack = board.get_tab(1).toSeq();
        REQUIRE(tempStack.size() == 3);
        REQUIRE(tempStack[2].r == KING);
        REQUIRE(tempStack[2].s == 3);
        tempStack = board.get_foundation(0).toSeq();
        REQUIRE(tempStack.size() == 1);
        REQUIRE(tempStack[0].r == ACE);
        REQUIRE(tempStack[0].s == 3);
    }
    
    SECTION("tab_mv - exception") {
        REQUIRE_THROWS_AS(board.tab_mv(Tableau, 0, 1), std::invalid_argument);
        REQUIRE_THROWS_AS(board.tab_mv(Foundation, 0, 0), std::invalid_argument);
        REQUIRE_THROWS_AS(board.tab_mv(Deck, 1, 0), std::invalid_argument);
        REQUIRE_THROWS_AS(board.tab_mv(Waste, 1, 0), std::invalid_argument);
    }
    
    SECTION("waste_mv - normal 1") {
        board.deck_mv();
        board.waste_mv(Tableau, 0);
        tempStack = board.get_tab(0).toSeq();
        REQUIRE(tempStack.size() == 5);
        REQUIRE(tempStack[4].r == ACE);
        REQUIRE(tempStack[4].s == 3);
        REQUIRE(board.get_waste().toSeq().size() == 0);
    }
    
    SECTION("waste_mv - normal 2") {
        board.deck_mv();
        board.waste_mv(Foundation, 0);
        tempStack = board.get_foundation(0).toSeq();
        REQUIRE(tempStack.size() == 1);
        REQUIRE(tempStack[0].r == ACE);
        REQUIRE(tempStack[0].s == 3);
        REQUIRE(board.get_waste().toSeq().size() == 0);
    }
    
    SECTION("waste_mv - exception") {
        board.deck_mv();
        REQUIRE_THROWS_AS(board.waste_mv(Tableau, 1), std::invalid_argument);
        REQUIRE_THROWS_AS(board.waste_mv(Deck, 0), std::invalid_argument);
        REQUIRE_THROWS_AS(board.waste_mv(Waste, 0), std::invalid_argument);
    }
    
    SECTION("deck_mv - normal") {
        board.deck_mv();
        REQUIRE(board.get_deck().toSeq().size() == 63);
        tempStack = board.get_waste().toSeq();
        REQUIRE(tempStack.size() == 1);
        REQUIRE(tempStack[0].r == ACE);
        REQUIRE(tempStack[0].s == 3);
    }
    
    SECTION("deck_mv - exception") {
        for (int i = 0; i < 64; i++)
            board.deck_mv();
        REQUIRE_THROWS_AS(board.deck_mv(), std::invalid_argument);
    }
    
    SECTION("valid_mv_exists") {
        REQUIRE(board.valid_mv_exists());
    }
    
    SECTION("is_win_state") {
        int count;
        std::vector<CardT> tempDeck;
        for (RankT rank = ACE; rank <= KING; rank++) {
            for (unsigned int suit = 0; suit < 4; suit++) {
                CardT n = {static_cast<SuitT>(suit), rank};
                tempDeck.push_back(n);
                tempDeck.push_back(n);
            }
        }
        BoardT tempBoard(tempDeck);
        REQUIRE(!tempBoard.is_win_state());
        for (int i = 0; i < 64; i++)
            tempBoard.deck_mv();
        for (int i = 0; i < 10; i+=2) {
            for (int j = 3; j >= 0; j--) {
                tempBoard.tab_mv(Foundation, i, j);
                tempBoard.tab_mv(Foundation, i+1, j+4);
            }
        }
        for (int i = 0; i < 64; i++)
            tempBoard.waste_mv(Foundation, i%8);
        REQUIRE(tempBoard.is_win_state());
    }
    
}