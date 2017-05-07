#pragma once

#include <SFML/Graphics.hpp>

class EventListener;

struct Event2Method{
	unsigned int event;
    void(EventListener::*p)(unsigned int);
};

class EventListener{
	public:
		EventListener();
		~EventListener();
		void Inicialize(sf::RenderWindow *window);
		bool IsKeyDown(unsigned int keyCode) const;
		void CheckEvents();
	private:
		bool m_keys[sf::Keyboard::KeyCount];
		void Closed(unsigned int);
		void KeyPressed(unsigned int);
		void KeyReleased(unsigned int);
		sf::RenderWindow *m_window;
		static const Event2Method m_events[4];
};

