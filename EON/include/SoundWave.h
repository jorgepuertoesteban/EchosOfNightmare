#pragma once

#include "Vec2.h"
#include "Pointer.h"
#include "PVector.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Scene;
class Trail;

class SoundWave : public sf::Drawable {
	public:
		SoundWave(GameObject *gameobj, int lifetime);
		~SoundWave();
		void Update();
		bool GetDead();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Pointer<GameObject>  m_gObj;
		std::vector<Vec2>    m_points;
		sf::VertexArray      m_trail;
		unsigned int		 m_lifetime;
		sf::Clock			 m_clockLife,
			                 m_clockTrail;
		bool				 m_TrailFree;
		bool				 m_dead;
};