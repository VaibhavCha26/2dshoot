#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LE 1000
#define HE 1000

int frame[LE * HE];
void clear(int color);
void draw(int x, int y, int color);
void shape(int x, int y);

//
void player(int x, int y);
void ene(int x, int y);
void bullet(int player_x, int ene_x, int ene_down_y_position,
            int player_top_y_position);
//
typedef struct { // forgot how structs work damn.
  float x, y;
  float vx, vy;

} speed;

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
  SDL_Window *popup = NULL;

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
  //
  //
  //
  //
  //
  //
  //
  int value = 1;
  //
  //
  //
  // SDL_SetRenderLogicalPresentation(rend, 320, 180,
  //                              SDL_LOGICAL_PRESENTATION_LETTERBOX);
  while (value) {
    //
    //
    // this event is for running main window
    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_EVENT_QUIT) {
        // stop this shit;
        value = 0;
      }
      //
      //
      //
      //
      //
      //
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          // check if there is a popup or not
          if (!popup) {
            popup = SDL_CreatePopupWindow(
                map, 500, 500, 200, 200,
                // the flag tells the os to treat this window as context menu -
                // alowing it to sit nearly top of the parent window
                SDL_WINDOW_POPUP_MENU);
            SDL_ShowWindow(popup); // first time :? why do i need this?
          }
        }
      }
    }
    SDL_Delay(10);
    //
    //
    //
    //
    clear(0x2A2A2A);
    // so would this be my canvas i guess?
    //

    //
    //
    //
    // player(HE / 2, LE / 2);
    draw(LE / 2, HE / 2, 0xFFFFFFF);
    bullet(HE / 2, LE / 2, 0, HE / 2);

    SDL_UpdateTexture(texture, NULL, frame, LE * sizeof(int));
    // here we will display things ig?
    SDL_RenderClear(rend);
    // doubt here on render texture parameters
    SDL_RenderTexture(rend, texture, NULL, NULL);
    SDL_RenderPresent(rend);
  }
  // first nuke the child window
  if (popup) {
    SDL_DestroyWindow(popup);
  }

  // here we nuke the things and stuff me made why? idk?
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(map);

  SDL_Quit();
  return 0;
}

void clear(int color) {
  for (int i = 0; i < HE * LE; i++) {
    frame[i] = color;
  }
}

void draw(int x, int y, int color) { frame[LE * y + x] = color; }

void shape(int x, int y) {
  draw(x - 1, y - 1, 0xFFFFFFFF);
  draw(x + 1, y + 1, 0xFFFFFFFF);
  draw(x, y - 1, 0xFFFFFFFF);
  draw(x, y + 1, 0xFFFFFFFF);
  draw(x - 1, y - 1, 0xFFFFFFFF);
  draw(x + 1, y + 1, 0xFFFFFFFF);
  draw(x, y, 0xFFFFFFFF);
}

void player(int x, int y) { shape(x, y); }
//
//
void ene(int x, int y) { shape(x, y); }

void bullet(int player_x, int ene_x, int ene_down_y_position,
            int player_top_y_position) {

  speed bullet;
  bullet.vx = 12;
  bullet.x = player_x;
  bullet.y = player_top_y_position;

  while (true) {
    bullet.y -= 1;
    draw(bullet.x, bullet.y, 0xFFFFFFFF);
  }
}
