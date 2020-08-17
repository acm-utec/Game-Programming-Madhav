#include"game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game():mWindow(nullptr),
    mRenderer(nullptr),
    mTicksCount(0),
    mIsRunning(true), 
    mPaddleDir(0),
    mPaddleDir2(0),
    dif(0),
    flag(false),
    flag2(false)
{
	Ball* ball1 = new Ball();
  Ball* ball2 = new Ball();
  Ball* ball3 = new Ball();
  balls = {ball1, ball2, ball3};
}

bool Game::Initialize(){
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0){
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
    SDL_WINDOW_FULLSCREEN
	);

	if (!mWindow){
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer){
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//
	for(auto &i: balls){
    i->setPos(1024.0f/2.0f, 768.0f/2.0f);
    i->setVel(-200.0f + 2.0, 235.0f + 2.0);    
	}

  paddle1.setPos(10.0f, 768.0f/2.0f);
  paddle2.setPos(1024.0f -(thickness +10), 768.0f/2.0f);

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE]){
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]){
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S]){
		mPaddleDir += 1;
	}

	// Update paddle direction based on I/K keys
  mPaddleDir2 = 0;
  if (state[SDL_SCANCODE_I]){
    mPaddleDir2 -= 1;
  }
  if (state[SDL_SCANCODE_K]){
    mPaddleDir2 += 1;
  }

}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle position based on direction
	paddle1.UpdatePos(mPaddleDir, deltaTime);
  paddle2.UpdatePos(mPaddleDir2, deltaTime);
	
	for(auto& i: balls){
	        i->UpdatePos(deltaTime);

	}
	
	for(auto& i: balls){
	 // Bounce if needed
        // Did we intersect with the paddle?
        float diff3 = paddle1.getPosy() - i->getPosy();
        // Take absolute value of difference
        diff3 = (diff3 > 0.0f) ? diff3 : -diff3;

        // Did we intersect with the paddle?
        float diff4 = paddle2.getPosy() - i->getPosy();
        // Take absolute value of difference
        diff4 = (diff4 > 0.0f) ? diff4 : -diff4;

        if (
                // Our y-difference is small enough
                diff3 <= paddleH / 2.0f &&
                // We are in the correct x-position
                i->getPosx() <= 25.0f && i->getPosx() >= 20.0f &&
                // The ball is moving to the left
                i->getVelx() < 0.0f)
        {
                i->UpdateVelx(-1.0f);
                dif ++;
        }
        else if (
                // Our y-difference is small enough
                diff4 <= paddleH / 2.0f &&
                // We are in the correct x-position
                i->getPosx() >= 1024.0f -(thickness +10) && i->getPosx() <=1024.0f -(thickness+5) &&
                // The ball is moving to the right
                i->getVelx() > 0.0f)
        {
                i->UpdateVelx(-1.0f);
                dif++;
        }

        // Did the ball go off the screen? (if so, end game)
        else if (i->getPosx() <= 0.0f || i->getPosx() >= 1024.0f)
        {
                mIsRunning = false;
        }
        if (i->getPosy() <= thickness && i->getVely() < 0.0f)
        {
                i->UpdateVely(-1);
                
        }
        // Did the ball collide with the bottom wall?
        else if (i->getPosy() >= (768 - thickness) &&
                i->getVely() > 0.0f)
        {
                i->UpdateVely(-1);
                
        }


	}
  
  if(dif == 15 && flag != true){
        balls[1]->UpdateVelx(1.2);
        balls[1]->UpdateVely(1.1);
        flag = true;
  }
  if(dif == 30 && flag2 != true){
        balls[2]->UpdateVelx(1.8);
        balls[2]->UpdateVely(1.5);
        flag2 = true;

  }
        


}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		0,	// B
		255		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw right wall
	/*
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);
	*/
	// Draw paddle
	paddle1.DrawPaddle(mRenderer);
	paddle2.DrawPaddle(mRenderer);	
	// Draw balls
	for(auto &i: balls){
		i->DrawBall(mRenderer);
	
	}
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

