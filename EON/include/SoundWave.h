#pragma once

#include "Vec2.h"
#include "Pointer.h"
#include "PVector.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Scene;
class Trail;

struct Point {
	float x, y;
	int r, g, b;
	Point() { r = g = b = 255; x = y = 0; }
	Point(Vec2 v) { x = v.x; y = v.y;  r = g = b = 255; }
	Point(Vec2 v, int r, int g, int b):r(r), g(g), b(b) { x = v.x; y = v.y; }
};

class SoundWave : public sf::Drawable {
	public:
		SoundWave(GameObject *gameobj, int lifetime);
		~SoundWave();
		void Update();
		bool GetDead();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Pointer<GameObject>  m_gObj;
		std::vector<Point>    m_points;
		sf::VertexArray      m_trail;
		unsigned int		 m_lifetime;
		sf::Clock			 m_clockLife,
			                 m_clockTrail;
		bool				 m_TrailFree;
		bool				 m_dead;
		int                  r = 255, g = 255, b = 255;
};