#include "Demo.h"

using namespace Engine;

Demo::Demo(Setting* setting) :Game(setting)
{

}


Demo::~Demo()
{
	delete spriteTexture;
	delete monsterTexture;
	delete dotTexture;
	delete spriteSprite;
	delete spriteSprite2;
	delete monsterSprite;
	delete dotSprite1;
	delete dotSprite2;
	delete dotSprite3;
	delete dotSprite4;
	delete music;
	delete text;
}

void Demo::Init()
{
	spriteTexture = new Texture("sprite.png");
	spriteSprite = new Sprite(spriteTexture, defaultSpriteShader, defaultQuad);
	spriteSprite->SetPosition((setting->screenWidth * 0.5f) - (spriteSprite->GetScaleWidth() * 0.5f),
		(setting->screenHeight * 0.5f) - (spriteSprite->GetScaleHeight() * 0.5f));
	spriteSprite->SetRotation(0);
	spriteSprite->SetScale(1.2f);
	spriteSprite->SetFlipVertical(true);

	spriteSprite2 = new Sprite(spriteTexture, defaultSpriteShader, defaultQuad);
	spriteSprite2->SetPosition((setting->screenWidth * 0.5f) - (spriteSprite2->GetScaleWidth() * 0.5f), 0);
	spriteSprite2->SetRotation(0);

	// a monster spritesheet has 6 cols and 2 rows (total frames = 6x2 = 12 frames)
	monsterTexture = new Texture("monster.png");
	monsterSprite = new Sprite(monsterTexture, defaultSpriteShader, defaultQuad);
	// Set monster sprite position 
	// 0,0 is at bottom left of the screen and width, height is at top right
	monsterSprite->SetPosition(800, 0);
	// set num cols in spritesheet
	monsterSprite->SetNumXFrames(6);
	// set num rows in spritesheet
	monsterSprite->SetNumYFrames(2);
	// Set animation speed more duration the speed will become slower
	monsterSprite->SetAnimationDuration(150);
	monsterSprite->SetScale(4.0f);
	// Add Animation name, start frame index, end frame index
	monsterSprite->AddAnimation("idle", 0, 3);
	monsterSprite->AddAnimation("walk", 6, 11);
	// If frame size / sprite size is contain blank space or padding then you must resize the bounding box
	// or collision shape to improve collision detection accuracy
	monsterSprite->SetBoundingBoxSize(monsterSprite->GetScaleWidth() - (16 * monsterSprite->GetScale()),
		monsterSprite->GetScaleHeight() - (4 * monsterSprite->GetScale()));

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);

	// Add input mapping 
	/*inputManager->AddInputMapping("Rotate Right", SDLK_e);
	inputManager->AddInputMapping("Rotate Left", SDLK_q);*/
	inputManager->AddInputMapping("Move Up", SDLK_w);
	inputManager->AddInputMapping("Move Down", SDLK_s);
	inputManager->AddInputMapping("Move Right", SDLK_d);
	inputManager->AddInputMapping("Move Left", SDLK_a);
	inputManager->AddInputMapping("Walk Right", SDLK_RIGHT);
	inputManager->AddInputMapping("Walk Left", SDLK_LEFT);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);

	// Playing music
	music = new Music("bensound-funkyelement.ogg");
	music->SetVolume(30);
	music->Play(true);

	sound = new Sound("stepwood_1.wav");
	sound->SetVolume(80);

	text = new Text("lucon.ttf", 14, defaultTextShader);
	text->SetScale(1.0f);
	text->SetColor(255, 255, 255);
	text->SetPosition(0, setting->screenHeight - (text->GetFontSize() * text->GetScale()));

	//Set the background color
	SetBackgroundColor(23, 23, 23);

}

void Demo::Update()
{
	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	float speed = 0.0f;
	//if (inputManager->IsKeyPressed("Rotate Right")) {
	//	speed = -0.1f;
	//}

	//if (inputManager->IsKeyPressed("Rotate Left")) {
	//	speed = 0.1f;
	//}

	float degree = speed * GetGameTime();

	spriteSprite->SetRotation(spriteSprite->GetRotation() + degree);

	float xspeed = 0, yspeed = 0;

	if (inputManager->IsKeyPressed("Move Up")) {
		yspeed = 0.08f;
		spriteSprite->SetPosition(spriteSprite->GetPosition().x + xspeed * GetGameTime(),
			spriteSprite->GetPosition().y + yspeed * GetGameTime());
	}

	if (inputManager->IsKeyPressed("Move Down")) {
		yspeed = -0.08f;
		spriteSprite->SetPosition(spriteSprite->GetPosition().x + xspeed * GetGameTime(),
			spriteSprite->GetPosition().y + yspeed * GetGameTime());
	}

	if (inputManager->IsKeyPressed("Move Right")) {
		xspeed = 0.08f;
		spriteSprite->SetPosition(spriteSprite->GetPosition().x + xspeed * GetGameTime(),
			spriteSprite->GetPosition().y + yspeed * GetGameTime());
	}

	if (inputManager->IsKeyPressed("Move Left")) {
		xspeed = -0.08f;
		spriteSprite->SetPosition(spriteSprite->GetPosition().x + xspeed * GetGameTime(),
			spriteSprite->GetPosition().y + yspeed * GetGameTime());
	}

	bool isCollided = spriteSprite2->GetBoundingBox()->CollideWith(spriteSprite->GetBoundingBox());
	text->SetText((isCollided ? "[Collision = Yes]" : "[Collision = No]") +
		("[FPS = " + to_string(currentFrameRate)) +
		"] Press W-A-S-D-Q-E to Move");

	monsterSprite->PlayAnim("idle");

	// Move monster sprite using keyboard
	vec2 oldMonsterPos = monsterSprite->GetPosition();
	if (inputManager->IsKeyPressed("Walk Right")) {
		xspeed = 0.04f;
		monsterSprite->PlayAnim("walk");
		monsterSprite->SetPosition(oldMonsterPos.x + xspeed * GetGameTime(),
			oldMonsterPos.y);
		monsterSprite->SetFlipHorizontal(false);
		if (!sound->IsPlaying())
			sound->Play(false);
	}

	if (inputManager->IsKeyPressed("Walk Left")) {
		xspeed = -0.04f;
		monsterSprite->PlayAnim("walk");
		monsterSprite->SetPosition(oldMonsterPos.x + xspeed * GetGameTime(),
			oldMonsterPos.y);
		monsterSprite->SetFlipHorizontal(true);
		if (!sound->IsPlaying())
			sound->Play(false);
	}

	// Update monster sprite animation
	monsterSprite->Update(GetGameTime());

	BoundingBox* bb = monsterSprite->GetBoundingBox();
	if (spriteSprite2->GetBoundingBox()->CollideWith(bb)) {
		//revert position if collided
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y);
	}
	
	//Render shape for debug
	dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()), 
		bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()), 
		bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()), 
		bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()), 
		bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));



}

void Demo::Render()
{
	spriteSprite2->Draw();
	spriteSprite->Draw();
	monsterSprite->Draw();
	dotSprite1->Draw();
	dotSprite2->Draw();
	dotSprite3->Draw();
	dotSprite4->Draw();
	text->Draw();
}


//int main(int argc, char** argv) {
//	Setting* setting = new Setting();
//	setting->windowTitle = "Project Example";
//	setting->screenWidth = 1024;
//	setting->screenHeight = 768;
//	setting->windowFlag = WindowFlag::WINDOWED;
//	Game* game = new Demo(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}
