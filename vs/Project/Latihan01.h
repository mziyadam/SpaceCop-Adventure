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
	class Latihan01:public Engine::Game
	{
	public:
		Latihan01(Setting* setting);
		~Latihan01();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		float color_duration = 0, r = 100, g = 0, b = 0;
		bool isLimit = false;
	};
}
#endif

