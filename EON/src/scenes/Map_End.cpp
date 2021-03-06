#include "Map_End.h"
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

Map_End::Map_End(sf::View* view):m_end(false), m_start(false){
	m_pPhysiworld.Reset(new PhysicWorld);
	m_physiworld = m_pPhysiworld.Get();
	m_pContactListener.Reset(new ContactListener(this)); 
	m_physiworld->SetContactListener(m_pContactListener.Get());
	ReadXML();
	m_view = view;
	m_view->setCenter(0,0);
	m_clockStart.restart();
	m_font.loadFromFile("Media/Fonts/OpenSans-Regular.ttf");
	m_rect.setFillColor(sf::Color(255, 255, 255, 0));
	m_rect.setSize(sf::Vector2f(4000, 4000));
	m_rect.setPosition(sf::Vector2f(-2000,-2000));
	m_text.setCharacterSize(60);
	m_text.setFont(m_font);
	sf::Color color = sf::Color::White;
	color.a = 250;
	m_text.setFillColor(color);
	m_text.setString(m_tutoStrings);
	m_text.setPosition(sf::Vector2f(0 - m_text.getLocalBounds().width / 2, 100));

	m_bufferIntro.loadFromFile("Media/Sounds/Intro.wav");
	m_soundIntro.setBuffer(m_bufferIntro);
}
Map_End::~Map_End(){
	m_soundWaves.Clear();
	m_pContactListener.Reset(nullptr);
}
void Map_End::Inicialice(EventListener* listener) {
	m_listener = listener;
}
bool Map_End::Success() {
	return true;
}
void Map_End::Update(){
	if (m_start) {
		EndMap();
	}
	m_physiworld->Update();
	CheckEvents();
	UpdateSoundWaves();
	UpdateText();
}
void Map_End::UpdateText() {
	sf::Color color = m_text.getFillColor();
	if (!m_black) {
		if (color.a > 100)
			color.a = color.a - 10;
		else
			m_black = true;
	}
	else {
		if (color.a < 250)
			color.a = color.a + 10;
		else
			m_black = false;
	}
	m_text.setFillColor(color);
}
void Map_End::Render(sf::RenderWindow *window){
	window->draw(m_text);
	for (auto it = m_soundWaves.GetBegin(); it != m_soundWaves.GetEnd(); it++) {
		window->draw(*(*it));
	}
	window->draw(m_rect);
}
void Map_End::CheckEvents() {
	if (!m_start && m_listener->IsKeyDown(sf::Keyboard::Return)) {
		m_soundIntro.play();
		m_start = true;
	}
}
void Map_End::ReadXML() {
	XMLReader reader;
	reader.Inicialize(this, m_path);
}
void Map_End::CreateWall(Vec2 pos, Vec2 size, int rotation) {
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
void Map_End::CreateSoundWave(Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r, int g, int b, PhysicBody *pB) {
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
void Map_End::CreatePlayer(Vec2 pos) {
	//USADO PARA CREAR LAS ONDAS
	auto plus = rand() % 45;
	unsigned int cont = 12;
	for (unsigned int i = 0; i < cont; i++) {
		float angle = ((i / (float)cont) * 360) + plus;
		CreateSoundWave(pos, Vec2(sinf(angle*3.14f / 180.f), cosf(angle*3.14f / 180.f)) * 6, Vec2(4,4), 99999);
	}

}
PVector<SoundWave>* Map_End::GetSoundWaves() {
	return &m_soundWaves;
}
bool Map_End::End() {
	return m_end;
}
void Map_End::EndMap() {
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
void Map_End::UpdateSoundWaves() {
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
GameObject* Map_End::CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 pos, Vec2 size) {
	return nullptr;
}
PVector<Enemy>* Map_End::GetEnemies() {
	return nullptr;
}
PVector<Magnet>* Map_End::GetMagnets() {
	return nullptr;
}
PVector<Mechanism>* Map_End::GetMechanisms() {
	return nullptr;
}
PVector<Door>* Map_End::GetDoors() {
	return nullptr;
}
PVector<Rock>* Map_End::GetRocks() {
	return nullptr;
}
Player* Map_End::GetPlayer() {
	return nullptr;
}
void Map_End::Life() {}
void Map_End::Dead() {}
void Map_End::CreateEnemy(Vec2 pos) {}
void Map_End::CreateMagnet(Vec2 pos) {};
void Map_End::CreateRock(Vec2 pos, Vec2 dir) {}
void Map_End::CreateMechanism(Vec2 pos, Vec2 size, int rotation, int door) {}
void Map_End::CreateDoor(Vec2 pos, Vec2 size, int rotation, int door) {}
void Map_End::CreateGoal(Vec2 pos, Vec2 size, int rotation) {}
void Map_End::CreateWater(Vec2 pos, Vec2 size, int rotation) {}
void Map_End::CreateDeadWall(Vec2 pos, Vec2 size, int rotation) {}