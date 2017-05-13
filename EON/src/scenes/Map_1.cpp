#include "Map_1.h"
#include "GameObject.h"
#include "PhysicWorld.h"
#include "VSoundWave.h"
#include "VPlayer.h"
#include "VEnemy.h"
#include "Enemy.h"
#include "VBox.h"
#include "VWall.h"
#include "VDeadWall.h"
#include "physicbodies\PBSoundWave.h"
#include "physicbodies\PBPlayer.h"
#include "physicbodies\PBEnemy.h"
#include "physicbodies\PBWall.h"
#include "physicbodies\PBWater.h"
#include "physicbodies\PBGoal.h"
#include "physicbodies\PBDeadWall.h"
#include "ContactListener.h"
#include "XMLReader.h"
#include "EventListener.h"
#include "SoundWave.h"
#include <iostream>

Map_1::Map_1(sf::View* view):m_end(false), m_finished(false){
	m_pPhysiworld.Reset(new PhysicWorld);
	m_physiworld = m_pPhysiworld.Get();
	m_pContactListener.Reset(new ContactListener(this)); 
	m_physiworld->SetContactListener(m_pContactListener.Get());
	ReadXML();
	m_view = view;
}
Map_1::~Map_1(){
}
void Map_1::Inicialice(EventListener* listener) {
	m_listener = listener;
}
void Map_1::Update(){
	m_physiworld->Update();
	m_player.Update();
	for (auto it = m_enemies.GetBegin(); it != m_enemies.GetEnd(); it++) {
		(*it)->Update();
	}
	CheckEvents();
	for (auto itGO = m_gameObjects.GetBegin(); itGO != m_gameObjects.GetEnd(); itGO++) {
		(*itGO)->Update();
	}
	if (m_finished && !m_end && m_clockEnd.getElapsedTime().asMilliseconds() > 5000) {
		auto itEn = m_enemies.GetBegin();
		while (itEn != m_enemies.GetEnd()) {
			int index = std::distance(m_enemies.GetBegin(), itEn);
			itEn = m_enemies.Remove(index);
		}
		auto itSW = m_soundWaves.GetBegin();
		while (itSW != m_soundWaves.GetEnd()) {
			int index = std::distance(m_soundWaves.GetBegin(), itSW);
			itSW = m_soundWaves.Remove(index);
		}
		m_end = true;
	}
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
	m_view->setCenter(m_player.GetPosition().x, m_player.GetPosition().y);
}
void Map_1::Render(sf::RenderWindow *window){
	for (auto it = m_Walls.GetBegin(); it != m_Walls.GetEnd(); it++) {
		if ((*it)->Visible())
			window->draw(*(*it));
	}
	for (auto it = m_soundWaves.GetBegin(); it != m_soundWaves.GetEnd(); it++) {
		window->draw(*(*it));
	}
	if (!m_finished) {
		for (auto it = m_gameObjects.GetBegin(); it != m_gameObjects.GetEnd(); it++) {
			if ((*it)->Visible())
				window->draw(*(*it));
		}
	}
	for (auto it = m_enemies.GetBegin(); it != m_enemies.GetEnd(); it++) {
			window->draw(*(*it));
	}
}
void Map_1::CheckEvents() {
	m_player.SetW(m_listener->IsKeyDown(sf::Keyboard::W));
	m_player.SetS(m_listener->IsKeyDown(sf::Keyboard::S));
	m_player.SetA(m_listener->IsKeyDown(sf::Keyboard::A));
	m_player.SetD(m_listener->IsKeyDown(sf::Keyboard::D));
	m_player.SetShift(m_listener->IsKeyDown(sf::Keyboard::LShift) || m_listener->IsKeyDown(sf::Keyboard::RShift));
	m_player.MakeSound(m_listener->IsKeyDown(sf::Keyboard::Space));
}
void Map_1::ReadXML() {
	XMLReader reader;
	reader.Inicialize(this, m_path);
}
void Map_1::Life() {
	m_player.KissOfLife();
	EndMap();
}
void Map_1::Dead() {
	m_player.KissOfDead();
	EndMap();
}
void Map_1::EndMap() {
	m_clockEnd.restart();
	m_finished = true;
}
GameObject* Map_1::CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 pos, Vec2 size) {
	m_physiworld->CreateBody(pB,  pos,  size);
	vB->Initialize(size);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pB, vB);
	m_gameObjects.Add(gObj);
	return gObj;
}
void Map_1::CreateEnemy(Vec2 pos) {
	GameObject *goEnemy = CreateGameObject(new PBEnemy, new VEnemy, pos, Vec2(50, 50));
	goEnemy->SetVisible(false);
	m_enemies.Add(new Enemy(goEnemy, this));
	m_player = Player(goEnemy, this);
}
void Map_1::CreatePlayer(Vec2 pos) {
	GameObject *goPlayer = CreateGameObject(new PBPlayer, new VPlayer, pos, Vec2(50, 50));
	m_player = Player(goPlayer, this);
}

void Map_1::CreateGoal(Vec2 pos, Vec2 size, int rotation) {
	PBGoal *pgoal = new PBGoal;
	VWall  *vgoal = new VWall;
	m_physiworld->CreateBody(pgoal, pos, size);
	vgoal->Initialize(size);
	vgoal->SetPosition(Vec2(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f)));
	vgoal->SetRotation((float)rotation);
	float radians = rotation * 3.141592653589793f / 180.f;
	pgoal->SetRotationFromCorner(radians);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pgoal, vgoal);
	gObj->SetVisible(false);
	m_pGoal.Reset(gObj);
}
void Map_1::CreateWater(Vec2 pos, Vec2 size, int rotation) {
	PBWater *pwater = new PBWater;
	VWall  *vwall = new VWall;
	m_physiworld->CreateBody(pwater, pos, size);
	vwall->Initialize(size);
	vwall->SetPosition(Vec2(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f)));
	vwall->SetRotation((float)rotation);
	float radians = rotation * 3.141592653589793f / 180.f;
	pwater->SetRotationFromCorner(radians);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pwater, vwall);
	gObj->SetVisible(false);
	m_Waters.Add(gObj);
}
void Map_1::CreateWall(Vec2 pos, Vec2 size, int rotation) {
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
void Map_1::CreateDeadWall(Vec2 pos, Vec2 size, int rotation) {
	PBDeadWall *pwall = new PBDeadWall;
	VDeadWall  *vwall = new VDeadWall;
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
void Map_1::CreateSoundWave(Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r, int g, int b, PhysicBody *pB) {
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
PVector<SoundWave>* Map_1::GetSoundWaves() {
	return &m_soundWaves;
}
PVector<Enemy>* Map_1::GetEnemies() {
	return &m_enemies;
}
bool Map_1::End() {
	return m_end;
}