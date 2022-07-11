#include "Background.h"

Engine::Background::~Background()
{
}

void Engine::Background::UpdateObject(float gameTime, Setting* setting,bool isReset)
{

	float xBg = this->GetPosition().x;
	float yBg = this->GetPosition().y;
	float speedBg = 0.05f;

	if (isReset) {
		this->SetPosition(0, 0);
	}
	else {
		yBg -= speedBg * gameTime;
		this->SetPosition(xBg, yBg);
	}


}
