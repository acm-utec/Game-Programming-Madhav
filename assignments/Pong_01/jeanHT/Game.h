// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include<SDL2/SDL.h>
#include <vector>
#include <iostream>

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

struct ball
{
	Vector2 pos;
	Vector2 vel;

	ball(float x,float y,float vel_x,float vel_y){
		pos.x = x;
		pos.y = y;
		vel.x = vel_x;
		vel.y = vel_y;
	}
};


// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	
	// Pong specific
	// Direction of paddle
	int mPaddleDir;
	// Direction of second paddle
	int mPaddleDir_1;
	// Position of paddle
	Vector2 mPaddlePos;
	// Direction of second paddle
	Vector2 mPaddlePos_1;
	//vector of balls
	std::vector<ball> balls;

			// Position of ball
			Vector2 mBallPos;
			// Velocity of ball
			Vector2 mBallVel;
};
