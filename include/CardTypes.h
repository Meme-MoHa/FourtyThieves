/**
 * \file CardTypes.h
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/09
 * \date Last modified 2019/03/17
 * \brief Defines the type of the card
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Total number of cards.
 */
#define TOTAL_CARD 104

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief Describes the suit of a card.
 */
enum SuitT {Heart, Diamond, Club, Spade};
 
/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief Describes the category of a card.
 */
enum CategoryT {Tableau, Foundation, Deck, Waste};

/**
 * \brief Describes a card as a tuple of suit and rank
 */
struct CardT {
    /**
     * \brief Suit of the card
     */
    SuitT s;
    /**
     * \brief Rank of the card
     */
    RankT r;
};

#endif
