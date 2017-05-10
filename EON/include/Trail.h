#pragma once

#include "Vec2.h"
#include "Pointer.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Scene;

class Trail : public sf::Drawable {
	public:
		Trail(Vec2 tam,Vec2 pos,float rotation);
		~Trail();
		void Update();
		bool GetDead();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::RectangleShape   m_rect;
		int					 m_lifetime;
		sf::Clock			 m_clockLife;
		sf::Clock			 m_clockVanish;
		bool				 m_dead;
};