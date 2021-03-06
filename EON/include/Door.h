#include <SFML\Audio.hpp>
#include "Pointer.h"
#include "Vec2.h"

class GameObject;
class Map;
class Door {
	public:
		Door(GameObject * = nullptr, Map *map = nullptr, int id = 0);
		~Door();
		void Update();
		void Press();
		void MakeNoise(int num, Vec2 pos);
		bool GetPressed();
		int  GetId();
private:
		Pointer<GameObject>  m_gObj;
		Map                  *m_map;
		int			         m_door;
		bool                 m_pressed;
		sf::SoundBuffer      m_buffer;
		sf::Sound            m_sound;
};
