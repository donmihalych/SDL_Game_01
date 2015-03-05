#if !defined __Game__
#define __Game__

#include <SDL.h>

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int with, int height, int flags);
	
	void hardcodeLoadTexture();

	void render();
	void update();
	void handleEvents();
	bool running();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	bool m_bRunning;
};

#endif