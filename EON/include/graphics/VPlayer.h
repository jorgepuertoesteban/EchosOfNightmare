#pragma once

#include <SFML/Graphics.hpp>
#include "VisualBody.h"

class VPlayer: public VisualBody{
    public:
        VPlayer();
        virtual ~VPlayer();
		virtual void Initialize(Vec2 tam);
		virtual bool   GetVisible();
		virtual void   SetPosition(Vec2 pos);
        virtual void   SetRotation(float angle);
		virtual void   SetVisible(bool aux);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	    bool                     m_visible,
								 m_setedPos;
		Vec2					 m_actPos;
		sf::Texture              m_texture[3];
		sf::Texture              *m_actualTxt;
		sf::Sprite               m_sprite;
};
