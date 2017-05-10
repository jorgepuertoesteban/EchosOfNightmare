#pragma once

#include "Vec2.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Map;

struct Direction {
	bool W = false;
	bool S = false;
	bool A = false;
	bool D = false;
	int lastH = 0;
	int lastV = 0;
};

class Player {
	public:
		Player(GameObject * = nullptr, Map * = nullptr);
		~Player();
		void Update();
		void SetW(bool);
		void SetS(bool);
		void SetA(bool);
		void SetD(bool);
		void MakeSound(bool aux);
	private:
		void Move();
		void CalcDir();
		void CalcAngle();
		Vec2	     m_dir;
		unsigned int m_speed;
		float		 m_angle;
		GameObject   *m_gObj;
		Map          *m_map;
		Direction    m_sDirection;
		bool         m_sound;

		sf::Clock    m_clockSound;
};