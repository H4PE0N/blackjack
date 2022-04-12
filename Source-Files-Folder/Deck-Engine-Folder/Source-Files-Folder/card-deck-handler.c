
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
	Card* deck = malloc(sizeof(Card) * DECK_CARDS);

	unsigned int index = 0;

	for(int suit = 1; suit <= DECK_SUITS; suit += 1)
	{
		for(int rank = 1; rank <= DECK_RANKS; rank += 1)
		{
			deck[index++] = SUIT_RANK_CARD(suit, rank);
		}
	}
	return deck;
}