
#ifndef CARD_DECK_HANDLER_H
#define CARD_DECK_HANDLER_H

Card* create_empty_deck(unsigned int);

Card* create_default_deck();

bool card_rank_exists(Card);

bool card_suit_exists(Card);

bool deck_card_exists(Card);

unsigned int card_array_amount(Card[]);

bool deal_playing_card(Card*, Card*);

bool deal_playing_cards(Card*, Card*, int);

bool playing_card_value(int*, Card);

bool playing_cards_value(int*, Card[]);

int create_random_int(int, int);

void shuffle_card_array(Card*);

#endif