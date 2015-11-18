#include <stdio.h>
#include <SDL2/SDL.h>

int main (int argc, char **argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	printf("SDL_Init Error: %s\n", SDL_GetError());
	return 1;
	}
	printf("I RAN\n");
	SDL_Quit();
}
