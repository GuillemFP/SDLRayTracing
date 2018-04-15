#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "SDL/include/SDL.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

int main(int argc, char ** argv)
{
	int nx = 800;
	int ny = 600;

	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int i;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(nx, ny, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	std::ofstream myFile;
	myFile.open("image.ppm");

	myFile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			myFile << ir << " " << ig << " " << ib << "\n";
			SDL_SetRenderDrawColor(renderer, ir, ig, ib, 255);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}

	SDL_RenderPresent(renderer);
	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	myFile.close();

	return EXIT_SUCCESS;
}
