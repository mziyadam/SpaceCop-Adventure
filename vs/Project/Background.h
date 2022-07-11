#ifndef Backgound_H
#define Background_H

#include "Sprite.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
namespace Engine {
	class Background :
		public Engine::Sprite
	{
    public:
        Background(Texture* texture, Shader* shader, Quad* quad, Setting* setting) :Sprite(texture, shader, quad) {
            this->SetPosition(0,0);
        };
        ~Background();
        void UpdateObject( float gameTime, Setting* setting,bool isReset);        
    };

}
#endif
