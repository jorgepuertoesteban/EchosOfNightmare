#include "Player.h"
#include "GameObject.h"
#include "Map.h"
#include "EventListener.h"
#include <math.h>
#include <iostream>

Player::Player(GameObject *gObj, Map *map)
	:m_gObj(gObj),m_map(map),m_dir(Vec2(0,0)), m_speed(2),m_sound(false), m_events(nullptr), m_inWater(false),
	m_walking(false),m_angle(0),m_kissOfDead(false), m_kissOfLife(false), m_finish(false),m_rock(false), m_stepCount(0), m_timeStep(0){
	m_bufferStep[0].loadFromFile("Media/Sounds/Step1.wav");
	m_bufferStep[1].loadFromFile("Media/Sounds/Step2.wav");
	m_bufferStep[2].loadFromFile("Media/Sounds/Step3.wav");
	m_bufferStep[3].loadFromFile("Media/Sounds/WaterStep.wav");
	m_bufferClap[0].loadFromFile("Media/Sounds/Clap3.wav");
	m_bufferClap[1].loadFromFile("Media/Sounds/Clap2.wav");
	m_bufferClap[2].loadFromFile("Media/Sounds/Clap1.wav");
	m_bufferWater[0].loadFromFile("Media/Sounds/WaterEntrance.wav");
	m_bufferWater[1].loadFromFile("Media/Sounds/WaterExit.wav");
	m_bufferDeath.loadFromFile("Media/Sounds/Death.wav");
	m_bufferLife.loadFromFile("Media/Sounds/Door.wav");
	m_soundDeath.setBuffer(m_bufferDeath);
	m_soundLife.setBuffer(m_bufferLife);
}
Player::~Player() {
}
void Player::Update() {
	if (m_clockEvents.getElapsedTime().asMilliseconds() > 50) {
		CheckEvents();
		Move();
		m_clockEvents.restart();
	}
	if (!m_finish) {
		if (Step()) {
			if (!m_sDirection.Shift) {
				m_soundStep.setVolume(100);
			}
			else {
				m_soundStep.setVolume(25);
			}
			if(m_inWater)
				m_soundStep.setBuffer(m_bufferStep[4]);
			else
				m_soundStep.setBuffer(m_bufferStep[m_stepCount]);
			if(!m_sDirection.Shift || m_inWater)
				m_soundStep.play();
			m_stepCount = (m_stepCount+1) % 3;
			if (m_inWater) {
				GenerateSound(25, 25, 4);
			}
			else if (!m_sDirection.Shift) {
				GenerateSound(25, 15, 4);
			}
			else{
				GenerateSound(10, 15, 1);
			}
		}
		if (m_kissOfDead || m_kissOfLife) {
			unsigned int count = 50;
			for (unsigned int i = 0; i < count; i++) {
				float angle = ((i / (float)count) * 360);
				int r, g, b;
				if (m_kissOfDead) {
					m_soundDeath.play();
					r = 102, g = 0, b = 0;
				}
				if (m_kissOfLife) {
					m_soundLife.play();
					r = 255, g = 255, b = 255;
				}
				m_map->CreateSoundWave(m_gObj->GetPosition(), Vec2(sinf(angle*3.14f / 180.f) * 4, cosf(angle*3.14f / 180.f) * 4), Vec2(16, 16), count, r, g, b);
			}
			m_finish = true;
		}
	}
	
}
void Player::KissOfDead() {
	m_kissOfDead = true;
}
void Player::KissOfLife() {
	m_kissOfLife = true;
}
void Player::ApplyForce(Vec2 force) {
	if(!m_kissOfDead)m_gObj->ApplyForce(force);
}

