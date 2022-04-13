
#include "../Header-Files-Folder/master-include-file.h"

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

	Card* playerCards = create_empty_deck(52);
	Card* dealerCards = create_empty_deck(52);


	deal_playing_cards(dealerCards, deck, 2);

	deal_playing_cards(playerCards, deck, 2);


	Event event;

	while(event.type != SDL_QUIT && !(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
	{
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			unsigned int playerAmount = card_array_amount(playerCards);
			deal_playing_card(&playerCards[playerAmount], deck);
		}

		render_game_board(screen, playerCards, dealerCards);
		SDL_UpdateWindowSurface(screen.window);

		SDL_WaitEvent(&event);
	}


	printf("free deck and cards\n");
	free(deck);
	free(playerCards);
	free(dealerCards);

	printf("free_screen_struct\n");
	free_screen_struct(screen);

	return false;
}