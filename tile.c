#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#define NUM_TILES 26

int main (int argc, char *argv[]) 
{
	int		i = 0;
	int		j = 0;
	int		d_sel = 0;
	SDL_DisplayMode d_mode;
	SDL_Rect	d_bounds;
	SDL_Window	*win = NULL;
	SDL_Renderer	*rend = NULL;
	SDL_Texture	*atlas = NULL;
	SDL_Surface	*sur = NULL;
	SDL_Rect	tile[NUM_TILES];
	SDL_Rect	target;

	// Sprindex is too cool a name not to use for the sprite/tile index enum type.
	enum sprindex {
		dude,
		mdude,
		van,
		panel,
		graves,
		ptank,
		vantank,
		puss,
		beefy,
		erect,
		mtank,
		obs,
		warms,
		dstank,
		airbus,
		choppa,
		jet,
		jumbo,
		bomber,
		missle,
		grabby,
		boat,
		pboat,
		sub,
		bship,
		carrier
	};

	enum sprindex brush = panel;
	
	for(i = 1; i < argc; i++)
	{
		if(strncmp(argv[i], "-d", 3) == 0)
		{
			i++;
			d_sel = atoi(argv[i]);
		}
	}
	printf("Selected Display is #%d\n", d_sel);

	for(i = 0; i < NUM_TILES; i++)
	{
		tile[i].x = i * 16;
		tile[i].y = 0;
		tile[i].h = 16;
		tile[i].w = 16;
	}
	for(i = 0; i < NUM_TILES; i++)
	{
		printf("tile[%d] x:%d y:%d h:%d w:%d\n", i, tile[i].x, tile[i].y, tile[i].h, tile[i].w);
	}

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
	
	win = SDL_CreateWindow
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

	sur = SDL_LoadBMP("tiles.bmp");
	atlas = SDL_CreateTextureFromSurface(rend, sur);
	SDL_FreeSurface(sur);

	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			target.x = j * 64;
			target.y = i * 64;
			target.h = 64;
			target.w = 64;
			SDL_RenderCopy(rend, atlas, &tile[brush], &target);
		}
	}
	SDL_RenderPresent(rend);

	SDL_Delay(5000);

	SDL_DestroyTexture(atlas);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);

	printf("I ran till the end\n");
	SDL_Quit();
	return 0;
}
