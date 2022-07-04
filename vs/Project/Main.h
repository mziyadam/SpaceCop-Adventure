#ifndef MAIN_H
#define MAIN_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"

namespace Engine {
	class Main :
		public Engine::Game
	{
	public:
		Main(Setting* setting);
		~Main();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Texture* spaceCopTexture = NULL;
		Texture* planetTexture = NULL;
		Texture* meteorTexture = NULL;
		Texture* backgroundTexture = NULL;

		Sprite* spaceCopSprite = NULL;
		Sprite* meteorSprite[15];
		Sprite* planetSprite[15];
		Sprite* backgroundSprite = NULL;

		Music* music = NULL;
		Sound* sound = NULL;
		Text* scoreText = NULL;
		Text* titleText = NULL;
		Text* startText = NULL;
		Text* quitText = NULL;
		float timeCounter = 0.0f;
		float spawnLength = 0.0f;
		int objectCounter = 1;
		int score = -120;
		bool isPaused = true;
		bool isStarted = false;
		void start();
	};
}
#endif

