#pragma once

#include "Scene.h"
#include "Vec2.h"

class GameObject;
class PhysicBody;
class VisualBody;

class Map: public Scene {
	public:
		virtual ~Map() {}
		virtual void Inicialice(EventListener*) = 0;
		virtual void Update() = 0;
		virtual void CheckEvents() = 0;
		virtual void ReadXML() = 0;
		virtual GameObject* CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 size, Vec2 pos) = 0;
		virtual void        CreateWall(Vec2 pos, Vec2 size, int rotation) = 0;
		virtual void        CreatePlayer    (Vec2 pos) = 0;
		virtual void        CreateSoundWave (Vec2 pos, Vec2 dir) = 0;
};

