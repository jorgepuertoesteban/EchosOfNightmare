#pragma once

#include "Vec2.h"
#include "SFML\Graphics.hpp"

class GameObject;
class EventListener;
class Map;


class Player {
	public:
		Player(GameObject * = nullptr, Map * = nullptr);
		~Player();
		bool Step();
		void Update();
		void KissOfDead();
		void KissOfLife();
		Vec2 GetPosition();
		void SetEventListener(EventListener *events);
		void MakeSound(bool);
		void GenerateSound(unsigned int count, unsigned int lifetime, float velocity);
	private:


		struct Direction {
			bool W = false;
			bool S = false;
			bool A = false;
			bool D = false;
			bool Shift = false;
			int lastH = 0;
			int lastV = 0;
		};

		void Move();
		void CalcDir();
		void CheckEvents();
		void CalcAngle();
		void ThrowRock(bool);
		Vec2	       m_dir;
		unsigned int   m_speed;
		float		   m_angle;
		GameObject     *m_gObj;
		Map            *m_map;
		Direction      m_sDirection;
		bool           m_sound,
			           m_rock,
			           m_walking,
			           m_kissOfDead,			
			           m_kissOfLife,
					   m_finish;
		sf::Clock      m_clockSound,
					   m_clockStep,
					   m_clockEvents;
		EventListener  *m_events;
};