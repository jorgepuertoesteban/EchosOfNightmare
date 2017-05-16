#pragma once

#include "Vec2.h"
#include "Pointer.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Scene;

struct Point {
	float x, y;
	int r, g, b;
	Point() { r = g = b = 255; x = y = 0; }
	Point(Vec2 v) { x = v.x; y = v.y;  r = g = b = 255; }
	Point(Vec2 v, int r, int g, int b):r(r), g(g), b(b) { x = v.x; y = v.y; }
};

class Rock : public sf::Drawable {
	public:
		Rock(GameObject *gameobj);
		~Rock();
		void Update();
		bool GetDead();
		int  GetId();
		void Colision();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Pointer<GameObject>  m_gObj;
		Point                m_points[4];
		sf::VertexArray      m_trail;
		unsigned int		 m_lifetime;
		sf::Clock			 m_clockTrail;
		bool				 m_colisioned,
							 m_dead;
};