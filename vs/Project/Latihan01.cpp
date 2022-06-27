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
	//chrono::steady_clock sc;   // create an object of `steady_clock` class
	//auto start = sc.now();     // start timer
	////int count = 0;
	//// do stuff....

	//auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
	//auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
	////cout << "Operation took: " << time_span.count() << " seconds !!!";
	////count += time_span.count();
	//using namespace std::this_thread; // sleep_for, sleep_until
	//using namespace std::chrono; // nanoseconds, system_clock, seconds
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
		/*if (g >= 255) {
			g = 0;
		}
		else {
			g += 100;
		}
		if (b >= 255) {
			b = 0;
		}
		else {
			b += 5;
		}*/
		SetBackgroundColor(r, g, b);
		color_duration = 0;
		}

	color_duration += GetGameTime();
		//SetBackgroundColor(240, 90, 240);
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
