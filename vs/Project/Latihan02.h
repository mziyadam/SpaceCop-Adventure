#ifndef Latihan01_H
#define Latihan01_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
namespace Engine {
	class Latihan02 :public Engine::Game
	{
	public:
		Latihan02(Setting* setting);
		~Latihan02();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture *texture=NULL;
		/*Engine::Sprite *sprite=NULL;*/
		map<int, Sprite*> mSprites;
		int cnt = 0;
		
		bool isXFlipped = false;
		float countTime = 0.0f;
		float counter = 0.0f;
	};
}
#endif

