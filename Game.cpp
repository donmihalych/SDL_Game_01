#include "Game.h"
#include <iostream>

using namespace std;

// на всякий случай инициализируем нулем все приватные члены класса
Game::Game()
{
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
	m_pTexture = nullptr;
	m_sourceRectangle = {};
	m_destinationRectangle = {};
}

Game::~Game()
{
	cout << "cleaning game" << endl;
	SDL_DestroyWindow(m_pWindow); 
	SDL_DestroyRenderer(m_pRenderer); 
	SDL_Quit();
}


bool Game::init(const char* title, int xpos, int ypos, int with, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL init success" << endl;
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, with, height, flags);
		
		if (m_pWindow != 0) // если удачная инициализация
		{
			cout << "window creation success" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				cout << "renderer creation success" << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				cout << "renderer init fail" << endl;
				return false;
			}
		}
		else
		{
			cout << "window init fail" << endl;
			return false;
		}
	}
	else
	{
		cout << "SDL init fail" << endl;
		return false;
	}

	cout << "init success" << endl;



 	SDL_Surface* pTempSurface = SDL_LoadBMP("assets/image1.bmp");
	if (!pTempSurface) 
		cout << "** image load error **" << endl;
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
 	SDL_FreeSurface(pTempSurface); // не забудем подчистить то что больше не нужно

	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	SDL_Event event = {};
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // нажали на крестик, закрыли окно
			m_bRunning = false;
		break;

		default:
		break;
		}
	}
}

bool Game::running()
{
//  ..................
	return m_bRunning;
}

