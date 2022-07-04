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
	backgroundSprite = new Sprite(backgroundTexture, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetPosition((0),
		(0));

	//INIT SPACECOP
	spaceCopTexture = new Texture("space_cop.png");
	spaceCopSprite = new Sprite(spaceCopTexture, defaultSpriteShader, defaultQuad);
	spaceCopSprite->SetPosition((setting->screenWidth * 0.5f) - (spaceCopSprite->GetScaleWidth() * 0.5f),
		(setting->screenHeight * 0.5f) - (spaceCopSprite->GetScaleHeight() * 0.5f));
	spaceCopSprite->SetRotation(0);
	spaceCopSprite->SetScale(1.2f);

	//INIT PLANET
	planetTexture = new Texture("planet.png");
	for (int i = 0; i < 15; i++) {
		planetSprite[i] = new Sprite(planetTexture, defaultSpriteShader, defaultQuad);
		planetSprite[i]->SetPosition((rand() % setting->screenWidth), setting->screenHeight);

		//INIT METEOR
		meteorTexture = new Texture("meteor.png");
		meteorSprite[i] = new Sprite(meteorTexture, defaultSpriteShader, defaultQuad);
		meteorSprite[i]->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
	}

	//INPUT MAPPING
	inputManager->AddInputMapping("Move Up", SDLK_w);
	inputManager->AddInputMapping("Play Pause", SDLK_SPACE);
	inputManager->AddInputMapping("Move Down", SDLK_s);
	inputManager->AddInputMapping("Move Right", SDLK_d);
	inputManager->AddInputMapping("Move Left", SDLK_a);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);

	//PLAY MUSIC
	music = new Music("undertale_49.ogg");
	music->SetVolume(30);
	//music->Play(true);

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
	//scoreText->SetScale(0.0f);

	//START TEXT
	startText = new Text("imprint.ttf", 32, defaultTextShader);
	startText->SetScale(1.0f);
	startText->SetColor(236, 227, 23);
	startText->SetPosition(setting->screenWidth / 2 - (startText->GetFontSize() * startText->GetScale() * 5), 100);
	//scoreText->SetScale(0.0f);

	//QUIT TEXT
	quitText = new Text("imprint.ttf", 24, defaultTextShader);
	quitText->SetScale(1.0f);
	quitText->SetColor(236, 227, 23);
	quitText->SetPosition(setting->screenWidth - (quitText->GetFontSize() * quitText->GetScale() * 5) - 25, 25);
	//scoreText->SetScale(0.0f);
}

void Main::Update()
{
	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}
	if (!isStarted) {
		titleText->SetText("Space Cop Adventure");
		startText->SetText("Press 'Spacebar' to Start");
		quitText->SetText("Quit (Esc)");
		if (inputManager->IsKeyReleased("Play Pause")) {
			isPaused = false;
			isStarted = true;
		}
		if (inputManager->IsKeyReleased("Quit")) {
			state = State::EXIT;
			return;
		}
	}
	if (!isPaused) {
		if (timeCounter >= (10000+spawnLength)) {
			spawnLength += 5000;
			timeCounter = 0;
			if(objectCounter<=50)
				objectCounter += 1;
		}
		timeCounter += GetGameTime();
		titleText->SetScale(0.0f);
		startText->SetScale(0.0f);
		for (int i = 0; i < objectCounter; i++) {
			//Planet Movement
			float xPlanet = planetSprite[i]->GetPosition().x;
			float yPlanet = planetSprite[i]->GetPosition().y;
			float velocityPlanet = 0.1f;
			if (score > 0)
				velocityPlanet = 0.1f + 0.00015f * score;
			cout << "VELOCITY PLANET :" << velocityPlanet << endl;
			if (yPlanet <= 0) {
				planetSprite[i]->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
			}
			else {
				yPlanet -= velocityPlanet * GetGameTime();
				planetSprite[i]->SetPosition(xPlanet, yPlanet);
			}

			//Meteor Movement
			float xMeteor = meteorSprite[i]->GetPosition().x;
			float yMeteor = meteorSprite[i]->GetPosition().y;
			float velocityMeteor = 0.1f;
			if (score > 0)
				velocityMeteor = 0.1f + 0.0001f * score;
			cout << "VELOCITY METEOR :" << velocityMeteor << endl;
			if (yMeteor <= 0) {
				meteorSprite[i]->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
			}
			else {
				yMeteor -= velocityMeteor * GetGameTime();
				meteorSprite[i]->SetPosition(xMeteor, yMeteor);
			}
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
		}
		if (inputManager->IsKeyReleased("Play Pause")) {
			score = 0;
			isPaused = false;
			start();
		}
	}
}

void Main::Render()
{
	backgroundSprite->Draw();
	spaceCopSprite->Draw();
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
	setting->windowTitle = "Project Example";
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
