#pragma once

#include "Scene.h"
#include "PVector.h"
#include "Vec2.h"

class GameObject;
class PhysicBody;
class SoundWave;
class VisualBody;
class Enemy;
class Rock;

class Map: public Scene {
	public:
		virtual ~Map() {}
		virtual void Inicialice(EventListener*) = 0;
		virtual void Update() = 0;
		virtual void CheckEvents() = 0;
		virtual void Life() = 0;
		virtual void Dead() = 0;
		virtual bool End() = 0;
		virtual void EndMap() = 0;
		virtual void ReadXML() = 0;
		virtual void        CreateEnemy(Vec2 pos) = 0;
		virtual void        CreatePlayer(Vec2 pos) = 0;
		virtual void        CreateRock(Vec2 pos, Vec2 dir) = 0;
		virtual void        CreateGoal(Vec2 pos, Vec2 size, int rotation) = 0;
		virtual void        CreateWall(Vec2 pos, Vec2 size, int rotation) = 0;
		virtual void        CreateWater(Vec2 pos, Vec2 size, int rotation) = 0;
		virtual void        CreateDeadWall(Vec2 pos, Vec2 size, int rotation) = 0;
		virtual void        CreateSoundWave (Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r = 255, int g = 255, int b = 255, PhysicBody * = nullptr) = 0;
		virtual GameObject* CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 size, Vec2 pos) = 0;
		virtual PVector<SoundWave>* GetSoundWaves() = 0;
		virtual PVector<Enemy>*     GetEnemies() = 0;
		virtual PVector<Rock>*      GetRocks() = 0;
};

