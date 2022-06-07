
#include "../Header-Files-Folder/master-include-file.h"

bool game_play_handler(Screen screen, Card* deck, int* playerMoney)
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

	shuffle_card_array(deck);

	Card* playerCards = create_empty_deck(8);
	Card* dealerCards = create_empty_deck(8);

	int playerStake = 0;


	render_game_board(screen, playerCards, dealerCards, deck, playerStake, *playerMoney);
	SDL_UpdateWindowSurface(screen.window);


	Event eventis;

	SDL_WaitEvent(&eventis);

	while(playerStake <= 0)
	{
		SDL_WaitEvent(&eventis);

		if(eventis.type == SDL_QUIT || (eventis.type == SDL_KEYDOWN && eventis.key.keysym.sym == SDLK_q))
		{
			free(playerCards);
			free(dealerCards);

			return false;
		}

		else if(eventis.type == SDL_KEYDOWN && eventis.key.keysym.sym == SDLK_1)
		{
			playerStake = 25;
		}

		else if(eventis.type == SDL_KEYDOWN && eventis.key.keysym.sym == SDLK_2)
		{
			playerStake = 50;
		}

		else if(eventis.type == SDL_KEYDOWN && eventis.key.keysym.sym == SDLK_3)
		{
			playerStake = 75;
		}
	}

	*playerMoney -= playerStake;



	if(!deal_dealer_cards(dealerCards, deck))
	{
		free(playerCards);
		free(dealerCards);

		return false;
	}
	if(!deal_player_cards(playerCards, deck))
	{
		free(playerCards);
		free(dealerCards);

		return false;
	}

	int playerValue = 0;

	// Try to get close to 21

	render_game_board(screen, playerCards, dealerCards, deck, playerStake, *playerMoney);
	SDL_UpdateWindowSurface(screen.window);

	Event event;

	SDL_WaitEvent(&event);

	playing_cards_value(&playerValue, playerCards);

	while(playerValue < 21)
	{
		SDL_WaitEvent(&event);

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

			if(!deal_upside_card(&playerCards[playerAmount], deck))
			{
				free(playerCards);
				free(dealerCards);

				return false;
			}

			render_game_board(screen, playerCards, dealerCards, deck, playerStake, *playerMoney);
			SDL_UpdateWindowSurface(screen.window);

			playing_cards_value(&playerValue, playerCards);
		}
	}
	// The dealer gets their cards

	unsigned int dAmount = card_array_amount(dealerCards);
	for(int index = 0; index < dAmount; index += 1)
	{
		dealerCards[index] = TURN_CARD_SHOW(dealerCards[index]);
	}

	render_game_board(screen, playerCards, dealerCards, deck, playerStake, *playerMoney);
	SDL_UpdateWindowSurface(screen.window);

	int dealerValue = 0;

	printf("player has enterd cards\n");

	playing_cards_value(&playerValue, playerCards);

	if(playerValue <= 21)
	{
		

		playing_cards_value(&dealerValue, dealerCards);

		bool hasAnAce = rank_within_cards(dealerCards, RANK_ACE);

		while(dealerValue < 21 && (dealerValue < 17 || (dealerValue < playerValue && hasAnAce) ))
		{
			SDL_Delay(1000);

			unsigned int dealerAmount = card_array_amount(dealerCards);

			if(!deal_upside_card(&dealerCards[dealerAmount], deck))
			{
				free(playerCards);
				free(dealerCards);

				return false;
			}

			playing_cards_value(&dealerValue, dealerCards);
			hasAnAce = rank_within_cards(dealerCards, RANK_ACE);

			render_game_board(screen, playerCards, dealerCards, deck, playerStake, *playerMoney);
			SDL_UpdateWindowSurface(screen.window);
		}
	}

	// The one with the best cards wins -> show results and return true

	if(playerValue <= 21 && (playerValue > dealerValue ||  dealerValue > 21))
	{ // WIN
		*playerMoney += playerStake * 2;
	}

	else if(playerValue < dealerValue || playerValue > 21)
	{ // LOSE
		*playerMoney += 0;
	}

	else if(playerValue == dealerValue && !(dealerValue > 21 && playerValue > 21))
	{ // SAME
		*playerMoney += playerStake;
	}

	render_game_board(screen, playerCards, dealerCards, deck, playerStake, *playerMoney);
	render_result_screen(screen, playerValue, dealerValue, playerStake);

	SDL_UpdateWindowSurface(screen.window);


	append_array_cards(deck, playerCards);
	append_array_cards(deck, dealerCards);

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

	int playerMoney = 500;

	while(game_play_handler(screen, deck, &playerMoney))
	{
		
	}

	printf("free deck and cards\n");
	free(deck);

	printf("free_screen_struct\n");
	free_screen_struct(screen);

	return false;
}