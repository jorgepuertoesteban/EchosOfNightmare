#include "Director.h"
#include "Map_1.h"
#include "Map_Intro.h"
#include "SceneFabric.h"

Director::Director():m_closed(false){
	sf::VideoMode vM = sf::VideoMode::getDesktopMode();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;
	m_view = sf::View(sf::FloatRect(0, 0, (float)vM.width, (float)vM.height));
	m_pWindow.Reset(new sf::RenderWindow(vM, "Echoes of nightmare.", sf::Style::Fullscreen, settings));
	//m_pWindow.Reset(new sf::RenderWindow(sf::VideoMode(1600,1600*9/16.f), "Echoes of nightmare.", sf::Style::Default, settings));
	m_window = m_pWindow.Get();
	m_eventListener.Inicialize(m_window);
	m_window->setVerticalSyncEnabled(true);
	m_window->setFramerateLimit(30);
	m_window->setMouseCursorVisible(false);
	m_window->setView(m_view);
	m_sFabric.Reset(new SceneFabric(&m_view));
	m_scene = m_sFabric.Get()->GetNext();
	m_scene->Inicialice(&m_eventListener);
}
Director::~Director(){
}
bool Director::Update() {
	m_eventListener.CheckEvents();
	if (m_eventListener.IsKeyDown(sf::Keyboard::Escape)) {
		m_window->close();
	}
	if (m_scene->End()) {
		NextScene();
	}
	else {
		m_scene->Update();
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
	if(m_scene->Success())
		m_scene = m_sFabric.Get()->GetNext();
	else
		m_scene = m_sFabric.Get()->GetSame();
		if (m_scene) {
		m_scene->Inicialice(&m_eventListener);
	}
	else {
		m_window->close();
	}
}