#pragma once

#include "Vec2.h"
#include "Pointer.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Scene;
class Map;



class Rock : public sf::Drawable {
	public:
		Rock(GameObject *gameobj, Map*);
		~Rock();
		void Update();
		bool GetDead();
		int  GetId();
		void Colision();
	private:
		void GenerateSound();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Pointer<GameObject>  m_gObj;
		sf::VertexArray      m_trail;
		unsigned int		 m_lifetime;
		sf::Clock			 m_clockTrail;
		bool				 m_colisioned,
							 m_dead,
							 m_sound;
		Map                  *m_map;
};