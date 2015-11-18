#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main (int argc, char *argv[]) 
{
	int		i = 0;
	int		d_sel = 0;
	SDL_DisplayMode d_mode;
	SDL_Rect	d_bounds;
	SDL_Window	*win = NULL;
	SDL_Renderer	*rend = NULL;
	SDL_Texture	*tex = NULL;
	SDL_Surface	*sur = NULL;
	
	for(i = 1; i < argc; i++)
	{
		if(strncmp(argv[i], "-d", 3) == 0)
		{
			i++;
			d_sel = atoi(argv[i]);
		}
	}
	printf("Selected Display is #%d\n", d_sel);


	if(SDL_Init(SDL_INIT_VIDEO) != 0)  // SDL_INIT_AUDIO if needed
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	int should_be_zero = SDL_GetCurrentDisplayMode(d_sel, &d_mode);

	if(should_be_zero != 0)
		SDL_Log("Could not get display mode for video display #%d: %s", d_sel, SDL_GetError());
	else
	{
		SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", d_sel, d_mode.w, d_mode.h, d_mode.refresh_rate);
		if(SDL_GetDisplayBounds(d_sel, &d_bounds) != 0)
		{
			SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
			return 1;
		}
		SDL_Log("Display #%d bounds: x %d-%d , y %d-%d", d_sel, d_bounds.x, d_bounds.x + d_bounds.w, d_bounds.y, d_bounds.y + d_bounds.h);
	}
	
	win= SDL_CreateWindow
	(
		"An SDL2 win",
		d_bounds.x,
		d_bounds.y,
		d_bounds.w,
		d_bounds.h,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
	);

	if(win == NULL)
	{
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if(rend == NULL)
	{
		SDL_Log("Could not create renerer: %s\n", SDL_GetError());
		return 1;
	}

	sur = SDL_LoadBMP("izanami.bmp");
	tex = SDL_CreateTextureFromSurface(rend, sur);
	SDL_FreeSurface(sur);

	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, tex, NULL, NULL);
	SDL_RenderPresent(rend);

	SDL_Delay(5000);

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);

	printf("I ran till the end\n");
	SDL_Quit();
	return 0;
}
