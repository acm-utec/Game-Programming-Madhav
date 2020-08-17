#include"ball.h"

Ball::Ball(){}
void Ball::setPos(float posx, float posy){
  posicion.x = posx;
  posicion.y = posy;

}
float Ball::getPosy(){
  return posicion.y;
}
float Ball::getPosx(){
  return posicion.x;
}
float Ball::getVelx(){
  return velocidad.x;
}
float Ball::getVely(){
  return velocidad.y;
}
void Ball::UpdateVelx(float n){
  velocidad.x *= n;
}
void Ball::UpdateVely(float n){
  velocidad.y *= n;
}
void Ball::setVel(float velx, float vely){
  velocidad.x = velx;
  velocidad.y = vely;
}
void Ball::UpdatePos(float deltatime){
  posicion.x += velocidad.x*deltatime;
  posicion.y += velocidad.y*deltatime;
}
void Ball::DrawBall(SDL_Renderer *mRenderer){
  SDL_Rect ball{
    static_cast<int>(posicion.x - 15/2),
    static_cast<int>(posicion.y -15/2),
    15,
    15
  };
  SDL_RenderFillRect(mRenderer, &ball);
}

