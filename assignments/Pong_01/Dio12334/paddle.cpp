#include"paddle.h"
        
Paddle::Paddle(){

}
float Paddle::getPosy(){
  return posicion.y;
}
float Paddle::getPosx(){
  return posicion.x;
}

void Paddle::setPos(float posx, float posy){
  posicion.x = posx;
  posicion.y = posy;
}

void Paddle::UpdatePos(int dir, float deltatime){
   if (dir != 0){
     posicion.y += dir * 300.0f * deltatime;
     if (posicion.y < (100.0f/2.0f + 15)){
       posicion.y = 100.0f/2.0f + 15;
     }
     else if (posicion.y > (768.0f - 100.0f/2.0f - 15)){
       posicion.y = 768.0f - 100.0f/2.0f - 15;
     }
  }

}
void Paddle::DrawPaddle(SDL_Renderer *mRenderer){
  SDL_Rect paddle{
    static_cast<int>(posicion.x),
    static_cast<int>(posicion.y - 100.0f/2),
    15,
    static_cast<int>(100.0f)
  };
  SDL_RenderFillRect(mRenderer, &paddle);
}

