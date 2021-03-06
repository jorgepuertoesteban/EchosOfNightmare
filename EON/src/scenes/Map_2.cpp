#include "Map_2.h"
#include "GameObject.h"
#include "PhysicWorld.h"
#include "VSoundWave.h"
#include "Player.h"
#include "VPlayer.h"
#include "VEnemy.h"
#include "Rock.h"
#include "Enemy.h"
#include "VBox.h"
#include "VWall.h"
#include "VDeadWall.h"
#include "physicbodies\PBRock.h"
#include "physicbodies\PBSoundWave.h"
#include "physicbodies\PBPlayer.h"
#include "physicbodies\PBMagnet.h"
#include "physicbodies\PBEnemy.h"
#include "physicbodies\PBWall.h"
#include "physicbodies\PBWater.h"
#include "physicbodies\PBGoal.h"
#include "physicbodies\PBDeadWall.h"
#include "physicbodies\PBMechanism.h"
#include "ContactListener.h"
#include "XMLReader.h"
#include "EventListener.h"
#include "Mechanism.h"
#include "SoundWave.h"
#include "Door.h"
#include "Magnet.h"
#include <iostream>

Map_2::Map_2(sf::View* view):m_end(false), m_start(false), m_finished(false), m_learn(true),m_success(false) {
	m_pPhysiworld.Reset(new PhysicWorld);
	m_physiworld = m_pPhysiworld.Get();
	m_pContactListener.Reset(new ContactListener(this)); 
	m_physiworld->SetContactListener(m_pContactListener.Get());
	ReadXML();
	m_view = view;
	m_clockStart.restart();
	m_font.loadFromFile("Media/Fonts/OpenSans-Regular.ttf");

	m_text.setPosition(sf::Vector2f(0,-2000));
	m_text.setCharacterSize(100);
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setString(m_mapName);

	m_bufferIntro.loadFromFile("Media/Sounds/Intro.wav");
	m_music.openFromFile("Media/Sounds/Ambient.wav");
	m_soundIntro.setBuffer(m_bufferIntro);
	m_music.setVolume(20);
	m_music.setLoop(true);
	m_soundIntro.play();
}
Map_2::~Map_2(){
	m_enemies.Clear();
	m_soundWaves.Clear();
	m_gameObjects.Clear();
	m_pGoal.Reset(nullptr);
	m_pGoal.Reset(nullptr);
	m_player.Reset(nullptr);
}
void Map_2::Inicialice(EventListener* listener) {
	m_listener = listener;
	m_player.Get()->SetEventListener(listener);
}
bool Map_2::Start() {
	if (!m_start) {
		if (m_clockStart.getElapsedTime().asMilliseconds() > 3000) {
			sf::Vector2f pos(m_player.Get()->GetPosition().x - (m_text.getLocalBounds().width / 2), m_player.Get()->GetPosition().y - m_text.getLocalBounds().height - 50);
			m_text.setPosition(pos);
			m_text.setCharacterSize(20);
			m_text.setFillColor(sf::Color::White);
			m_text.setString(m_tutoStrings);
			m_music.play();
			m_start = true;
		}
		return false;
	}
	return true;
}
void Map_2::Update(){
	m_physiworld->Update();
	CheckEvents();
	UpdateEnemies();
	UpdateGameObjects();
	UpdateSoundWaves();
	UpdateDoors();
	UpdateRocks();
	UpdateMagnets();
	m_view->setCenter(m_player.Get()->GetPosition().x, m_player.Get()->GetPosition().y);
	if (!Start()) {
		UpdateIntro();
		return;
	}
	else {
		UpdateText();
	}
	m_player.Get()->Update();
	CheckFinish();
}
void Map_2::UpdateIntro() {
	int alpha = m_text.getFillColor().a;
	if(alpha>=3)alpha -= 3;
	else alpha = 0;
	sf::Vector2f pos(m_player.Get()->GetPosition().x - (m_text.getLocalBounds().width / 2), m_player.Get()->GetPosition().y - m_text.getLocalBounds().height - 50);
	m_text.setPosition(pos);
	m_text.setFillColor(sf::Color(255,255,255,alpha));
}
void Map_2::UpdateText() {
	if (m_learn) {
		int alpha = m_text.getFillColor().a;
		if (alpha > 150)alpha--;
		else if (alpha >= 3)alpha -= 3;
		sf::Vector2f pos(m_player.Get()->GetPosition().x - (m_text.getLocalBounds().width / 2), m_player.Get()->GetPosition().y - m_text.getLocalBounds().height - 50);
		m_text.setPosition(pos);
		m_text.setFillColor(sf::Color(255, 255, 255, alpha));
		if (alpha == 0) {
			m_learn = false;
		}
	}
}
void Map_2::Render(sf::RenderWindow *window){
	window->draw(m_text);
	if (!Start()) {
		return;
	}
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
	for (auto it = m_rocks.GetBegin(); it != m_rocks.GetEnd(); it++) {
		window->draw(*(*it));
	}
}
void Map_2::CheckEvents() {
}
bool Map_2::Success() {
	return m_success;
}
void Map_2::ReadXML() {
	XMLReader reader;
	reader.Inicialize(this, m_path);
}
void Map_2::Life() {
	m_success = true;
	m_player.Get()->KissOfLife();
	StartFinish();
}
void Map_2::Dead() {
	m_player.Get()->KissOfDead();
	StartFinish();
}
void Map_2::StartFinish() {
	m_clockEnd.restart();
	m_finished = true;
}
GameObject* Map_2::CreateGameObject(PhysicBody* pB, VisualBody* vB, Vec2 pos, Vec2 size) {
	m_physiworld->CreateBody(pB,  pos,  size);
	vB->Initialize(size);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pB, vB);
	m_gameObjects.Add(gObj);
	return gObj;
}
void Map_2::CreateEnemy(Vec2 pos) {
	GameObject *goEnemy = CreateGameObject(new PBEnemy, new VEnemy, pos, Vec2(35,35));
	goEnemy->SetVisible(false);
	m_enemies.Add(new Enemy(goEnemy, this));
}
void Map_2::CreatePlayer(Vec2 pos) {
	GameObject *goPlayer = CreateGameObject(new PBPlayer, new VPlayer, pos, Vec2(35, 35));
	m_player.Reset(new Player(goPlayer, this));
	sf::Vector2f posText(m_player.Get()->GetPosition().x - (m_text.getLocalBounds().width / 2), m_player.Get()->GetPosition().y - m_text.getLocalBounds().height);
}
void Map_2::CreateRock(Vec2 pos, Vec2 dir) {
	PBRock      *pR = new PBRock;
	VSoundWave  *vB = new VSoundWave;
	Vec2 size(5, 5);
	m_physiworld->CreateBody(pR, pos, size);
	vB->Initialize(size);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pR, vB);
	gObj->SetLinearVelocity(dir);
	m_rocks.Add(new Rock(gObj,this));
}
void Map_2::CreateMagnet(Vec2 pos) {
	PBMagnet *pmagnet = new PBMagnet;
	VWall  *vwall = new VWall;
	Vec2 size{ 100,100 };
	m_physiworld->CreateBody(pmagnet, pos- size/2, size);
	vwall->Initialize(size);
	vwall->SetPosition(Vec2(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f)));
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pmagnet, vwall);
	gObj->SetVisible(false);
	m_magnets.Add(new Magnet(gObj, this));
}
void Map_2::CreateMechanism(Vec2 pos, Vec2 size, int rotation, int door) {
	PBMechanism *pmechanism = new PBMechanism;
	VWall  *vwall = new VWall;
	m_physiworld->CreateBody(pmechanism, pos, size);
	vwall->Initialize(size);
	vwall->SetPosition(Vec2(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f)));
	vwall->SetRotation((float)rotation);
	float radians = rotation * 3.141592653589793f / 180.f;
	pmechanism->SetRotationFromCorner(radians);
	GameObject* gObj = new GameObject();
	gObj->Inicialize(pmechanism, vwall);
	gObj->SetVisible(false);
	m_mechanisms.Add(new Mechanism(gObj, door));
}
void Map_2::CreateDoor(Vec2 pos, Vec2 size, int rotation, int door) {
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
	m_doors.Add(new Door(gObj, this, door));
}
void Map_2::CreateGoal(Vec2 pos, Vec2 size, int rotation) {
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
void Map_2::CreateWater(Vec2 pos, Vec2 size, int rotation) {
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
void Map_2::CreateWall(Vec2 pos, Vec2 size, int rotation) {
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
void Map_2::CreateDeadWall(Vec2 pos, Vec2 size, int rotation) {
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
void Map_2::CreateSoundWave(Vec2 pos, Vec2 dir, Vec2 size, int lifetime, int r, int g, int b, PhysicBody *pB) {
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
Player* Map_2::GetPlayer() {
	return m_player.Get();
}

PVector<SoundWave>* Map_2::GetSoundWaves() {
	return &m_soundWaves;
}
PVector<Mechanism>* Map_2::GetMechanisms() {
	return &m_mechanisms;
}
PVector<Enemy>* Map_2::GetEnemies() {
	return &m_enemies;
}
PVector<Door>* Map_2::GetDoors() {
	return &m_doors;
}
PVector<Rock>* Map_2::GetRocks() {
	return &m_rocks;
}
PVector<Magnet>* Map_2::GetMagnets() {
	return &m_magnets;
}
bool Map_2::End() {
	return m_end;
}
void Map_2::EndMap() {
	m_end = true;
}
void Map_2::CheckFinish() {
	if (m_finished && !m_end && m_clockEnd.getElapsedTime().asMilliseconds() > 4000) {
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
		EndMap();
	}
}
void Map_2::UpdateGameObjects() {
	for (auto itGO = m_gameObjects.GetBegin(); itGO != m_gameObjects.GetEnd(); itGO++) {
		(*itGO)->Update();
	}
}
void Map_2::UpdateSoundWaves() {
	auto itSW = m_soundWaves.GetBegin();
	while (itSW != m_soundWaves.GetEnd()) {
		(*itSW)->Update();
		if ((*itSW)->GetDead()) {
			int index = std::distance(m_soundWaves.GetBegin(), itSW);
			itSW = m_soundWaves.Remove(index);
		}
		else {

			Vec2 itWc = (*itSW)->GetPosition() / 64.f;
			float itM{ 0.1f };

			auto itMg = m_magnets.GetBegin();
			while (itMg != m_magnets.GetEnd()) {

				auto cont = 0;

				Vec2 mWc = (*itMg)->GetPosition() / 64.f;
				float  mM{ 1.0f };


				b2Vec2 delta(mWc.x - itWc.x, mWc.y - itWc.y);
				float r = delta.Length() / 10;
				float force = 9.8f * mM * itM / (r*r);

				delta.Normalize();
				Vec2 delta2{ force *delta.x, force *delta.y };
				(*itSW)->ApplyForce(delta2);

				itMg++;
			}

			itSW++;
		}

	}
}
void Map_2::UpdateEnemies() {
	for (auto it = m_enemies.GetBegin(); it != m_enemies.GetEnd(); it++) {
		(*it)->Update();
	}
}
void Map_2::UpdateRocks() {
	for (auto it = m_rocks.GetBegin(); it != m_rocks.GetEnd(); it++) {
		(*it)->Update();
	}
}
void Map_2::UpdateDoors() {
	auto it = m_doors.GetBegin();
	while (it != m_doors.GetEnd()) {
		(*it)->Update();
		if ((*it)->GetPressed()) {
			int index = std::distance(m_doors.GetBegin(), it);
			it = m_doors.Remove(index);
		}
		else {
			it++;
		}
	}
}
void Map_2::UpdateMagnets() {
	auto it = m_magnets.GetBegin();
	while (it != m_magnets.GetEnd()) {
		(*it)->Update();
	}
}