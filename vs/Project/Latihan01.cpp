#include "Latihan01.h"
using namespace Engine;
using namespace std;

Latihan01::Latihan01(Setting* setting) :Game(setting)
{

}

Engine::Latihan01::~Latihan01()
{
}

void Engine::Latihan01::Render()
{
}

void Engine::Latihan01::Update()
{
	if (color_duration >= 100) {
		if (r >= 255)
			isLimit = true;
		if (r <= 0)
			isLimit = false;
		if (isLimit) {
			r -= 25;
		}
		else {
			r += 25;
	}
		
		SetBackgroundColor(r, g, b);
		color_duration = 0;
		}
	color_duration += GetGameTime();
	}

	
	
	


void Engine::Latihan01::Init()
{
	//Set the background color
	//SetBackgroundColor(80, 250, 70);
}
//int main(int argc, char** argv) {
//	Setting* setting = new Setting();
//	setting->windowTitle = "Project Example";
//	setting->screenWidth = 1024;
//	setting->screenHeight = 768;
//	setting->windowFlag = WindowFlag::WINDOWED;
//	//setting->targetFrameRate = 60;
//	Game* game = new Latihan01(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}
