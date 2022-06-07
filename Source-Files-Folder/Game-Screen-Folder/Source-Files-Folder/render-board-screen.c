
#include "../Header-Files-Folder/screen-include-file.h"

bool create_card_filename(char* filename, Card card)
{
	unsigned int suit = CARD_SUIT_MACRO(card);
	unsigned int rank = CARD_RANK_MACRO(card);

	if(!NUMBER_IN_BOUNDS(suit, 1, DECK_SUITS) || !NUMBER_IN_BOUNDS(rank, 1, DECK_RANKS)) return false;

	sprintf(filename, CARD_FILE_MALL, SUIT_STRINGS[suit], RANK_STRINGS[rank]);

	return true;
}

bool extract_card_image(Surface** image, Card card)
{
	char filename[256];

	if(!create_card_filename(filename, card)) return false;

	return default_folder_image(image, filename);
}

bool default_folder_image(Surface** image, char filename[])
{
	char filePath[256];

	sprintf(filePath, "%s/%s", IMAGE_FOLDER, filename);

	return extract_file_image(image, filePath);
}

bool default_folder_font(Font** font, char filename[], int size)
{
	char filePath[256];

	sprintf(filePath, "%s/%s", FONT_FOLDER, filename);

	return extract_file_font(font, filePath, size);
}

bool render_screen_deck(Screen screen, Card deck[], int width, int height)
{
	unsigned int amount = card_array_amount(deck);

	unsigned int displayAmount = (amount > DECK_DISPLAY_AMOUNT) ? DECK_DISPLAY_AMOUNT : amount;

	int renderHeight = height - (CARD_HEIGHT / 2);
	int startWidth = width - ((DECK_MARGIN * (displayAmount - 1) + CARD_WIDTH) / 2);

	for(int index = 0; index < displayAmount; index += 1)
	{
		int renderWidth = startWidth + (DECK_MARGIN * index);

		if(!render_screen_card(screen, deck[index], renderWidth, renderHeight)) return false;
	}

	return true;
}

bool render_game_board(Screen screen, Card playerCards[], Card dealerCards[], Card deck[], int playerStake, int playerMoney)
{
	Surface* tableImage = NULL;
	if(!default_folder_image(&tableImage, (char*) TABLE_IMAGE)) return false;
	
	Rect tablePosition = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	
	if(!render_screen_image(screen, tableImage, tablePosition)) return false;


	if(!render_screen_cards(screen, dealerCards, WINDOW_WIDTH / 6 * 3, WINDOW_HEIGHT / 4 * 1)) return false;
	if(!render_screen_cards(screen, playerCards, WINDOW_WIDTH / 6 * 3, WINDOW_HEIGHT / 4 * 3)) return false;


	render_game_options(screen);
	render_stake_options(screen);

	render_player_values(screen, playerMoney);
	render_play_values(screen, playerCards, dealerCards, playerStake);

	return true;
}

bool render_stake_options(Screen screen)
{
	Color color = {255, 255, 255};

	char* textBlock[] = {"1 : 25", "2 : 50", "3 : 75"};

	render_text_block(screen, textBlock, 3, color, WINDOW_WIDTH / 6 * 5, WINDOW_HEIGHT / 4 * 1, 2);

	return true;
}

bool render_result_screen(Screen screen, int playerValue, int dealerValue, int playerStake)
{
	char resultText[200];

	Color color = {255, 255, 255};

	if(playerValue <= 21 && (playerValue > dealerValue ||  dealerValue > 21))
	{ // WIN
		sprintf(resultText, "YOU WON : $%d", playerStake);
		color = (Color) {0, 0, 255};
	}

	else if(playerValue < dealerValue || playerValue > 21)
	{ // LOSE
		sprintf(resultText, "YOU LOST : $%d", playerStake);
		color = (Color) {255, 0, 0};
	}

	else if(playerValue == dealerValue && !(dealerValue > 21 && playerValue > 21))
	{ // SAME
		sprintf(resultText, "EQUAL");
	}

	render_screen_text(screen, resultText, color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 4);
	

	return true;
}

