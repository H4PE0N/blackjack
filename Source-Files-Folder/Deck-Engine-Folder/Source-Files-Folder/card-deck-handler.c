
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
			Card card = SUIT_RANK_CARD(suit, rank);
			deck[index++] = TURN_CARD_DOWN(card);
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

bool rank_within_cards(Card cards[], unsigned int rank)
{
	unsigned int amount = card_array_amount(cards);

	for(int index = 0; index < amount; index += 1)
	{
		if(CARD_RANK_MACRO(cards[index]) == rank) return true;
	}
	return false;
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

// FLAG: SHOW, DOWN, NONE
bool upside_cards_value(int* value, Card cards[])
{
	unsigned int amount = card_array_amount(cards);

	int tempValue = 0;
	int aceAmount = 0;

	for(int index = 0; index < amount; index += 1)
	{
		if(!deck_card_exists(cards[index])) return false;

		if(!CARD_SIDE_SHOW(cards[index])) continue;


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

// FLAG: SHOW, DOWN, NONE
// Instead of all "upside" and "hidden" functions
bool deal_upside_card(Card* card, Card* deck)
{
	unsigned int amount = card_array_amount(deck);

	if(amount <= 0) return false;

	*card = TURN_CARD_SHOW(deck[amount - 1]);

	deck[amount - 1] = CARD_NONE;

	return true;
}

bool deal_hidden_card(Card* card, Card* deck)
{
	unsigned int amount = card_array_amount(deck);

	if(amount <= 0) return false;

	*card = TURN_CARD_DOWN(deck[amount - 1]);

	deck[amount - 1] = CARD_NONE;

	return true;
}

bool deal_player_cards(Card* playerCards, Card* deck)
{
	if(!deal_upside_card(&playerCards[0], deck)) return false;
	if(!deal_upside_card(&playerCards[1], deck)) return false;

	return true;
}

bool deal_dealer_cards(Card* dealerCards, Card* deck)
{
	if(!deal_hidden_card(&dealerCards[0], deck)) return false;
	if(!deal_upside_card(&dealerCards[1], deck)) return false;

	return true;
}

bool deal_upside_cards(Card* cards, Card* deck, int amount)
{
	unsigned int deckAmount = card_array_amount(deck);

	if(!NUMBER_IN_BOUNDS(amount, 1, deckAmount)) return false;

	for(int index = 0; index < amount; index += 1)
	{
		if(!deal_upside_card(&cards[index], deck)) return false;
	}

	return true;
}
