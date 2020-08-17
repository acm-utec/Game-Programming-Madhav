#ifndef GAME_H
#define GAME_H

#include"SDL2/SDL.h"
#include<vector>
#include"ball.h"
#include"paddle.h"
#include<iostream>

class Game{

  private:
      void ProcessInput();
      void UpdateGame();
      void GenerateOutput();

      SDL_Window* mWindow;
      SDL_Renderer* mRenderer;
      Uint32 mTicksCount;
      bool mIsRunning;

      int mPaddleDir, mPaddleDir2;
      Paddle paddle1;
      Paddle paddle2;
      std::vector<Ball*> balls;

      int dif;
      bool flag, flag2;

   public:
      Game();
      bool Initialize();
      void RunLoop();
      void Shutdown();

};

#endif
