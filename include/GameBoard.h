/**
 * \file GameBoard.h
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/09
 * \date Last modified 2019/03/25
 * \brief Defines the gameboard class for the game
 */
#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

//Importation
#include "CardTypes.h"
#include "CardStack.h"
#include <vector>

//Define constant and type
/**
 * \brief Size of tableau
 */
#define TAB_SIZE 10
/**
 * \brief Size of foundation
 */
#define FOUND_SIZE 8
/**
 * \brief Defines the type of an natural number
 */
typedef unsigned int naturalNumber;

/**
 * \brief The gameboard class for the game
 */
class BoardT {
    private:
        CardStackT tableau[TAB_SIZE];
        CardStackT foundation[FOUND_SIZE];
        CardStackT deck;
        CardStackT waste;
        bool is_valid_pos(CategoryT category, naturalNumber number);
        bool tab_placeable(CardT card1, CardT card2);
        bool foundation_placeable(CardT card1, CardT card2);
    public:
        /**
         * \brief Default constructor method for the class
         */
        BoardT();
        /**
         * \brief Constructor method of the class.
         * \details First 40 cards goes into the tableau, the rest of cards goes to deck.
         * \param cards Sequence of cards
         * \throws invalid_argument invalid argument exception when the cards given is not exactly two deck.
         */
        BoardT(std::vector<CardT> cards);
        /**
         * \brief Check if the move (from the tableau) is valid
         * \param category Category of the destination
         * \param origin Place of card being moved
         * \param destination Place the card is being moved to
         * \return True if valid, false otherwise
         * \throws out_of_range Location is not valid
         */
        bool is_valid_tab_mv(CategoryT category, naturalNumber origin, naturalNumber destination);
        /**
         * \brief Check if the move (from the waste) is valid
         * \param category Category of the destination
         * \param destination Place the card is being moved to
         * \return True if valid, false otherwise
         * \throws out_of_range Location is not valid
         * \throws invalid_argument No card in waste
         */
        bool is_valid_waste_mv(CategoryT category, naturalNumber destination);
        /**
         * \brief Check if the size of deck is bigger than 0
         * \return True if bigger, false otherwise
         */
        bool is_valid_deck_mv();
        /**
         * \brief Move a card from tableau to tableau or foundation
         * \param category Category of the destination
         * \param origin Place of card being moved
         * \param destination Place the card is being moved to
         * \throws invalid_argument Cannot move the card
         */
        void tab_mv(CategoryT category, naturalNumber origin, naturalNumber destination);
        /**
         * \brief Move a card from waste to tableau or foundation
         * \param category Category of the destination
         * \param destination Place the card is being moved to
         * \throws invalid_argument Cannot move the card
         */
        void waste_mv(CategoryT category, naturalNumber destination);
        /**
         * \brief Move a card from deck to waste
         * \throws invalid_argument Cannot move the card
         */
        void deck_mv();
        /**
         * \brief Return one of the tableaus on the game board
         * \param number The number of the tableau being returned
         * \return One of the tableaus
         * \throws invalid_argument Invalid position
         */
        CardStackT get_tab(naturalNumber number);
        /**
         * \brief Return one of the foundations on the game board
         * \param number The number of the foundation being returned
         * \return One of the foundations
         * \throws invalid_argument Invalid position
         */
        CardStackT get_foundation(naturalNumber number);
        /**
         * \brief Return the deck on the game board
         * \return deck
         */
        CardStackT get_deck();
        /**
         * \brief Return the waste on the game board
         * \return waste
         */
        CardStackT get_waste();
        /**
         * \brief Check if there exist any more valid moves
         * \return True if there exists, false otherwise
         */
        bool valid_mv_exists();
        /**
         * \brief Check if the player have won the game
         * \return True if won, false otherwise
         */
        bool is_win_state();
};

#endif
