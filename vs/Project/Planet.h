#ifndef Planet_H
#define Planet_H
#include "Sprite.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
namespace Engine {
    class Planet :
        public Engine::Sprite
    {
    public:
        Planet(Texture* texture, Shader* shader, Quad* quad, Setting* setting) :Sprite(texture, shader, quad) {
            this->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
        };
        ~Planet();
        void UpdateObject(int score, float gameTime, Setting* setting);
    };
}
#endif

