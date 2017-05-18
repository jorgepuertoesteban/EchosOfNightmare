 #pragma once

#include "Map.h"
#include "Pointer.h"
#include "PVector.h"

class PhysicWorld;
class ContactListener;
class Goal;
class Wall;

class Map_2: public Map{
	public:
		Map_2(sf::View*);
		virtual ~Map_2();
		virtual void Inicialice(EventListener*);
		virtual void Update();
		virtual void Render(sf::RenderWindow*);
		virtual void CheckEvents();
		virtual bool Success();
		virtual void Life();
		virtual void Dead();
		virtual bool End();
		virtual void ReadXML();
		virtual void        CreateEnemy(Vec2 pos);
		virtual void        CreatePlayer(Vec2 pos);
		virtual void        CreateRock(Vec2 pos, Vec2 dir);
		virtual void        CreateGoal(Vec2 pos, Vec2 size, int rotation);
		virtual void        CreateWall(Vec2 pos, Vec2 size, int rotation);
		virtual void        CreateWater(Vec2 pos,Vec2 size, int rotation);
		virtual void        CreateDeadWall(Vec2 pos, Vec2 size, int rotation);
		virtual void        CreateSoundWave(Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r = 255, int g = 255, int b = 255, PhysicBody * = nullptr);
		virtual GameObject* CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 size, Vec2 pos);
		PVector<SoundWave>* GetSoundWaves();
		PVector<Enemy>*     GetEnemies();
		PVector<Rock>*      GetRocks();
		virtual Player*     GetPlayer();
private:
		bool Start();
		void StartFinish();
		void EndMap();
		void UpdateIntro();
		void UpdateGameObjects();
		void UpdateSoundWaves();
		void UpdateEnemies();
		void UpdateRocks();
		void UpdateText();
		void CheckFinish();
		Pointer<PhysicWorld>     m_pPhysiworld;
		sf::Font                 m_font;
		sf::Text                 m_text;
		sf::Clock                m_clockStart,
			                     m_clockEnd;
		sf::View                 *m_view;
		PVector<SoundWave>       m_soundWaves;
		PVector<Enemy>           m_enemies;
		PVector<Rock>            m_rocks;
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
			                     m_success,
								 m_finished,
							     m_learn;
		const char               *m_path        = "Media/Maps/map2.tmx",
		                         *m_mapName     = "Loneless",
						         *m_tutoStrings = "Hold and release Space to make noise";
};

