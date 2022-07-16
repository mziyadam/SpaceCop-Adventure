#include "Main.h"

using namespace Engine;

Main::Main(Setting* setting) :Game(setting)
{

}


Main::~Main()
{
	delete spaceCopTexture;
	delete spaceCopSprite;
	delete backgroundTexture;
	delete backgroundSprite;
	delete music;
	delete scoreText;
}

void Main::Init()
{
	//INIT BACKGROUND
	backgroundTexture = new Texture("space_background.png");
	backgroundSprite = new Background(backgroundTexture, defaultSpriteShader, defaultQuad,setting);
	backgroundSprite->SetPosition((0),
		(0));

	//INIT BUTTON
	startTexture = new Texture("start.png");
	startSprite=new Sprite(startTexture, defaultSpriteShader, defaultQuad);
	startSprite->SetPosition(setting->screenWidth / 2 -100 , 250);
	startSprite->SetScale(0.5f);

	startHoverTexture = new Texture("start-hover.png");
	startHoverSprite=new Sprite(startHoverTexture, defaultSpriteShader, defaultQuad);
	startHoverSprite->SetPosition(setting->screenWidth / 2- 100, 250);
	startHoverSprite->SetScale(0.0f);

	quitTexture = new Texture("quit.png");
	quitSprite=new Sprite(quitTexture, defaultSpriteShader, defaultQuad);
	quitSprite->SetPosition(setting->screenWidth/2 - 100  , 175);
	quitSprite->SetScale(0.5f);

	quitHoverTexture = new Texture("quit-hover.png");
	quitHoverSprite=new Sprite(quitHoverTexture, defaultSpriteShader, defaultQuad);
	quitHoverSprite->SetPosition(setting->screenWidth/2 - 100 , 175);
	quitHoverSprite->SetScale(0.0f);


	//INIT SPACECOP
	spaceCopTexture = new Texture("spacecop-spritesheet.png");
	spaceCopSprite = new Sprite(spaceCopTexture, defaultSpriteShader, defaultQuad);
	spaceCopSprite->SetNumXFrames(60);
	spaceCopSprite->SetNumYFrames(1);
	spaceCopSprite->AddAnimation("move", 0, 59);
	spaceCopSprite->PlayAnim("move");
	spaceCopSprite->SetAnimationDuration(50);
	spaceCopSprite->SetPosition((setting->screenWidth * 0.5f) - (spaceCopSprite->GetScaleWidth() * 0.5f),
		(setting->screenHeight * 0.5f) - (spaceCopSprite->GetScaleHeight() * 0.5f));
	spaceCopSprite->SetRotation(0);
	spaceCopSprite->SetScale(1.2f);

	//INIT TEXTURE PLANET AND METEOR
	planetTexture = new Texture("planet.png");
	meteorTexture = new Texture("meteor.png");
	for (int i = 0; i < 15; i++) {
		//INIT PLANET
		planetSprite[i] = new Planet(planetTexture, defaultSpriteShader, defaultQuad,setting);

		//INIT METEOR
		meteorSprite[i] = new Meteor(meteorTexture, defaultSpriteShader, defaultQuad,setting);
	}

	//INPUT MAPPING
	inputManager->AddInputMapping("Move Up", SDLK_w);
	inputManager->AddInputMapping("Play Pause", SDLK_SPACE);
	inputManager->AddInputMapping("Move Down", SDLK_s);
	inputManager->AddInputMapping("Move Right", SDLK_d);
	inputManager->AddInputMapping("Enter", SDLK_RETURN);
	inputManager->AddInputMapping("Move Left", SDLK_a);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);

	//PLAY MUSIC
	music = new Music("undertale_49.ogg");
	music->SetVolume(100);
	music->Play(true);

	//CRASH SOUND
	sound = new Sound("crash.wav");
	sound->SetVolume(80);

	//SCORE TEXT
	scoreText = new Text("imprint.ttf", 24, defaultTextShader);
	scoreText->SetScale(1.0f);
	scoreText->SetColor(236, 227, 23);
	scoreText->SetPosition(setting->screenWidth - (scoreText->GetFontSize() * scoreText->GetScale() * 5) - 25, setting->screenHeight - (scoreText->GetFontSize() * scoreText->GetScale()) - 25);
	//scoreText->SetScale(0.0f);

	//TITLE TEXT
	titleText = new Text("imprint.ttf", 36, defaultTextShader);
	titleText->SetScale(1.0f);
	titleText->SetColor(236, 227, 23);
	titleText->SetPosition(setting->screenWidth / 2 - (titleText->GetFontSize() * titleText->GetScale() * 5), setting->screenHeight - (titleText->GetFontSize() * titleText->GetScale()) - 100);
	
	titleTexture = new Texture("title-spritesheet.png");
	titleSprite = new Sprite(titleTexture, defaultSpriteShader, defaultQuad);
	titleSprite->SetNumXFrames(2);
	titleSprite->SetNumYFrames(1);
	titleSprite->AddAnimation("light", 0, 1);
	titleSprite->PlayAnim("light");
	titleSprite->SetAnimationDuration(500);
	titleSprite->SetPosition(setting->screenWidth / 2 - ( titleSprite->GetScaleWidth() * 0.5f), setting->screenHeight - (titleSprite->GetScaleHeight() *0.5f) - 100);
	titleSprite->SetRotation(0);
	titleSprite->SetScale(1.0f);

	//START TEXT
	startText = new Text("imprint.ttf", 32, defaultTextShader);
	startText->SetScale(1.0f);
	startText->SetColor(236, 227, 23);
	startText->SetPosition(setting->screenWidth / 2 - (startText->GetFontSize() * startText->GetScale() * 5), 100);

	//QUIT TEXT
	quitText = new Text("imprint.ttf", 24, defaultTextShader);
	quitText->SetScale(1.0f);
	quitText->SetColor(236, 227, 23);
	quitText->SetPosition(setting->screenWidth - (quitText->GetFontSize() * quitText->GetScale() * 5) - 25, 25);
}

