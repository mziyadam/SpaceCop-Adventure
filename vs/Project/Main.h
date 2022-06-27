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
		Texture* spriteTexture = NULL;
		Texture* monsterTexture = NULL;
		Texture* dotTexture = NULL;
		Sprite* spriteSprite = NULL;
		Sprite* spriteSprite2 = NULL;
		Sprite* monsterSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Music* music = NULL;;
		Sound* sound = NULL;
		Text* text = NULL;

	};
}
#endif

