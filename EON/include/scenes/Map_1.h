 #pragma once

#include "Map.h"
#include "Pointer.h"
#include "PVector.h"

class PhysicWorld;
class ContactListener;
class SoundWave;
class Goal;
class Wall;
class Player;

class Map_1: public Map{
	public:
		Map_1(sf::View*);
		virtual ~Map_1();
		virtual void Inicialice(EventListener*);
		virtual void Update();
		virtual void Render(sf::RenderWindow*);
		virtual void CheckEvents();
		virtual void Life();
		virtual void Dead();
		virtual bool End();
		virtual void ReadXML();
		virtual void        CreateEnemy(Vec2 pos);
		virtual void        CreatePlayer(Vec2 pos);
		virtual void        CreateGoal(Vec2 pos, Vec2 size, int rotation);
		virtual void        CreateWall(Vec2 pos, Vec2 size, int rotation);
		virtual void        CreateWater(Vec2 pos,Vec2 size, int rotation);
		virtual void        CreateDeadWall(Vec2 pos, Vec2 size, int rotation);
		virtual void        CreateSoundWave(Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r = 255, int g = 255, int b = 255, PhysicBody * = nullptr);
		virtual GameObject* CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 size, Vec2 pos);
		PVector<SoundWave>* GetSoundWaves();
		PVector<Enemy>*     GetEnemies();
	private:
		bool Start();
		void StartFinish();
		void EndMap();
		void UpdateIntro();
		void RenderIntro(sf::RenderWindow *window);
		void UpdateGameObjects();
		void UpdateSoundWaves();
		void UpdateEnemies();
		void CheckFinish();
		Pointer<PhysicWorld>     m_pPhysiworld;
		sf::Font                 m_font;
		sf::Text                 m_text;
		sf::Clock                m_clockStart,
			                     m_clockEnd;
		sf::View                 *m_view;
		PVector<SoundWave>       m_soundWaves;
		PVector<Enemy>           m_enemies;
		PVector<GameObject>      m_gameObjects,
			                     m_Walls,
			                     m_Waters;
		Pointer<GameObject>      m_pGoal;
		Pointer<ContactListener> m_pContactListener;
		PhysicWorld              *m_physiworld;
		EventListener			 *m_listener;
		Pointer<Player>			 m_player;
		bool                     m_start,
			                     m_end,
								 m_finished;
		const char*              m_path = "Media/Maps/map1.tmx";
};

