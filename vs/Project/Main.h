#ifndef MAIN_H
#define MAIN_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Meteor.h"
#include "Background.h"
#include "Planet.h"
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
		Texture* startTexture = NULL;
		Texture* startHoverTexture = NULL;
		Texture* quitTexture = NULL;
		Texture* quitHoverTexture = NULL;
		Texture* titleTexture = NULL;

		Sprite* spaceCopSprite = NULL;
		Meteor* meteorSprite[15];
		Planet* planetSprite[15];
		Background* backgroundSprite = NULL;
		Sprite* startSprite = NULL;
		Sprite* startHoverSprite = NULL;
		Sprite* quitSprite = NULL;
		Sprite* quitHoverSprite = NULL;
		Sprite* titleSprite = NULL;

		Music* music = NULL;
		Sound* sound = NULL;
		Text* scoreText = NULL;
		Text* titleText = NULL;
		Text* startText = NULL;
		Text* quitText = NULL;
		float timeCounter = 0.0f;
		float backgroundCounter = 0.0f;
		float spawnLength = 0.0f;
		int objectCounter = 1;
		int score = -120;
		bool isPaused = true;
		bool isStarted = false;
		bool isStartHover = true;
		void start();
	};
}
#endif

