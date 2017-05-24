#pragma once

class Map;
class Player;
class Enemy;
class Wall;
class DeadWall;
class Goal;
class XMLReader;

struct Layer2Method {
	char* layer;
	void (XMLReader::*p)();
};

class XMLReader{
	public:
		XMLReader();
		~XMLReader();
		void Inicialize(Map *, const char*);
	private:
		void AddPlayer();
		void AddEnemy();
		void AddWall();
		void AddWater();
		void AddGoal();
		void AddDoor();
		void AddDeadWall();
		void AddMechanism();
		Map*    m_map;
		float   m_x,
				m_y,
				m_width,
				m_height,
				m_rotation;
		int		m_name;
		static const Layer2Method m_layers[9];
};
