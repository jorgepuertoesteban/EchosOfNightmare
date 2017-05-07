#pragma once

#include "Vec2.h"

class VisualBody : public sf::Drawable {
    public:
		virtual ~VisualBody() {}
		virtual void Initialize(Vec2 tam) = 0;
		virtual bool   GetVisible() = 0;
		virtual void   SetPosition(Vec2 pos) = 0;
		virtual void   SetRotation(float angle) = 0;
		virtual void   SetVisible(bool aux) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	protected:		
}; 



