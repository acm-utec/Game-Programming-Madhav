#ifndef PADDLE_H 
#define PADDLE_H

#include"vector.h"
#include"SDL2/SDL.h"

class Paddle{
  private:
      Vector posicion;
  public:
        Paddle();
        float getPosy();
        float getPosx();
        void setPos(float posx, float posy);
        void UpdatePos(int dir, float deltatime);
        void DrawPaddle(SDL_Renderer *mRenderer);

};

#endif
