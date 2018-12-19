#include <iostream>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"

int main()
{
        /*
        SDL_Window *window;

        SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

        // Create an application window with the following settings:
        window = SDL_CreateWindow(
                                  "An SDL2 window",                  // window title
                                  SDL_WINDOWPOS_UNDEFINED,           // initial x position
                                  SDL_WINDOWPOS_UNDEFINED,           // initial y position
                                  640,                               // width, in pixels
                                  480,                               // height, in pixels
                                  SDL_WINDOW_OPENGL                  // flags - see below
                                  );

        // Check that the window was successfully created
        if (window == nullptr)
        {
                std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
                exit(EXIT_FAILURE);
        }
        // The window is open: could enter program loop here (see SDL_PollEvent())

        SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

        // Close and destroy the window
        SDL_DestroyWindow(window);

        // Clean up
        SDL_Quit();
        */
        SDL_Window *win = NULL;
        SDL_Renderer *renderer = NULL;
        SDL_Texture *bitmapTex = NULL;
        SDL_Surface *bitmapSurface = NULL;
        int posX = 100, posY = 100, width = 320, height = 240;

        SDL_Init(SDL_INIT_VIDEO);

        win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

        bitmapSurface = SDL_LoadBMP("img/hello.bmp");
        bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
        SDL_FreeSurface(bitmapSurface);

        while (1) {
                SDL_Event e;
                if (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                                break;
                        }
                }

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
                SDL_RenderPresent(renderer);
        }

        SDL_DestroyTexture(bitmapTex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);

        SDL_Quit();
}
