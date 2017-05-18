 #pragma once

#include "Map.h"
#include "Pointer.h"
#include "PVector.h"

class PhysicWorld;
class ContactListener;
class Goal;
class Wall;

class Map_Intro: public Map{
	public:
		Map_Intro(sf::View*);
		virtual ~Map_Intro();
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
		void EndMap();
		void UpdateSoundWaves();
		void UpdateText();
		Pointer<PhysicWorld>     m_pPhysiworld;
		sf::Font                 m_font;
		sf::Text                 m_text;
		sf::RectangleShape       m_rect;
		sf::Clock                m_clockStart,
			                     m_clockEnd;
		sf::View                 *m_view;
		PVector<SoundWave>       m_soundWaves;
		PVector<GameObject>      m_Walls;
		Pointer<ContactListener> m_pContactListener;
		PhysicWorld              *m_physiworld;
		EventListener			 *m_listener;
		bool                     m_start,
			                     m_end,
								 m_finished;
		const char               *m_path        = "Media/Maps/Intro.tmx",
						         *m_tutoStrings = "Press ENTER to start";
};
