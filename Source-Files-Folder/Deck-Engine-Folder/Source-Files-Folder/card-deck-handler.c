
#include "../Header-Files-Folder/engine-include-file.h"

Card* create_empty_deck(unsigned int amount)
{
	Card* deck = malloc(sizeof(Card) * amount);

	for(int index = 0; index < amount; index += 1)
	{
		deck[index] = SUIT_RANK_CARD(SUIT_NONE, RANK_NONE);
	}
	return deck;
}

Card* create_default_deck()
{
	unsigned int SUITS_ARRAY[] = {SUIT_DIMNDS, SUIT_SPADES, SUIT_HEARTS, SUIT_CLUBS};
	unsigned int RANKS_ARRAY[] = {RANK_ACE, RANK_TWO, RANK_THREE, RANK_FOUR, RANK_FIVE, RANK_SIX, RANK_SEVEN, RANK_EIGHT, RANK_NINE, RANK_TEN, RANK_JACK, RANK_QUEEN, RANK_KING};

	Card* deck = malloc(sizeof(Card) * DECK_CARDS);

	unsigned int index = 0;

	for(int suitIndex = 0; suitIndex < DECK_SUITS; suitIndex += 1)
	{
		for(int RANKIndex = 0; RANKIndex < DECK_RANKS; RANKIndex += 1)
		{
			deck[index++] = SUIT_RANK_CARD(SUITS_ARRAY[suitIndex], RANKS_ARRAY[RANKIndex]);
		}
	}
	return deck;
}