#pragma once

#include "Vec2.h"
#include "GameObject.h"

class GameObject;
class Scene;

class SoundWave {
	public:
		SoundWave(GameObject *gameobj);
		~SoundWave();
		void Update();
	private:
		GameObject   *m_gObj;
};