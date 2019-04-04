/**
 * \file GameBoard.cpp
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/09
 * \date Last modified 2019/03/25
 * \brief Implimentation of the gameboard class for the game
 */
//Importation
#include "GameBoard.h"
#include <stdexcept>

/**
 * \brief Default constructor method for the class
 */
BoardT::BoardT() {
    for (int i = 0; i < TAB_SIZE; i++)
        tableau[i] = *(new CardStackT());
    for (int i = 0; i < FOUND_SIZE; i++)
        foundation[i] = *(new CardStackT());
    deck = *(new CardStackT());
    waste = *(new CardStackT());
}

/**
 * \brief Constructor method of the class.
 * \details First 40 cards goes into the tableau, the rest of cards goes to deck.
 * \param cards Sequence of cards
 * \throws invalid_argument invalid argument exception when the cards given is not exactly two deck.
 */
BoardT::BoardT(std::vector<CardT> cards) {
    //Declare variables
    int check[13][4] = {0};
    //Check if the given sequence of cards is exactly two deck
    if (cards.size() != 104)
        throw std::invalid_argument("");
    for (unsigned int i = 0; i < cards.size(); i++)
        check[cards[i].r-1][cards[i].s] += 1;
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            if (check[i][j] != 2)
                throw std::invalid_argument("");
        }
    }
    //Create the different sections of the game board
    for (int i = 0; i < TAB_SIZE; i++) {
        std::vector<CardT> temp(cards.begin()+(4*i), cards.begin()+(4*i+4));
        tableau[i] = *(new CardStackT(temp));
    }
    for (int i = 0; i < FOUND_SIZE; i++) {
        foundation[i] = *(new CardStackT());
    }
    std::vector<CardT> temp(cards.begin()+40, cards.begin()+104);
    deck = *(new CardStackT(temp));
    waste = *(new CardStackT());
}

/**
 * \brief Check if the move (from the tableau) is valid
 * \param category Category of the destination
 * \param origin Place of card being moved
 * \param destination Place the card is being moved to
 * \return True if valid, false otherwise
 * \throws out_of_range Location is not valid
 */
bool BoardT::is_valid_tab_mv(CategoryT category, naturalNumber origin, naturalNumber destination) {
    //Check for exception
    if (category == Tableau || category == Foundation) {
        if (!is_valid_pos(Tableau, origin) || !is_valid_pos(category, destination))
            throw std::out_of_range("");
    }
    //Check if the move is valid
    if (category == Deck || category == Waste)
        return false;
    if (tableau[origin].size() == 0)
        return false;
    else if (category == Tableau) {
        if (tableau[destination].size() == 0)
            return true;
        else
            return tab_placeable(tableau[origin].top(), tableau[destination].top());
    }
    else {
        if (foundation[destination].size() == 0)
            return tableau[origin].top().r == ACE;
        else
            return foundation_placeable(tableau[origin].top(), foundation[destination].top());
    }
}

/**
 * \brief Check if the move (from the waste) is valid
 * \param category Category of the destination
 * \param destination Place the card is being moved to
 * \return True if valid, false otherwise
 * \throws out_of_range Location is not valid
 * \throws invalid_argument No card in waste
 */
bool BoardT::is_valid_waste_mv(CategoryT category, naturalNumber destination) {
    //Check for exception
    if (category == Tableau || category == Foundation) {
        if (!is_valid_pos(category, destination))
            throw std::out_of_range("");
    }
    if (waste.size() == 0)
        throw std::invalid_argument("");
    //Check if the move is valid
    if (category == Deck || category == Waste)
        return false;
    else if (category == Tableau) {
        if (tableau[destination].size() == 0)
            return true;
        else
            return tab_placeable(waste.top(), tableau[destination].top());
    }
    else {
        if (foundation[destination].size() == 0)
            return waste.top().r == ACE;
        else
            return foundation_placeable(waste.top(), foundation[destination].top());
    }
}

/**
 * \brief Check if the size of deck is bigger than 0
 * \return True if bigger, false otherwise
 */
bool BoardT::is_valid_deck_mv() {
    return (deck.size() > 0);
}

/**
 * \brief Move a card from tableau to tableau or foundation
 * \param category Category of the destination
 * \param origin Place of card being moved
 * \param destination Place the card is being moved to
 * \throws invalid_argument Cannot move the card
 */
