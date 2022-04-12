
#ifndef SCREEN_STRUCTS_H
#define SCREEN_STRUCTS_H

typedef SDL_Window    Window;
typedef SDL_Renderer  Renderer;
typedef SDL_Surface	  Surface;
typedef SDL_Texture   Texture;
typedef SDL_Rect      Rect;
typedef SDL_Color     Color;
typedef SDL_Event     Event;

typedef struct Screen
{
  Window* window;
  Surface* surface;
  Renderer* renderer;
  unsigned int width;
  unsigned int height;
} Screen;

#endif