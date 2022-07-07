#include "Meteor.h"


Engine::Meteor::~Meteor()
{
}

void Engine::Meteor::UpdateObject(int score, float gameTime, Setting* setting)
{
	float xMeteor = this->GetPosition().x;
	float yMeteor = this->GetPosition().y;
	float velocityMeteor = 0.1f;
	if (score > 0)
		velocityMeteor = 0.1f + 0.0001f * score;
	cout << "VELOCITY METEOR :" << velocityMeteor << endl;
	if (yMeteor <= 0) {
		this->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
	}
	else {
		yMeteor -= velocityMeteor * gameTime;
		this->SetPosition(xMeteor, yMeteor);
	}
	score += (0.055f * gameTime);
}