void BoardT::tab_mv(CategoryT category, naturalNumber origin, naturalNumber destination) {
    if (!is_valid_tab_mv(category, origin, destination))
        throw std::invalid_argument("");
    if (category == Tableau) {
        tableau[destination] = tableau[destination].push(tableau[origin].top());
        tableau[origin] = tableau[origin].pop();
    }
    else if (category == Foundation) {
        foundation[destination] = foundation[destination].push(tableau[origin].top());
        tableau[origin] = tableau[origin].pop();
    }
}

/**
 * \brief Move a card from waste to tableau or foundation
 * \param category Category of the destination
 * \param destination Place the card is being moved to
 * \throws invalid_argument Cannot move the card
 */
void BoardT::waste_mv(CategoryT category, naturalNumber destination) {
    if (!is_valid_waste_mv(category, destination))
        throw std::invalid_argument("");
    if (category == Tableau) {
        tableau[destination] = tableau[destination].push(waste.top());
        waste = waste.pop();
    }
    else if (category == Foundation) {
        foundation[destination] = foundation[destination].push(waste.top());
        waste = waste.pop();
    }
}

/**
 * \brief Move a card from deck to waste
 * \throws invalid_argument Cannot move the card
 */
void BoardT::deck_mv() {
    if (!is_valid_deck_mv())
        throw std::invalid_argument("");
    waste = waste.push(deck.top());
    deck = deck.pop();
}

/**
 * \brief Return one of the tableaus on the game board
 * \param number The number of the tableau being returned
 * \return One of the tableaus
 * \throws invalid_argument Invalid position
 */
CardStackT BoardT::get_tab(naturalNumber number) {
    if (!is_valid_pos(Tableau, number))
        throw std::out_of_range("");
    return tableau[number];
}

/**
 * \brief Return one of the foundations on the game board
 * \param number The number of the foundation being returned
 * \return One of the foundations
 * \throws invalid_argument Invalid position
 */
CardStackT BoardT::get_foundation(naturalNumber number) {
    if (!is_valid_pos(Foundation, number))
        throw std::out_of_range("");
    return foundation[number];
}

/**
 * \brief Return the deck on the game board
 * \return deck
 */
CardStackT BoardT::get_deck() {
    return deck;
}

/**
 * \brief Return the waste on the game board
 * \return waste
 */
CardStackT BoardT::get_waste() {
    return waste;
}

/**
 * \brief Check if there exist any more valid moves
 * \return True if there exists, false otherwise
 */
bool BoardT::valid_mv_exists() {
    //Check for move from deck
    if (is_valid_deck_mv())
        return true;
    //Check for move from tableau
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            if (is_valid_tab_mv(Tableau, i, j))
                return true;
        }
        for (int j = 0; j < FOUND_SIZE; j++) {
            if (is_valid_tab_mv(Foundation, i, j))
                return true;
        }
    }
    //Check for move from waste
    try {
        for (int i = 0; i < TAB_SIZE; i++) {
            if (is_valid_waste_mv(Tableau, i))
                return true;
        }
        for (int i = 0; i < FOUND_SIZE; i++) {
            if (is_valid_waste_mv(Foundation, i))
                return true;
        }
    } catch (std::invalid_argument &e) {}
    return false;
}

/**
 * \brief Check if the player have won the game
 * \return True if won, false otherwise
 */
bool BoardT::is_win_state() {
    bool win = true;
    for (int i = 0; i <= 7; i++) {
        if (foundation[i].size() == 0)
            win = false;
        else
            if (foundation[i].top().r != KING)
                win = false;
    }
    return win;
}

/**
 * \brief Check if the given location is a valid location
 * \param category Category of the location
 * \param number Exact location
 * \return True if valid, false otherwise
 */
bool BoardT::is_valid_pos(CategoryT category, naturalNumber number) {
    if (category == Tableau) {
        if (number >= 0 && number <= 9)
            return true;
        else
        	return false;
    }
    else if (category == Foundation) {
        if (number >= 0 && number <= 7)
            return true;
        else
        	return false;
    }
    else
        return true;
}

/**
 * \brief Check if you can place a card from tableau to tableau
 * \param card1 first card
 * \param card2 second card
 * \return True if you can, false otherwise
 */
bool BoardT::tab_placeable(CardT card1, CardT card2) {
    return (card1.s == card2.s && card1.r == card2.r-1);
}

/**
 * \brief Check if you can place a card from tableau to foundation
 * \param card1 first card
 * \param card2 second card
 * \return True if you can, false otherwise
 */
bool BoardT::foundation_placeable(CardT card1, CardT card2) {
    return (card1.s == card2.s && card1.r == card2.r+1);
}
