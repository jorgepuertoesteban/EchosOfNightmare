#include "EventListener.h"

const Event2Method EventListener::m_events[4] = {
	  { sf::Event::Closed               , &Closed      }
	 ,{ sf::Event::KeyPressed           , &KeyPressed  }
	 ,{ sf::Event::KeyReleased          , &KeyReleased }
	 ,{ -1                              , 0            }
};
EventListener::EventListener():m_window(nullptr){
	for (unsigned int i = 0; i<sf::Keyboard::KeyCount; ++i)
		m_keys[i] = false;
}
EventListener::~EventListener(){
}
void EventListener::Inicialize(sf::RenderWindow *window) {
	m_window = window;
}
void EventListener::CheckEvents(){
	sf::Event event_recieved;
	while (m_window->pollEvent(event_recieved)){
		const Event2Method * it = m_events;
		while (it->event != -1){
			if (it->event == event_recieved.type) {
				(this->*it->Event2Method::p)(event_recieved.key.code);
				break;
			}
			it++;
		}
	}
}
bool EventListener::IsKeyDown(unsigned int keyCode) const {
	return m_keys[keyCode];
}
void EventListener::Closed(unsigned int key){
	m_window->close();
}
void EventListener::KeyPressed(unsigned int key) {
	m_keys[key] = true;
}
void EventListener::KeyReleased(unsigned int key) {
	m_keys[key] = false;
}