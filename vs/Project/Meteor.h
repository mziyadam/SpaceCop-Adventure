#ifndef Meteor_H
#define Meteor_H
#include "Sprite.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
namespace Engine {
    class Meteor :
        public Engine::Sprite
    {
    public:
        Meteor(Texture* texture, Shader* shader, Quad* quad,Setting* setting) :Sprite(texture, shader, quad) {
            this->SetPosition((rand() % setting->screenWidth), setting->screenHeight);
        };
        ~Meteor();
        void UpdateObject(int score, float gameTime, Setting* setting);
    };
}
#endif

