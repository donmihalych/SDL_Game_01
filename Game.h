#if !defined __Game__
#define __Game__

#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int with, int height, int flags);
	
	bool hardcodeLoadTexture();

	void render();
	void update();
	void handleEvents();
	bool running();

//	const int max_FPS_in_ms = 125; // При Х..8 кадрах в секунду, задержка между кадрами в МС = 1/8 *1000 
	const int max_FPS_in_ms = 67; // При Х..15 кадрах в секунду, задержка между кадрами в МС = 1/15 *1000 
//const int max_FPS_in_ms = 40; // При Х..25 кадрах в секунду, задержка между кадрами в МС = 1/25 *1000 

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int n_frame;

	bool m_bRunning;
};

#endif