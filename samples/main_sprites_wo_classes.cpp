/*
SDL_Surface is used in software rendering. With software rendering, as saloomi2012 correctly noticed, you are using regular RAM to store image data. Thus, in most cases you can access data buffer associated with surface directly, modifying its content, i.e. it is using CPU, hence the software name.
SDL_Texture on the other hand, is used in a hardware rendering, textures are stored in VRAM and you don't have access to it directly as with SDL_Surface. The rendering operations are accelerated by GPU, using, internally, either OpenGL or DirectX (available only on Windows) API, which in turn are using your video hardware, hence hardware rendering name.
	Needless to say that hardware rendering is by orders of magnitude faster than software rendering and should be always be considered as primary option.

SDL_RenderClear(ren); //Очистка рендера // Use this function to clear the current rendering target with the drawing color
SDL_RenderCopy(ren,background,NULL,&background_RECT); // Use this function to copy a portion of the texture to the current rendering target.
SDL_RenderPresent(ren); // Вывести все в рендер // Use this function to update the screen with any rendering performed since the previous call

while (SDL_PollEvent(&event)) // опрос // Use this function to poll for currently pending events
	SDL_PumpEvents(); // обработчик событий. // gathering events from the input devices

SDL_CreateTextureFromSurface // Use this function to create a texture from an existing surface
	http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php




*/

#define _CRT_SECURE_NO_WARNINGS // для freopen

#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


void move_UP(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.y -= offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}
void move_DOWN(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.y += offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}
void move_LEFT(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.x -= offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}
void move_RIGHT(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.x += offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}

void render_UPDATE(SDL_Renderer* render, SDL_Texture* texture[], SDL_Rect* destrect[], int states[])
{
	SDL_RenderClear(render);
	if (states[0]) SDL_RenderCopy(render, texture[0], NULL, destrect[0]);
	if (states[1]) SDL_RenderCopy(render, texture[1], NULL, destrect[1]);
}




int main(int argc, char* argv[])
{
	//	возможность вывода в параллельное окно консоли служебных сообщений
 	AllocConsole();
 	freopen("CON", "w", stdout);

	SDL_DisplayMode displayMode = {};

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 500, 500, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Rect player_RECT;
	player_RECT.x = 0;   //Смещение полотна по Х
	player_RECT.y = 0;   //Смещение полотна по Y
	player_RECT.w = 333; //Ширина полотна
	player_RECT.h = 227; //Высота полотна

	SDL_Rect background_RECT;
	background_RECT.x = 0;
	background_RECT.y = 0;
	background_RECT.w = displayMode.w;
	background_RECT.h = displayMode.h;

	const int player_WIGHT = 333;   //Ширина исходнго изображения
	const int player_HEIGH = 227;   //Высота исходного изображения
	double TESTtexture_SCALE = 1.0; //Множетель для зумирования

	SDL_Texture *background = IMG_LoadTexture(ren, "assets\\1945.png");
	SDL_Texture *player = IMG_LoadTexture(ren, "assets\\image1.bmp");

	SDL_RenderClear(ren); //Очистка рендера
	SDL_RenderCopy(ren, background, NULL, &background_RECT); //Копируем в рендер фон
	SDL_RenderCopy(ren, player, NULL, &player_RECT); //Копируем в рендер персонажа
	SDL_RenderPresent(ren); //Погнали!!

	SDL_Texture* ARRAY_textures[2] = { background, player };
	SDL_Rect* ARRAY_rect[2] = { &background_RECT, &player_RECT };
	int ARRAY_texturesState[2] = { 1, 1 };

	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	bool quit = false;
	while (!quit)
		while (SDL_PollEvent(&event))
		{
			SDL_PumpEvents(); // обработчик событий.

			if (event.type == SDL_QUIT) 
			{
				quit = true;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN) 
			{
				if (event.button.button == SDL_BUTTON_LEFT && event.button.x <= 10 && event.button.y <= 10) 
				{
					quit = true;
				}
				if (event.button.button == SDL_BUTTON_RIGHT) 
				{
					ARRAY_texturesState[1] = 1;
				}
				if ((event.button.button == SDL_BUTTON_LEFT) && (event.button.x >= player_RECT.x) &&
					(event.button.y >= player_RECT.y) &&
					(event.button.x <= player_RECT.w + player_RECT.x) &&
					(event.button.y <= player_RECT.h + player_RECT.y)) 
				{
					ARRAY_texturesState[1] = 0;
				}
			}


			if ((keyboardState[SDL_SCANCODE_UP]) || (keyboardState[SDL_SCANCODE_W]))
				move_UP(ren, player, player_RECT);

			if ((keyboardState[SDL_SCANCODE_DOWN]) || (keyboardState[SDL_SCANCODE_S]))
				move_DOWN(ren, player, player_RECT);

			if ((keyboardState[SDL_SCANCODE_LEFT]) || (keyboardState[SDL_SCANCODE_A]))
				move_LEFT(ren, player, player_RECT);

			if ((keyboardState[SDL_SCANCODE_RIGHT]) || (keyboardState[SDL_SCANCODE_D]))
				move_RIGHT(ren, player, player_RECT);


			//ZOOM----------------------------------------------------------------
			if (keyboardState[SDL_SCANCODE_KP_PLUS])
			{
				TESTtexture_SCALE += 0.02;
				player_RECT.h = player_HEIGH * TESTtexture_SCALE;
				player_RECT.w = player_WIGHT * TESTtexture_SCALE;
			}
			if (keyboardState[SDL_SCANCODE_KP_MINUS])
			{
				TESTtexture_SCALE -= 0.02;
				player_RECT.h = player_HEIGH * TESTtexture_SCALE;
				player_RECT.w = player_WIGHT * TESTtexture_SCALE;
			}

			render_UPDATE(ren, ARRAY_textures, ARRAY_rect, ARRAY_texturesState);	//Написанная нами функция обновления рендера
			SDL_RenderPresent(ren);


		}
//Перед тем как все закончить нам нужно удалить наши текстуры из памяти.
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(background);
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 1;
	
	
}

void ss()
{
	double previous = getCurrentTime();
	double lag = 0.0;
	
	while (true)
	{
		double current = getCurrentTime(); // текущее время
		double elapsed = current - previous; // время потраченное на 1 игровой цикл
		previous = current;
		lag += elapsed;

		processInput();

		while (lag >= MS_PER_UPDATE) // выделим на один апдейт не больше "500" миллисекунд
		{
			update();
			lag -= MS_PER_UPDATE;
		}

		render();
	}
}