#pragma once

#include "Vec2.h"
#include "SFML\Graphics.hpp"

class GameObject;
class Map;

struct Direction {
	bool W     = false;
	bool S     = false;
	bool A     = false;
	bool D     = false;
	bool Shift = false;
	int lastH  = 0;
	int lastV  = 0;
};

class Player {
	public:
		Player(GameObject * = nullptr, Map * = nullptr);
		~Player();
		bool Step();
		void Update();
		void KissOfDead();
		void KissOfLife();
		void SetW(bool);
		void SetS(bool);
		void SetA(bool);
		void SetD(bool);
		void SetShift(bool);
		Vec2 GetPosition();
		void MakeSound(bool);
		void GenerateSound(unsigned int count);
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
		bool         m_sound,
			         m_walking,
			         m_kissOfDead,			
			         m_kissOfLife,
					 m_finish;
		sf::Clock    m_clockSound,
			         m_clockStep;
};