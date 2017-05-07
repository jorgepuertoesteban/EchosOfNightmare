#pragma once

#include "Vec2.h"

class GameObject;
class Scene;

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
		Player(GameObject * = nullptr, Scene * = nullptr);
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
		Scene        *m_scene;
		Direction    m_sDirection;
		bool         m_sound;
};