void Player::Move() {
	if (!m_finish) {
		CalcDir();
		CalcAngle();
		m_gObj->SetLinearVelocity(m_dir);
		m_gObj->SetRotation(m_angle);
	}
	else {
		m_gObj->SetLinearVelocity(Vec2(0,0));
	}
	sf::Listener::setPosition(m_gObj->GetPosition().x, m_gObj->GetPosition().y, 0);
}
void Player::CalcDir() {
	m_dir.x = 0;
	m_dir.y = 0;
	if (m_sound)
		return;
	if (m_sDirection.W && m_sDirection.S)
		m_dir.y = (float)m_sDirection.lastV;
	else{
		if (m_sDirection.W)
			m_dir.y = -1;
		if(m_sDirection.S)
			m_dir.y = 1;
	}
	if (m_sDirection.A && m_sDirection.D)
		m_dir.x = (float)m_sDirection.lastH;
	else {
		if (m_sDirection.A)
			m_dir.x = -1;
		if (m_sDirection.D)
			m_dir.x = 1;
	}
	if (m_dir.x != 0 && m_dir.y != 0) {
		m_dir = m_dir * m_speed;
		m_dir.x = m_dir.x / 1.25f;
		m_dir.y = m_dir.y / 1.25f;

	}
	else
		m_dir = m_dir * m_speed;

	if (m_inWater || m_sDirection.Shift) {
		m_dir = m_dir / 2;
	}
}
void Player::CalcAngle() {
	if (m_dir.x != 0 || m_dir.y != 0) {
		m_angle = atan(m_dir.y / m_dir.x);
		if (m_dir.x < 0) {
			if (m_dir.y > 0)
				m_angle = (90 * 3.1415f/ 180.0f) - m_angle;
			else
				m_angle += 180 * 3.1415f/ 180.0f;
		}
	}
}
void Player::CheckEvents() {
	m_sDirection.Shift = (m_events->IsKeyDown(sf::Keyboard::LShift) || m_events->IsKeyDown(sf::Keyboard::RShift));
	m_sDirection.W     = m_events->IsKeyDown(sf::Keyboard::W);
	m_sDirection.A     = m_events->IsKeyDown(sf::Keyboard::A);
	m_sDirection.S     = m_events->IsKeyDown(sf::Keyboard::S);
	m_sDirection.D     = m_events->IsKeyDown(sf::Keyboard::D);
	MakeSound(m_events->IsKeyDown(sf::Keyboard::Space));
	ThrowRock(m_events->IsKeyDown(sf::Keyboard::Return));
	if (m_sDirection.W) m_sDirection.lastV = -1;
	if (m_sDirection.S) m_sDirection.lastV = 1;
	if (m_sDirection.A) m_sDirection.lastH = -1;
	if (m_sDirection.D) m_sDirection.lastH = 1;
}
Vec2 Player::GetPosition() {
	return m_gObj->GetPosition();
}
bool Player::Step() {
	if (m_dir.x || m_dir.y) {
		if (!m_walking) {
			m_walking = true;
			m_clockStep.restart();
		}
		if ( ( !m_sDirection.Shift && m_clockStep.getElapsedTime().asMilliseconds() + m_timeStep> 500)
			||((m_sDirection.Shift || m_inWater) && m_clockStep.getElapsedTime().asMilliseconds() + m_timeStep> 600)) {
			m_clockStep.restart();
			m_timeStep = 0;
			return true;
		}

	}
	else {
		if (m_walking) {
			m_timeStep += m_clockStep.getElapsedTime().asMilliseconds();
			m_walking = false;
		}
	}
	return false;
}
void Player::MakeSound(bool key_pressed){
	if(!m_finish && !m_sound && key_pressed){
		m_clockSound.restart();
		m_sound = true;
	}
	if(!m_finish && m_sound && !key_pressed){
		m_sound = false;
		int cant;
		int lifetime;
		sf::Int32 time = m_clockSound.getElapsedTime().asMilliseconds();
		if (time > 2500)
			time = 2500;
		if (time < 433) {
			m_soundClap.setBuffer(m_bufferClap[0]);
			if (time < 400) {
				m_soundClap.setVolume(10);
				cant = 12;
				lifetime = 15;
			}
			else {
				m_soundClap.setVolume(30);
				cant = 24;
				lifetime = 28;
			}
		}
		else if (time < 866) {
			m_soundClap.setBuffer(m_bufferClap[1]);
			if(time < 1200) {
				m_soundClap.setVolume(50);
				cant = 36;
				lifetime = 39;
			}
			else {
				m_soundClap.setVolume(70);
				cant = 48;
				lifetime = 62;
			}
		}
		else {
			m_soundClap.setBuffer(m_bufferClap[2]);
			if (time < 2000) {
				m_soundClap.setVolume(90);
				cant = 80;
				lifetime = 100;
			}
			else {
				m_soundClap.setVolume(100);
				cant = 100;
				lifetime = 120;
			}
		}
		m_soundClap.play();
		GenerateSound(cant, lifetime, 6);

		/*
		int numRays;
		sf::Int32 time = m_clockSound.getElapsedTime().asMilliseconds()/10;
		if (time > 2) {
			numRays = time;
			if (numRays < 35) {
				m_soundClap.setVolume(10);
				m_bufferClap.loadFromFile("Media/Sounds/Clap3.wav");
			}
			else if (numRays < 50) {
				m_soundClap.setVolume(30);
				m_bufferClap.loadFromFile("Media/Sounds/Clap2.wav");
			}
			else {
				m_soundClap.setVolume(60);
				m_bufferClap.loadFromFile("Media/Sounds/Clap1.wav");
				numRays = 70;
			}
			m_soundClap.play();
			GenerateSound(numRays, numRays, 6);
		}*/
	}
}
void Player::ThrowRock(bool rock) {
	if (!m_rock && rock) {
		m_map->CreateRock(m_gObj->GetPosition(), Vec2(cosf(m_angle), sinf(m_angle))*20);
		m_rock = true;
	}
	else if (m_rock && !rock) {
		m_rock = false;
	}
}
void Player::GenerateSound(unsigned int count, unsigned int lifetime , float velocity) {
	auto plus = rand() % 45;
	for (unsigned int i = 0; i < count; i++) {
		float angle = ((i / (float)count) * 360) + plus ;
		m_map->CreateSoundWave(m_gObj->GetPosition(), Vec2(sinf(angle*3.14f / 180.f) * velocity, cosf(angle*3.14f / 180.f) * velocity),Vec2(5, 5), lifetime);
	}
}
void Player::SetEventListener(EventListener *events) {
	m_events = events;
}
void Player::SetInWater(bool aux) {
	if(aux)
		m_soundWater.setBuffer(m_bufferWater[0]);
	else
		m_soundWater.setBuffer(m_bufferWater[1]);
	m_soundWater.play();
	m_inWater = aux;
}
