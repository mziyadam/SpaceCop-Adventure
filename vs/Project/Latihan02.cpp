#include "Latihan02.h"
using namespace Engine;
using namespace std;

Latihan02::Latihan02(Setting* setting) :Game(setting)
{

}

Engine::Latihan02::~Latihan02()
{
}

void Engine::Latihan02::Render()
{
	sprite->Draw();
}

void Engine::Latihan02::Update()
{
	sprite->Update(GetGameTime());
}

void Engine::Latihan02::Init()
{
	texture = new Texture("small_star.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(60);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("move", 0, 59);
	sprite->PlayAnim("move");
	sprite->SetAnimationDuration(100);
}
int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "Project Example";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = WindowFlag::WINDOWED;
	//setting->targetFrameRate = 60;
	Game* game = new Latihan02(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
