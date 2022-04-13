
#include "../Header-Files-Folder/master-include-file.h"

bool game_play_handler(Screen screen, Card* deck)
{
	/*
	1. Get cards
	2. Try to get close to 21
	- if you go over -> show results and return true
	3. The dealer gets their card
	4. The one with the best cards wins -> show results and return true

	- if you close the program -> return false

	*/

	// Get cards
	Card* playerCards = create_empty_deck(52);
	Card* dealerCards = create_empty_deck(52);


	deal_playing_cards(dealerCards, deck, 2);
	deal_playing_cards(playerCards, deck, 2);

	int playerValue = 0;

	// Try to get close to 21

	render_game_board(screen, playerCards, dealerCards);
	SDL_UpdateWindowSurface(screen.window);

	Event event;

	SDL_WaitEvent(&event);

	playing_cards_value(&playerValue, playerCards);

	while(playerValue < 21)
	{
		SDL_WaitEvent(&event);

		render_game_board(screen, playerCards, dealerCards);
		SDL_UpdateWindowSurface(screen.window);

		if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
		{
			free(playerCards);
			free(dealerCards);

			return false;
		}

		if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g))
		{
			break;
		}

		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_h)
		{
			unsigned int playerAmount = card_array_amount(playerCards);

			deal_playing_card(&playerCards[playerAmount], deck);
		}

		playing_cards_value(&playerValue, playerCards);
	}


	int dealerValue = 0;

	printf("player has enterd cards\n");

	playing_cards_value(&playerValue, playerCards);

	if(playerValue <= 21)
	{
		// The dealer gets their cards

		playing_cards_value(&dealerValue, dealerCards);

		bool hasAnAce = rank_within_cards(dealerCards, RANK_ACE);

		while(dealerValue < 21 && (dealerValue < 17 || (dealerValue < playerValue && hasAnAce) ))
		{
			printf("dealing another card to the dealer\n");

			unsigned int dealerAmount = card_array_amount(dealerCards);

			deal_playing_card(&dealerCards[dealerAmount], deck);

			playing_cards_value(&dealerValue, dealerCards);
			hasAnAce = rank_within_cards(dealerCards, RANK_ACE);
		}
	}

	// The one with the best cards wins -> show results and return true

	if(playerValue <= 21 && (playerValue > dealerValue ||  dealerValue > 21))
	{ // WIN

	}

	else if(playerValue < dealerValue || playerValue > 21)
	{ // LOSE
		
	}

	else if(playerValue == dealerValue && !(dealerValue > 21 && playerValue > 21))
	{ // SAME

	}

	render_game_board(screen, playerCards, dealerCards);
	render_result_screen(screen, playerValue, dealerValue);

	SDL_UpdateWindowSurface(screen.window);

	free(playerCards);
	free(dealerCards);

	Event eventosaurus;

	SDL_WaitEvent(&eventosaurus);

	while(!(eventosaurus.type == SDL_KEYDOWN && eventosaurus.key.keysym.sym == SDLK_SPACE))
	{
		SDL_WaitEvent(&eventosaurus);
	}

	return true;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	Screen screen;

	if(!setup_screen_struct(&screen, WINDOW_WIDTH, WINDOW_HEIGHT, "BlackJack"))
	{
		printf("Could not setup screen!\n");

		return false;
	}

	Card* deck = create_default_deck();
	shuffle_card_array(deck);

	int index = 0;

	while(game_play_handler(screen, deck) && index < 20)
	{
		index += 1;
	}

	printf("free deck and cards\n");
	free(deck);

	printf("free_screen_struct\n");
	free_screen_struct(screen);

	return false;
}