#pragma once

#include <SFML/Graphics.hpp>
#include "EventListener.h"
#include "Pointer.h"

class SceneFabric;
class Scene;

class Director{
	public:
		Director();
		~Director();
		bool Update();
		void Render();
		void NextScene();
	private:
		Pointer<SceneFabric>      m_sFabric;
		Pointer<sf::RenderWindow> m_pWindow;
		sf::RenderWindow         *m_window;
		sf::View                  m_view;
		Scene        		     *m_scene;
		EventListener			  m_eventListener;
		bool				      m_closed;
};

