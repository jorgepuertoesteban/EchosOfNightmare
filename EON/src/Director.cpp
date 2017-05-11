#include "Director.h"
#include "Map_1.h"

Director::Director():m_closed(false){
	m_pScene.Reset(new Map_1);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10000;
	m_pWindow.Reset(new sf::RenderWindow(sf::VideoMode(600, 600), "Echoes of nightmare.", sf::Style::Default, settings));
	m_window = m_pWindow.Get();
	m_window->setVerticalSyncEnabled(true);
	m_scene = m_pScene.Get();
	m_eventListener.Inicialize(m_window);
	m_scene->Inicialice(&m_eventListener);
	m_window->setFramerateLimit(60);
}
Director::~Director(){
}
bool Director::Update() {
	m_eventListener.CheckEvents();
	m_scene->Update();
	return m_window->isOpen();
}
void Director::Render() {
	m_window->clear(sf::Color::Black);
	m_scene->Render(m_window);
	m_window->display();
}