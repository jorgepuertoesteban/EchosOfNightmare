#include <SFML\Audio.hpp>
#include "Pointer.h"
#include "Vec2.h"

class GameObject;
class Map;
class Magnet {
	public:
		Magnet(GameObject * = nullptr, Map* map = nullptr);
		~Magnet();
		int  GetId();
		void Update();
		Vec2 GetPosition();
private:
	void GenerateSound();
		Pointer<GameObject>  m_gObj;
		sf::SoundBuffer m_buffer;
		sf::Sound       m_sound;
		Map             *m_map;
		sf::Clock		m_clockWaves;
};
