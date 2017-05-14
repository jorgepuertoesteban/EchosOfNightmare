#pragma once

#include <SFML/Graphics.hpp>
#include "VisualBody.h"

class VEnemy: public VisualBody{
    public:
        VEnemy();
        virtual ~VEnemy();
		virtual void Initialize(Vec2 tam);
		virtual bool   GetVisible();
		virtual void   SetPosition(Vec2 pos);
        virtual void   SetRotation(float angle);
		virtual void   SetVisible(bool aux);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	    bool                m_visible;
		sf::RectangleShape  m_rect;
};