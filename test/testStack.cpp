/**
 * \file testStack.cpp
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/18
 * \date Last modified 2019/03/22
 * \brief Unit testing for Stack/CardStack
 */
//Importation
#include "catch.h"
#include "CardTypes.h"
#include "Stack.h"
#include "CardStack.h"
#include <vector>
#include <stdexcept>



//===============================================================================================================================



//Testing unit for Stack/CardStack
//Test for normal, boundary and exception cases
TEST_CASE("Tests for Stack/CardStack", "[Stack/CardStack]") {
    
    //Variables needed for the testing
    std::vector<CardT> emptyCards;
    std::vector<CardT> cards;
    cards.push_back({static_cast<SuitT>(0), ACE});
    cards.push_back({static_cast<SuitT>(0), 2});
    cards.push_back({static_cast<SuitT>(0), 3});
    CardStackT emptyStack(emptyCards);
    CardStackT stack(cards);
    std::vector<CardT> tempStack;
    CardT tempCard;
    
    SECTION("Constructor and toSeq - normal") {
        tempStack = stack.toSeq();
        for (int i = 0; i < 3; i++) {
            REQUIRE(tempStack[i].r == i+1);
            REQUIRE(tempStack[i].s == 0);
        }
    }
    
    SECTION("Constructor and toSeq - boundary") {
        REQUIRE(emptyStack.toSeq().size() == 0);
    }
    
    SECTION("push - normal") {
        stack = stack.push({static_cast<SuitT>(0), KING});
        tempStack = stack.toSeq();
        REQUIRE(tempStack.size() == 4);
        REQUIRE(tempStack[3].r == KING);
        REQUIRE(tempStack[3].s == 0);
    }
    
    SECTION("push - boundary") {
        emptyStack = emptyStack.push({static_cast<SuitT>(0), KING});
        tempStack = emptyStack.toSeq();
        REQUIRE(tempStack[0].r == KING);
        REQUIRE(tempStack[0].s == 0);
    }
    
    SECTION("pop - normal") {
        tempStack = stack.pop().toSeq();
        REQUIRE(tempStack.size() == 2);
        REQUIRE(tempStack[1].r == 2);
        REQUIRE(tempStack[1].s == 0);
    }
    
    SECTION("pop - exception") {
        REQUIRE_THROWS_AS(emptyStack.pop(), std::out_of_range);
    }
    
    SECTION("top - normal") {
        tempCard = stack.top();
        REQUIRE(tempCard.r == 3);
        REQUIRE(tempCard.s == 0);
    }
    
    SECTION("top - exception") {
        REQUIRE_THROWS_AS(emptyStack.top(), std::out_of_range);
    }
    
    SECTION("size - normal") {
        REQUIRE(stack.size() == 3);
    }
    
    SECTION("size - boundary") {
        REQUIRE(emptyStack.size() == 0);
    }
    
}