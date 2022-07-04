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
	//sprite->Draw();
	for (int i = 0; i < 100; i++) {
		mSprites.find(i)->second->Draw();
	}
}
void spawnSprite(Texture *texture,Sprite *sprite, float gameTime,float *countTime,float width, float height){
	sprite->Update(gameTime);
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.1f;
	/*if (isXFlipped) {
		x -= velocity * GetGameTime();
	}
	else {
		x += velocity * GetGameTime();
	}
	if (x >= (width-sprite->GetScaleWidth())) {
		isXFlipped = true;
		sprite->SetFlipHorizontal(true);
	}
	if (x <= 0) {
		isXFlipped = false;
		sprite->SetFlipHorizontal(false);
	}*/
	if (y <= 0) {
		if (*countTime < 2000) {
			*countTime += gameTime;
			y += velocity * gameTime;
		}
		else if (*countTime >= 2000) {
			sprite->SetSize(0, 0);
			*countTime = 0;
		}
	}
	y -= velocity * gameTime;
	sprite->SetPosition(x, y);

}
void Engine::Latihan02::Update()
{
	
	/*sprite->Update(GetGameTime());
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.1f;
	float width = setting->screenWidth;
	float height = setting->screenHeight;*/
	
	/*if (isXFlipped) {
		x -= velocity * GetGameTime();
	}
	else {
		x += velocity * GetGameTime();
	}
	if (x >= (width-sprite->GetScaleWidth())) {
		isXFlipped = true;
		sprite->SetFlipHorizontal(true);
	}
	if (x <= 0) {
		isXFlipped = false;
		sprite->SetFlipHorizontal(false);
	}*/
	/*if (inputManager->IsKeyPressed("turn-left")) {
		if (x>=0) {
			x -= velocity * GetGameTime();
			sprite->SetFlipHorizontal(true);
		}
	}
	if (inputManager->IsKeyPressed("turn-right")) {
		if (x<= (width - sprite->GetScaleWidth())) {
			x += velocity * GetGameTime();
			sprite->SetFlipHorizontal(false);
		}
	}*/
		if (counter < 2000) {
			if (cnt < 100) {
				auto it = mSprites.find(cnt);
				
				spawnSprite(texture, it->second, GetGameTime(), &countTime, setting->screenWidth, setting->screenHeight);
				cnt++;
			}
			/*counter += GetGameTime();
			texture = new Texture("woman-run.png");
			sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
			sprite->SetNumXFrames(6);
			sprite->SetNumYFrames(5);
			sprite->AddAnimation("move", 0, 11);
			sprite->PlayAnim("move");
			sprite->SetAnimationDuration(100);
			sprite->SetPosition(rand() % setting->screenWidth, setting->screenHeight);*/
			

		}
		else if (counter >= 2000) {
			
			counter = 0;
		}
	
	//if (y <= 0) {
	//	if (countTime < 2000) {
	//		countTime += GetGameTime();
	//		y += velocity * GetGameTime();
	//	}
	//	else if (countTime >= 2000) {
	//		sprite->SetSize(0,0);
	//		//countTime = 0;
	//	}
	//}
	//y -= velocity * GetGameTime();
	//sprite->SetPosition(x, y);

}

void Engine::Latihan02::Init()
{
	texture = new Texture("woman-run.png");
	//sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	//sprite->SetNumXFrames(6);
	//sprite->SetNumYFrames(5);
	//sprite->AddAnimation("move", 0, 11);
	//sprite->PlayAnim("move");
	//sprite->SetAnimationDuration(100);
	//// insert elements in random order
	//sprite->SetPosition(rand() % setting->screenWidth, setting->screenHeight);
	//mSprites.insert(pair<int, Sprite*>(1, sprite));
	for (int i = 0; i < 100; i++) {
		Engine::Sprite* sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
		sprite->SetNumXFrames(6);
		sprite->SetNumYFrames(5);
		sprite->AddAnimation("move", 0, 11);
		sprite->PlayAnim("move");
		sprite->SetAnimationDuration(100);
		// insert elements in random order
		int randWidth = rand() % setting->screenWidth;
		
		sprite->SetPosition(randWidth, setting->screenHeight);
		//sprite->Draw();
		mSprites.insert(pair<int, Sprite*>(i, sprite));
	}
	/*sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(5);
	sprite->AddAnimation("move", 0, 11);
	sprite->PlayAnim("move");
	sprite->SetAnimationDuration(100);*/
	// insert elements in random order
	//sprite->SetPosition(rand() % setting->screenWidth, setting->screenHeight);
	//mSprites.insert(pair<int, Sprite*>(1, sprite));
	//rand() % width;
	/*texture = new Texture("spaceCop.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(1);
	sprite->SetNumYFrames(1);*/
	inputManager->AddInputMapping("turn-left", SDLK_a);
	inputManager->AddInputMapping("turn-left", SDLK_LEFT);
	inputManager->AddInputMapping("turn-right", SDLK_d);
	inputManager->AddInputMapping("turn-right", SDLK_RIGHT);
}
//int main(int argc, char** argv) {
//	Setting* setting = new Setting();
//	setting->windowTitle = "Project Example";
//	setting->screenWidth = 1024;
//	setting->screenHeight = 768;
//	setting->windowFlag = WindowFlag::WINDOWED;
//	setting->targetFrameRate = 60;
//	Game* game = new Latihan02(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}
