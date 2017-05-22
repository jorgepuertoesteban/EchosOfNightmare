#include "Map_Intro.h"
#include "GameObject.h"
#include "PhysicWorld.h"
#include "VSoundWave.h"
#include "VWall.h"
#include "physicbodies\PBSoundWave.h"
#include "physicbodies\PBWall.h"
#include "ContactListener.h"
#include "XMLReader.h"
#include "EventListener.h"
#include "SoundWave.h"
#include <iostream>

Map_Intro::Map_Intro(sf::View* view):m_end(false), m_start(false){
	m_pPhysiworld.Reset(new PhysicWorld);
	m_physiworld = m_pPhysiworld.Get();
	m_pContactListener.Reset(new ContactListener(this)); 
	m_physiworld->SetContactListener(m_pContactListener.Get());
	ReadXML();
	m_view = view;
	m_view->setCenter(0,0);
	m_clockStart.restart();
	m_font.loadFromFile("Media/Fonts/Bitter-Bold.ttf");
	m_rect.setFillColor(sf::Color(255, 255, 255, 0));
	m_rect.setSize(sf::Vector2f(4000, 4000));
	m_rect.setPosition(sf::Vector2f(-2000,-2000));
	m_text.setCharacterSize(60);
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setString(m_tutoStrings);
	m_text.setPosition(sf::Vector2f(0 - m_text.getLocalBounds().width / 2, 100));

	m_bufferIntro.loadFromFile("Media/Sounds/Intro.wav");
	m_soundIntro.setBuffer(m_bufferIntro);
}
Map_Intro::~Map_Intro(){
	m_soundWaves.Clear();
	m_pContactListener.Reset(nullptr);
}
void Map_Intro::Inicialice(EventListener* listener) {
	m_listener = listener;
}
bool Map_Intro::Success() {
	return true;
}
void Map_Intro::Update(){
	if (m_start) {
		EndMap();
	}
	m_physiworld->Update();
	CheckEvents();
	UpdateSoundWaves();
	UpdateText();
}
void Map_Intro::UpdateText() {
	sf::Color color = m_text.getFillColor();
	color.a = color.a - 5;
	m_text.setFillColor(color);
}
void Map_Intro::Render(sf::RenderWindow *window){
	window->draw(m_text);
	for (auto it = m_soundWaves.GetBegin(); it != m_soundWaves.GetEnd(); it++) {
		window->draw(*(*it));
	}
	window->draw(m_rect);
}
void Map_Intro::CheckEvents() {
	if (!m_start && m_listener->IsKeyDown(sf::Keyboard::Return)) {
		m_soundIntro.play();
		m_start = true;
	}
}
void Map_Intro::ReadXML() {
	XMLReader reader;
	reader.Inicialize(this, m_path);
}
void Map_Intro::CreateWall(Vec2 pos, Vec2 size, int rotation) {
	PBWall *pwall = new PBWall;
	VWall  *vwall = new VWall;
	m_physiworld->CreateBody(pwall, pos, size);
	vwall->Initialize(size);
	vwall->SetPosition(Vec2(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f)));
	vwall->SetRotation((float)rotation);
	float radians = rotation * 3.141592653589793f / 180.f;
	pwall->SetRotationFromCorner(radians);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pwall, vwall);
	gObj->SetVisible(false);
	m_Walls.Add(gObj);
}
void Map_Intro::CreateSoundWave(Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r, int g, int b, PhysicBody *pB) {
	if (!pB) {
		PBSoundWave *pSW = new PBSoundWave;
		pB = pSW;
	}
	VSoundWave  *vB = new VSoundWave;
	m_physiworld->CreateBody(pB, pos, size);
	vB->Initialize(size);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pB, vB);
	gObj->SetLinearVelocity(dir);
	m_soundWaves.Add(new SoundWave(gObj,lifetime,r,g,b));
}

void Map_Intro::CreatePlayer(Vec2 pos) {
	//USADO PARA CREAR LAS ONDAS
	auto plus = rand() % 45;
	unsigned int cont = 15;
	for (unsigned int i = 0; i < cont; i++) {
		float angle = ((i / (float)cont) * 360) + plus;
		CreateSoundWave(pos, Vec2(sinf(angle*3.14f / 180.f), cosf(angle*3.14f / 180.f)) * 6, Vec2(10,10), 99999);
	}

}
PVector<SoundWave>* Map_Intro::GetSoundWaves() {
	return &m_soundWaves;
}
bool Map_Intro::End() {
	return m_end;
}
void Map_Intro::EndMap() {
	if(!m_end) {
		sf::Color color = m_rect.getFillColor();
		if (color.a < 255) {
			color.a = color.a + 5;
			m_rect.setFillColor(color);
		}
		else {
			m_end = true;
		}
	}
}
void Map_Intro::UpdateSoundWaves() {
	auto itSW = m_soundWaves.GetBegin();
	while (itSW != m_soundWaves.GetEnd()) {
		(*itSW)->Update();
		if ((*itSW)->GetDead()) {
			int index = std::distance(m_soundWaves.GetBegin(), itSW);
			itSW = m_soundWaves.Remove(index);
		}
		else {
			itSW++;
		}
	}
}
GameObject* Map_Intro::CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 pos, Vec2 size) {
	return nullptr;
}
PVector<Enemy>* Map_Intro::GetEnemies() {
	return nullptr;
}
PVector<Rock>* Map_Intro::GetRocks() {
	return nullptr;
}
Player* Map_Intro::GetPlayer() {
	return nullptr;
}
void Map_Intro::Life() {}
void Map_Intro::Dead() {}
void Map_Intro::CreateEnemy(Vec2 pos) {}
void Map_Intro::CreateRock(Vec2 pos, Vec2 dir) {}
void Map_Intro::CreateGoal(Vec2 pos, Vec2 size, int rotation) {}
void Map_Intro::CreateWater(Vec2 pos, Vec2 size, int rotation) {}
void Map_Intro::CreateDeadWall(Vec2 pos, Vec2 size, int rotation) {}