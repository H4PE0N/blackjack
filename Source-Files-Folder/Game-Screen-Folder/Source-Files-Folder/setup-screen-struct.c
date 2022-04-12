
#include "../Header-Files-Folder/screen-include-file.h"

bool setup_screen_struct(Screen* screen, unsigned int width, unsigned int height, char title[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Quit();

		return false;
	}

	if(TTF_Init() == -1)
	{
		SDL_Quit();

		return false;
	}

	screen->width = width;
	screen->height = height;

	if(!make_screen_window(&screen->window, screen->width, screen->height, title))
	{
		SDL_Quit();

		return false;
	}

	if(!make_window_surface(&screen->surface, screen->window))
	{
		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	if(!make_surface_renderer(&screen->renderer, screen->surface))
	{
		SDL_FreeSurface(screen->surface);

		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	return true;
}

bool make_surface_texture(Texture** texture, Renderer* renderer, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(renderer, surface);

	return (texture != NULL);
}

bool make_surface_renderer(Renderer** renderer, Surface* surface)
{
  *renderer = SDL_CreateSoftwareRenderer(surface);

	return (*renderer != NULL);
}

bool make_window_surface(Surface** surface, Window* window)
{
  *surface = SDL_GetWindowSurface(window);

	return (*surface != NULL);
}

bool make_screen_window(Window** window, unsigned int width, unsigned int height, char title[])
{
  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

	return (*window != NULL);
}

void free_screen_struct(Screen screen)
{
	SDL_DestroyRenderer(screen.renderer);

	SDL_FreeSurface(screen.surface);

	SDL_DestroyWindow(screen.window);

	SDL_Quit();
}