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
		int  GetId();
		void SetColor(int,int,int);
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Pointer<GameObject>  m_gObj;
		std::vector<Point>    m_points;
		sf::VertexArray      m_trail;
		unsigned int		 m_lifetime;
		sf::Clock			 m_clockLife,
			                 m_clockTrail;
		bool				 m_TrailFree,
							 m_dead,
			                 m_delete;
		int                  m_r, 
							 m_g, 
							 m_b;
};