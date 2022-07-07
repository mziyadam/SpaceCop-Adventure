#include "Planet.h"

Engine::Planet::~Planet()
{
}

void Engine::Planet::UpdateObject(int score, float gameTime, Setting* setting)
{
	float xPlanet = this->GetPosition().x;
	float yPlanet = this->GetPosition().y;
	float velocityPlanet = 0.1f;
	if (score > 0)
		velocityPlanet = 0.1f + 0.00015f * score;
	cout << "VELOCITY PLANET :" << velocityPlanet << endl;
	if (yPlanet <= 0) {
		this->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
	}
	else {
		yPlanet -= velocityPlanet * gameTime;
		this->SetPosition(xPlanet, yPlanet);
	}
}
