#pragma once

#include "Vec2.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

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
		void SetInWater(bool);
		void SetEventListener(EventListener *events);
		void MakeSound(bool);
		void ApplyForce(Vec2);
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
		sf::SoundBuffer m_bufferStep[4];
		sf::SoundBuffer m_bufferWater[2];
		sf::SoundBuffer m_bufferClap[3];
		sf::SoundBuffer m_bufferDeath;
		sf::SoundBuffer m_bufferLife;
		sf::Sound       m_soundWater;
		sf::Sound       m_soundStep;
		sf::Sound       m_soundClap;
		sf::Sound       m_soundDeath;
		sf::Sound       m_soundLife;
		Vec2	        m_dir;
		unsigned int    m_speed,
						m_stepCount;
		float		    m_angle;
		GameObject      *m_gObj;
		Map             *m_map;
		Direction       m_sDirection;
		bool            m_sound,
			            m_rock,
			            m_walking,
			            m_kissOfDead,			
			            m_kissOfLife,
					    m_inWater,
					    m_finish;
		sf::Clock       m_clockSound,
					    m_clockStep,
					    m_clockEvents;
		unsigned int    m_timeStep;
		EventListener   *m_events;

};