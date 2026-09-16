#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
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
void player_draw(int x, int y);
void ene(int x, int y);
//
typedef struct { // forgot how structs work damn.
  float x, y;
  float vx, vy;
} speed;
//
//
void bullet_draw(speed *player, speed *ene, speed *bullet);
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
  speed player;
  speed ene;
  speed bullet;
  //
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Event event;
  SDL_Event movement;
  SDL_Window *map = SDL_CreateWindow("Game", LE, HE, 0);
  SDL_Window *popup = NULL;

  SDL_Renderer *rend = SDL_CreateRenderer(map, NULL);

  SDL_Texture *texture = SDL_CreateTexture(
      rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 250,
      250); // i can use different texture access and different pixelformat but
            // idk this is fine?\
            //
  //
  // Make every pixel box draw 4 times larger

  // like do i need it ?
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  //
  //
  //

  player.x = 250 / 2.0;
  player.y = 250 / 2.0;
  // its for testing -- remove to a better place
  bullet.y = player.y;
  bullet.x = player.x;
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
    // this event is for running main window
    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_EVENT_QUIT) {
        // stop this shit;
        value = 0;
      }
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
      // i am going to use this event for movement as well -- lets see what
      // happens;
    }

    const bool *ihatemylife = SDL_GetKeyboardState(NULL);
    //
    //
    //
    //
    if (ihatemylife[SDL_SCANCODE_A]) {
      if (player.x > 0) {
        player.x -= 0.2f;
      }
    }
    if (ihatemylife[SDL_SCANCODE_D]) {
      if (player.x < HE - 1) {
        player.x += 0.2f;
      }
    }
    // this following this is simply fun and nothing else;
    if (ihatemylife[SDL_SCANCODE_W]) {
      if (player.y > 0) {
        player.y -= 0.2f;
      }
    }
    if (ihatemylife[SDL_SCANCODE_S]) {
      if (player.y < HE - 1) {
        player.y += 0.2f;
      }
    }
    bool bulletIn = ihatemylife[SDL_SCANCODE_SPACE];

    if (bulletIn) {
      if (bullet.y > 0) {
        bullet.y -= 0.6f;
        bulletIn = 1;
      } else {
        bulletIn = 0;
      }
    } else {
      bullet.x = player.x;
      bullet.y = player.y;
    }

    //
    // my mind is fucked
    clear(0x2A2A2A);
    // so would this be my canvas i guess?
    //
    player_draw(player.x, player.y);
    if (bullet.y != 0) {
      draw(bullet.x, bullet.y, 0xFFFFFFFF);
    }
    //
    //
    //
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
  draw(x - 1, y + 1, 0xFFFFFFFF);
  draw(x - 1, y, 0xFFFFFFFF);
  draw(x + 1, y, 0xFFFFFFFF);
  draw(x + 1, y - 1, 0xFFFFFFFF);
  draw(x + 1, y + 1, 0xFFFFFFFF);
  draw(x, y + 1, 0xFFFFFFFF);
  draw(x, y - 1, 0xFFFFFFFF);
  draw(x, y, 0xFFFFFFFF);
}

void player_draw(int x, int y) { shape(x, y); }
//
//
void ene(int x, int y) { shape(x, y); }

// is there no other method that importing the dammend texture and rend
// togethter? wtf?
//  i will pass the pointer to the struct having these wthings now.
