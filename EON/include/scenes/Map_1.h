 #pragma once

#include "Map.h"
#include "Pointer.h"
#include "PVector.h"
#include "Player.h"

class PhysicWorld;
class ContactListener;
class SoundWave;
class Wall;

class Map_1: public Map{
	public:
		Map_1();
		virtual ~Map_1();
		virtual void Inicialice(EventListener*);
		virtual void Update();
		virtual void Render(sf::RenderWindow*);
		virtual void CheckEvents();
		virtual void ReadXML();
		virtual GameObject* CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 size, Vec2 pos);
		virtual void        CreateWall(Vec2 pos,Vec2 size, int rotation);
		virtual void        CreatePlayer(Vec2 pos);
		virtual void        CreateSoundWave(Vec2 pos, Vec2 dir, int lifetime);
private:
		Pointer<PhysicWorld>     m_pPhysiworld;
		PVector<SoundWave>       m_soundWaves;
		PVector<GameObject>      m_gameObjects;
		PVector<GameObject>      m_Walls;
		Pointer<ContactListener> m_pContactListener;
		PhysicWorld              *m_physiworld;
		EventListener			 *m_listener;
		Player			         m_player;
		const char*              m_path = "Media/Maps/map1.tmx";
};

