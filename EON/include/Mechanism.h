#include <SFML\Audio.hpp>
#include "Pointer.h"

class GameObject;
class Mechanism {
	public:
		Mechanism(GameObject * = nullptr, int door = 0);
		~Mechanism();
		void Press();
		bool GetPressed();
		int  GetId();
		int  GetDoor();
private:
		Pointer<GameObject>  m_gObj;
		int			    m_door;
		bool            m_pressed;
		sf::SoundBuffer m_buffer;
		sf::Sound       m_sound;
};
