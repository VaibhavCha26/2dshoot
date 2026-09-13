#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#define LE 1000
#define HE 1000

int frame[LE * HE];
void clear(int color);
void draw(int x, int y, int color);
//
void player(int x, int y);
void ene(int x, int y);
void bullet(int x, int y);
//
struct speed {
  float x, y;
  float vx, vy;
};

/*
 *
 */
/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Event event;

  SDL_Window *map = SDL_CreateWindow("Game", LE, HE, 0);

  SDL_Renderer *rend = SDL_CreateRenderer(map, NULL);

  SDL_Texture *texture = SDL_CreateTexture(
      rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, LE,
      HE); // i can use different texture access and different pixelformat but
           // idk this is fine?
  // like do i need it ?
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  //
  //
  //
  // here the manipulation of pixel will be done -- i can't increase the size
  // wtf?
  SDL_SetRenderLogicalPresentation(rend, 250, 250,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  int value = 1;
  //
  //
  //
  // SDL_SetRenderLogicalPresentation(rend, 320, 180,
  //                              SDL_LOGICAL_PRESENTATION_LETTERBOX);
  const bool *keys =
      SDL_GetKeyboardState(NULL); // why int* numkeys and not nullptr
  while (value) {
    //
    //
    SDL_Event pop_event;
    // this event is for running main window
    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_EVENT_QUIT) {
        // stop this shit;
        value = 0;
      }

      if (keys[SDL_SCANCODE_ESCAPE] == true) {
        int popframebuffer[500 * 500];
        SDL_Window *popup =
            SDL_CreatePopupWindow(map, 500, 500, LE / 2, HE / 2, 0);
        SDL_Renderer *poprend = SDL_CreateRenderer(popup, NULL);
        SDL_Texture *poptexture =
            SDL_CreateTexture(poprend, SDL_PIXELFORMAT_ABGR8888,
                              SDL_TEXTUREACCESS_STREAMING, HE / 2, LE / 2);
        int value2;
        // after this the window is running or not command comes for  the popup
        // one
        while (value2) {
          //
          if (event.type == SDL_EVENT_QUIT) {
            value2 = 0;
          }

          clear(0x2A2A2A);
          // here i am confused as fuck -- can i use that rectanble thing i
          // learned or no?
          SDL_UpdateTexture(poptexture, NULL, popframebuffer,
                            500 * sizeof(int));
          SDL_UpdateTexture(texture, NULL, frame, LE * sizeof(int));
          // here we will display things ig?
          SDL_RenderClear(poprend);
          // doubt here on render texture parameters
          SDL_RenderTexture(poprend, poptexture, NULL, NULL);
          // wtf does render present do?-
          SDL_RenderPresent(poprend); //--> so basically it updates my windows
                                      //display screen with any drawing
                                      // operations perforemed since last frame.
        }
        SDL_DestroyTexture(poptexture);
        SDL_DestroyRenderer(poprend);
        SDL_DestroyWindow(popup);
        SDL_Quit();
      }
      clear(0x2A2A2A);
      // so would this be my canvas i guess?
      //
      //
      //
      // player(HE / 2, LE / 2);
      draw(LE / 2, HE / 2, 0xFFFFFFF);

      SDL_UpdateTexture(texture, NULL, frame, LE * sizeof(int));
      // here we will display things ig?
      SDL_RenderClear(rend);
      // doubt here on render texture parameters
      SDL_RenderTexture(rend, texture, NULL, NULL);
      SDL_RenderPresent(rend);
    }

    // here we nuke the things and stuff me made why? idk?
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(map);

    SDL_Quit();
    return 0;
  }
}

void clear(int color) {
  for (int i = 0; i < HE * LE; i++) {
    frame[i] = color;
  }
}

void draw(int x, int y, int color) { frame[LE * y + x] = color; }

/*void player(int x, int y) { draw(x, y, 0xFFFFFFFF); }
void ene(int x, int y) {}
void bullet(int x, int y) {}*/
