#include "Director.h"
#include "Map_1.h"

Director::Director():m_closed(false){
	sf::VideoMode vM = sf::VideoMode::getDesktopMode();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10000;
	m_view = sf::View(sf::FloatRect(0, 0, (float)vM.width, (float)vM.height));
	m_pWindow.Reset(new sf::RenderWindow(vM, "Echoes of nightmare.", sf::Style::Default, settings));
	m_window = m_pWindow.Get();
	m_window->setVerticalSyncEnabled(true);
	m_window->setFramerateLimit(45);
	m_window->setView(m_view);
	NextScene();
}
Director::~Director(){
}
bool Director::Update() {
	m_eventListener.CheckEvents();
	if (m_eventListener.IsKeyDown(sf::Keyboard::Escape)) {
		m_window->close();
	}
	m_scene->Update();
	if (m_scene->End()) {
		NextScene();
	}
	m_window->setView(m_view);
	return m_window->isOpen();
}
void Director::Render() {
	m_window->clear(sf::Color::Black);
	m_scene->Render(m_window);
	m_window->display();
}
void Director::NextScene() {
	m_pScene.Reset(new Map_1(&m_view));
	m_scene = m_pScene.Get();
	m_eventListener.Inicialize(m_window);
	m_scene->Inicialice(&m_eventListener);
}