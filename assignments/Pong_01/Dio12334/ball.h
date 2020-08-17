#ifndef BALL_H
#define BALL_H

#include"SDL2/SDL.h"
#include"vector.h"

class Ball{
    private:
        Vector posicion;
        Vector velocidad;

    public:
        Ball();
        float getPosy();
        float getPosx();
        float getVelx();
        float getVely();
        void UpdateVelx(float n);
        void UpdateVely(float n);
        void setPos(float posx, float posy);
        void setVel(float velx, float vely);
        void UpdatePos(float deltatime);
        void DrawBall(SDL_Renderer *mRenderer);

};

#endif