bool render_text_block(Screen screen, char* textArray[], int amount, Color color, int width, int height, float size)
{
	Font* textFont = NULL;

	if(!default_folder_font(&textFont, (char*) FONT_FILE, FONT_SIZE)) return false;

	Surface* textSurfaceArray[amount];

	int textHeight = 0;
	int textWidth = 0;

	for(int index = 0; index < amount; index += 1)
	{
		textSurfaceArray[index] = TTF_RenderText_Solid(textFont, textArray[index], color); 

		if(textSurfaceArray[index]->w * size > textWidth) textWidth = textSurfaceArray[index]->w * size;

		if(textSurfaceArray[index]->h * size > textHeight) textHeight = textSurfaceArray[index]->h * size;
	}

	int renderWidth = (width - textWidth / 2);
	int totalHeight = ((1.25 * textHeight) * amount) / 2;

	for(int index = 0; index < amount; index += 1)
	{
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen.renderer, textSurfaceArray[index]);

		int renderHeight = (height - totalHeight + ((1.2 * textHeight) * index));

		//int currentWidth = textSurfaceArray[index]->w * size;

		Rect position = {renderWidth, renderHeight, textWidth, textHeight};

		SDL_RenderCopy(screen.renderer, textTexture, NULL, &position);

		SDL_FreeSurface(textSurfaceArray[index]);
		SDL_DestroyTexture(textTexture);
	}

	TTF_CloseFont(textFont);

	return true;
}

bool render_play_values(Screen screen, Card playerCards[], Card dealerCards[], int playerStake)
{
	Color color = {255, 255, 255};

	char stakeText[200];

	sprintf(stakeText, "STAKE : $%d", playerStake);

	int playerValue = 0;
	int dealerValue = 0;

	playing_cards_value(&playerValue, playerCards);
	upside_cards_value(&dealerValue, dealerCards);

	char playerText[200];
	char dealerText[200];

	sprintf(playerText, "Player: %d", playerValue);
	sprintf(dealerText, "Dealer: %d", dealerValue);

	char* textBlock[] = {stakeText, playerText, dealerText};

	render_text_block(screen, textBlock, 3, color, WINDOW_WIDTH / 6 * 1, WINDOW_HEIGHT / 4 * 3, 2);

	return true;
}

bool render_player_values(Screen screen, int playerMoney)
{
	Color color = {255, 255, 255};

	char moneyText[200];

	sprintf(moneyText, "MONEY : $%d", playerMoney);

	char nameText[200];

	sprintf(nameText, "NAME : HAMPUS");

	char* textBlock[] = {nameText, moneyText};

	render_text_block(screen, textBlock, 2, color, WINDOW_WIDTH / 6 * 1, WINDOW_HEIGHT / 4 * 1, 1.5);

	return true;
}

bool render_game_options(Screen screen)
{
	Color color = {255, 255, 255};

	char* textBlock[] = {"DEAL : J", "STAND : K", "SPLIT : L", "DOUBL : O"};

	render_text_block(screen, textBlock, 4, color, WINDOW_WIDTH / 6 * 5, WINDOW_HEIGHT / 4 * 3, 2);

	return true;
}

bool render_screen_card(Screen screen, Card card, int width, int height)
{
	Surface* cardImage = NULL;

	if(CARD_SIDE_SHOW(card))
	{
		if(!extract_card_image(&cardImage, card)) return false;
	}
	else
	{
		if(!default_folder_image(&cardImage, (char*) CARD_BACK_IMAGE)) return false;
	}

	Rect position = {width, height, CARD_WIDTH, CARD_HEIGHT};

	return render_screen_image(screen, cardImage, position);
}

bool render_screen_cards(Screen screen, Card cards[], int width, int height)
{
	unsigned int amount = card_array_amount(cards);

	int renderHeight = height - (CARD_HEIGHT / 2);
	int startWidth = width - ((CARD_MARGIN * (amount - 1) + CARD_WIDTH) / 2);

	for(int index = 0; index < amount; index += 1)
	{
		int renderWidth = startWidth + (CARD_MARGIN * index);

		if(!render_screen_card(screen, cards[index], renderWidth, renderHeight)) return false;
	}

	return true;
}

bool extract_file_image(Surface** image, char filePath[])
{
	return ( (*image = IMG_Load(filePath)) != NULL);
}

bool extract_file_font(Font** font, char filePath[], int size)
{
	return ( (*font = TTF_OpenFont(filePath, size)) != NULL);
}

bool render_screen_image(Screen screen, Surface* image, Rect position)
{
	Texture* texture = NULL;

	if(!make_surface_texture(&texture, screen.renderer, image)) return false;
	
	SDL_RenderCopy(screen.renderer, texture, NULL, &position);

	SDL_DestroyTexture(texture);

	return true;
}

bool render_screen_text(Screen screen, char text[], Color color, int width, int height, float size)
{
	Font* textFont = NULL;

	if(!default_folder_font(&textFont, (char*) FONT_FILE, FONT_SIZE)) return false;	

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(textFont, text, color); 

	SDL_Texture* message = SDL_CreateTextureFromSurface(screen.renderer, surfaceMessage);

	int textHeight = surfaceMessage->h * size;
	int textWidth = surfaceMessage->w * size;

	Rect position = {width - textWidth / 2, height - textHeight / 2, textWidth, textHeight};

	SDL_RenderCopy(screen.renderer, message, NULL, &position);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);

	TTF_CloseFont(textFont);

	return true;
}