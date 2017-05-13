#pragma once

#include "Vec2.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Map;

class Enemy: public sf::Drawable {
	public:
		Enemy(GameObject * = nullptr, Map * = nullptr);
		~Enemy();
		void Update();
		void SetTarget(Vec2);
		int GetId();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Move();
		void CalcDir();
		bool ReachTarget();
		void GenerateSound(unsigned int count);
		bool         m_stoped;
		Vec2	     m_target,
					 m_dir;
		unsigned int m_speed;
		GameObject   *m_gObj;
		Map          *m_map;
		sf::Clock    m_clockSound;
};