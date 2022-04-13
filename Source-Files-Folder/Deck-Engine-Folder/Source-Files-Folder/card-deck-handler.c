
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

bool card_rank_exists(Card card)
{
	unsigned int rank = CARD_RANK_MACRO(card);

	return NUMBER_IN_BOUNDS(rank, 1, 13);
}

bool card_suit_exists(Card card)
{
	unsigned int suit = CARD_SUIT_MACRO(card);

	return NUMBER_IN_BOUNDS(suit, 1, 5);
}

bool deck_card_exists(Card card)
{
	bool suitExists = card_suit_exists(card);
	bool rankExists = card_rank_exists(card);

	return (suitExists && rankExists);
}

unsigned int card_array_amount(Card cardArray[])
{
	unsigned int amount = 0;

	while(deck_card_exists(cardArray[amount])) amount += 1;

	return amount;
}