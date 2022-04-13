
#ifndef CARD_DECK_HANDLER_H
#define CARD_DECK_HANDLER_H

Card* create_empty_deck(unsigned int);

Card* create_default_deck();

bool card_rank_exists(Card);

bool card_suit_exists(Card);

bool deck_card_exists(Card);

unsigned int card_array_amount(Card[]);

#endif