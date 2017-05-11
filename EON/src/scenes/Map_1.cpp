#include "Map_1.h"
#include "GameObject.h"
#include "PhysicWorld.h"
#include "VSoundWave.h"
#include "VPlayer.h"
#include "VBox.h"
#include "VWall.h"
#include "physicbodies\PBSoundWave.h"
#include "physicbodies\PBPlayer.h"
#include "physicbodies\PBWall.h"
#include "physicbodies\PBBox.h"
#include "ContactListener.h"
#include "XMLReader.h"
#include "EventListener.h"
#include "SoundWave.h"
#include <iostream>

Map_1::Map_1(){
	m_pPhysiworld.Reset(new PhysicWorld);
	m_physiworld = m_pPhysiworld.Get();
	m_pContactListener.Reset(new ContactListener()); 
	m_physiworld->SetContactListener(m_pContactListener.Get());
	ReadXML();
}
Map_1::~Map_1(){
}
void Map_1::Inicialice(EventListener* listener) {
	m_listener = listener;
}
void Map_1::Update(){
	m_physiworld->Update();
	m_player.Update();
	CheckEvents();
	for (auto itGO = m_gameObjects.GetBegin(); itGO != m_gameObjects.GetEnd(); itGO++) {
		(*itGO)->Update();
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
}
void Map_1::Render(sf::RenderWindow *window){
	
	for (auto it = m_Walls.GetBegin(); it != m_Walls.GetEnd(); it++) {
		if ((*it)->Visible())
			window->draw(*(*it));
	}
	for (auto it = m_soundWaves.GetBegin(); it != m_soundWaves.GetEnd(); it++) {
		window->draw(*(*it));
	}
	for (auto it = m_gameObjects.GetBegin(); it != m_gameObjects.GetEnd(); it++) {
		if ((*it)->Visible())
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
GameObject* Map_1::CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 pos, Vec2 size) {
	m_physiworld->CreateBody(pB,  pos,  size);
	vB->Initialize(size);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pB, vB);
	m_gameObjects.Add(gObj);
	return gObj;
}
void Map_1::CreatePlayer(Vec2 pos) {
	GameObject *goPlayer = CreateGameObject(new PBPlayer, new VPlayer, pos, Vec2(35, 35));
	m_player = Player(goPlayer, this);
}
void Map_1::CreateWall(Vec2 pos, Vec2 size, int rotation) {
	PBWall *pwall = new PBWall;
	VWall  *vwall = new VWall;
	m_physiworld->CreateBody(pwall, pos, size);
	vwall->Initialize(size);
	vwall->SetPosition(Vec2(pos.x+(size.x/2.f), pos.y + (size.y / 2.f)));
	vwall->SetRotation((float)rotation);
	float radians = rotation * 3.141592653589793f / 180.f;
	pwall->SetRotation(radians);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pwall, vwall);
	gObj->SetVisible(false);
	m_Walls.Add(gObj);
}
void Map_1::CreateSoundWave(Vec2 pos, Vec2 dir, int lifetime) {
	Vec2 size(15,15);
	VSoundWave  *vB = new VSoundWave;
	PBSoundWave *pB = new PBSoundWave;
	m_physiworld->CreateBody(pB, pos, size);
	vB->Initialize(size);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pB, vB);
	gObj->SetLinearVelocity(dir);
	m_soundWaves.Add(new SoundWave(gObj,lifetime));
}
