#define _CRT_SECURE_NO_WARNINGS // дл€ freopen

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include "Game.h"

using namespace std;

Game* g_game = nullptr;

int main(int argc, char* argv[])
{
	//	возможность вывода в параллельное окно консоли служебных сообщений
	AllocConsole();
	freopen("CON", "w", stdout);

	g_game = new Game();
	g_game->init("Chapter 1", 700, 250, 640, 480, 0);
	g_game->hardcodeLoadTexture();

	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	delete g_game;

	system("pause");
	return 0;
}








/***************** –≈јЋ»«ј÷»я ‘”Ќ ÷»… ******************/
/*******************************************************/


// bool init(const char* title, int xpos, int ypos, int height, int with, int flags)
// {
// 	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
// 	{
// 		g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, with, flags);
// 		if (g_pWindow != 0)
// 		{
// 			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
// 		}
// 	}
// 	else
// 	{
// 		return false; // не смогли инициализировать SDL
// 	}
// 	
// 	return true;
// }
// 
// void render()
// {
// 	// установить в черный
// 	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
// 	SDL_RenderClear(g_pRenderer);
// 	SDL_RenderPresent(g_pRenderer);
// }