void Main::Update()
{
	//CHECK BEFORE START CONDITION
	if (!isStarted) {
		//titleText->SetText("Space Cop Adventure");
		titleSprite->Update(GetGameTime());
		if (isStartHover) {
			startHoverSprite->SetScale(0.5f);
			quitHoverSprite->SetScale(0.0f);
		}
		else {
			startHoverSprite->SetScale(0.0f);
			quitHoverSprite->SetScale(0.5f);
		}
		if (inputManager->IsKeyReleased("Move Up")) {
			isStartHover = true;
		}
		if (inputManager->IsKeyReleased("Move Down")) {
			isStartHover = false;
		}
		if (inputManager->IsKeyReleased("Enter")) {
			startHoverSprite->SetScale(0.0f);
			startSprite->SetScale(0.0f);
			quitSprite->SetScale(0.0f);
			quitHoverSprite->SetScale(0.0f);
			if (isStartHover) {
				isPaused = false;
				isStarted = true;
			}
			else {
				state = State::EXIT;
				return;
			}

		}
	}
	if (!isPaused) {
		spaceCopSprite->Update(GetGameTime());
		quitText->SetText("Quit (Esc)");
		titleSprite->SetScale(0.0f);
		if (inputManager->IsKeyReleased("Quit")) {
			isPaused=true;
			return;
		}
		
		if (backgroundCounter >= 15000) {
			backgroundSprite->UpdateObject(GetGameTime(), setting,true);
			backgroundCounter = 0.0f;
		}
		else {
			backgroundSprite->UpdateObject(GetGameTime(), setting, false);
		}
		backgroundCounter += GetGameTime();


		if (timeCounter >= (10000+spawnLength)) {
			spawnLength += 5000;
			timeCounter = 0;
			if(objectCounter<=15)
				objectCounter += 1;
		}
		timeCounter += GetGameTime();
		titleText->SetScale(0.0f);
		startText->SetScale(0.0f);
		for (int i = 0; i < objectCounter; i++) {
			//PLANET MOVEMENT
			planetSprite[i]->UpdateObject(score,GetGameTime(),setting);
			//METEOR MOVEMENT
			meteorSprite[i]->UpdateObject(score, GetGameTime(), setting);
			//ADD SCORE
			score += (0.055f * GetGameTime());
		}

		//INPUT HANDLING
		float x = spaceCopSprite->GetPosition().x;
		float y = spaceCopSprite->GetPosition().y;
		float speed = 0.1f;
		if (score > 0)
			speed = 0.1f + 0.00015f * score;
		float width = setting->screenWidth;
		float height = setting->screenHeight;

		if (inputManager->IsKeyPressed("Move Up")) {
			if (y <= (height - spaceCopSprite->GetScaleHeight())) {
				y += speed * GetGameTime();
			}
		}

		if (inputManager->IsKeyPressed("Move Down")) {
			if (y >= 0) {
				y -= speed * GetGameTime();
			}
		}

		if (inputManager->IsKeyPressed("Move Right")) {
			if (x <= (width - spaceCopSprite->GetScaleWidth())) {
				x += speed * GetGameTime();
			}
		}

		if (inputManager->IsKeyPressed("Move Left")) {
			if (x >= 0) {
				x -= speed * GetGameTime();
			}
		}
		spaceCopSprite->SetPosition(x, y);
		scoreText->SetText("Score: " + (score >= 0 ?
			to_string(score) : "0"));

		BoundingBox* bb = spaceCopSprite->GetBoundingBox();
		for (int i = 0; i < objectCounter; i++) {
			if (meteorSprite[i]->GetBoundingBox()->CollideWith(bb) || planetSprite[i]->GetBoundingBox()->CollideWith(bb)) {
				isPaused = true;
				if (!sound->IsPlaying())
					sound->Play(false);
			}
		}
	}
	else {
		titleText->SetScale(1.0f);
		startText->SetScale(1.0f);
		objectCounter = 1;
		if (isStarted) {
			titleText->SetPosition(setting->screenWidth / 2 - (titleText->GetFontSize() * titleText->GetScale() * 2), setting->screenHeight - (titleText->GetFontSize() * titleText->GetScale()) - 100);
			titleText->SetText("Game Over");
			startText->SetText("Press 'Spacebar' to Retry");
			quitText->SetText("Quit (Esc)");
			if (inputManager->IsKeyReleased("Play Pause")) {
				score = 0;
				isPaused = false;
				start();
			}
			if (inputManager->IsKeyReleased("Quit")) {
				state = State::EXIT;
				return;
			}
		}
	}
}

void Main::Render()
{
	backgroundSprite->Draw();
	startSprite->Draw();
	startHoverSprite->Draw();
	quitSprite->Draw();
	quitHoverSprite->Draw();
	spaceCopSprite->Draw();
	titleSprite->Draw();
	for (int i = 0; i < 15; i++) {
		meteorSprite[i]->Draw();
		planetSprite[i]->Draw();
	}
	scoreText->Draw();
	titleText->Draw();
	startText->Draw();
	quitText->Draw();
}

void Main::start() {
	spaceCopSprite->SetPosition((setting->screenWidth * 0.5f) - (spaceCopSprite->GetScaleWidth() * 0.5f),
		(setting->screenHeight * 0.5f) - (spaceCopSprite->GetScaleHeight() * 0.5f));
	for (int i = 0; i < 15; i++) {
		planetSprite[i]->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
		meteorSprite[i]->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
	}
}

int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "Space Cop Adventure";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = WindowFlag::WINDOWED;
	setting->targetFrameRate = 60;
	Game* game = new Main(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
