
#ifndef DECK_ENGINE_STRUCTS_H
#define DECK_ENGINE_STRUCTS_H

typedef unsigned int Card;

extern const unsigned int RANK_NONE;
extern const unsigned int RANK_ACE;
extern const unsigned int RANK_TWO;
extern const unsigned int RANK_THREE;
extern const unsigned int RANK_FOUR;
extern const unsigned int RANK_FIVE;
extern const unsigned int RANK_SIX;
extern const unsigned int RANK_SEVEN;
extern const unsigned int RANK_EIGHT;
extern const unsigned int RANK_NINE;
extern const unsigned int RANK_TEN;
extern const unsigned int RANK_JACK;
extern const unsigned int RANK_QUEEN;
extern const unsigned int RANK_KING;

extern const unsigned int SUIT_NONE;
extern const unsigned int SUIT_DIMNDS;
extern const unsigned int SUIT_SPADES;
extern const unsigned int SUIT_HEARTS;
extern const unsigned int SUIT_CLUBS;
extern const unsigned int SUIT_JOKER;

extern const Card CARD_SUIT_MASK;
extern const Card CARD_RANK_MASK;

extern const Card CARD_SUIT_SHIFT;
extern const Card CARD_RANK_SHIFT;

extern const Card CARD_NONE;

#endif