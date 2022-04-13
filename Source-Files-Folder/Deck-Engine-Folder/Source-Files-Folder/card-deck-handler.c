
#include "../Header-Files-Folder/engine-include-file.h"

Card* create_empty_deck(unsigned int amount)
{
	Card* deck = malloc(sizeof(Card) * (amount + 1));

	for(int index = 0; index < (amount + 1); index += 1)
	{
		deck[index] = CARD_NONE;
	}
	return deck;
}

Card* create_default_deck()
{
	Card* deck = malloc(sizeof(Card) * (DECK_CARDS + 1));

	unsigned int index = 0;

	for(int suit = 1; suit <= DECK_SUITS; suit += 1)
	{
		for(int rank = 1; rank <= DECK_RANKS; rank += 1)
		{
			deck[index++] = SUIT_RANK_CARD(suit, rank);
		}
	}

	deck[DECK_CARDS] = CARD_NONE;

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

bool deal_playing_card(Card* card, Card* deck)
{
	unsigned int amount = card_array_amount(deck);

	if(amount <= 0) return false;

	*card = deck[amount - 1];

	deck[amount - 1] = CARD_NONE;

	return true;
}

bool playing_cards_value(int* value, Card cards[])
{
	unsigned int amount = card_array_amount(cards);

	int tempValue = 0;
	int aceAmount = 0;

	for(int index = 0; index < amount; index += 1)
	{
		if(!deck_card_exists(cards[index])) return false;


		unsigned int rank = CARD_RANK_MACRO(cards[index]);

		if(NUMBER_IN_BOUNDS(rank, 2, 10)) tempValue += rank;

		else if(NUMBER_IN_BOUNDS(rank, 11, 13)) tempValue += 10;

		else if(rank == 1) aceAmount += 1;
	}

	for(int index = 0; index < aceAmount; index += 1)
	{
		if(tempValue + 11 <= 21) tempValue += 11;

		else tempValue += 1;
	}

	*value = tempValue;

	return true;
}

int create_random_int(int minimum, int maximum)
{
	return (rand() % (maximum - minimum)) + minimum;
}

void shuffle_card_array(Card* cards)
{
	unsigned int amount = card_array_amount(cards);

	for(int index = 0; index < amount; index += 1)
	{
		int randomIndex = create_random_int(0, amount - 1);
		Card temp = cards[index];
		cards[index] = cards[randomIndex];
		cards[randomIndex] = temp;
	}
}

bool deal_playing_cards(Card* cards, Card* deck, int amount)
{
	unsigned int deckAmount = card_array_amount(deck);

	if(!NUMBER_IN_BOUNDS(amount, 1, deckAmount)) return false;

	for(int index = 0; index < amount; index += 1)
	{
		if(!deal_playing_card(&cards[index], deck)) return false;
	}

	return true;
}
