#include "Player.h"
#include "GameObject.h"
#include "Map.h"
#include <math.h>
#include <iostream>


Player::Player(GameObject *gObj, Map *map)
	:m_gObj(gObj),m_map(map),m_dir(Vec2(0,0)), m_speed(3),m_sound(false){
}
Player::~Player() {
}
void Player::Update() {
	Move();	
}

void Player::Move() {
	CalcDir();
	CalcAngle();
	m_gObj->SetLinearVelocity(m_dir);
	m_gObj->SetRotation(m_angle);
}
void Player::CalcDir() {
	m_dir.x = 0;
	m_dir.y = 0;
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
}
void Player::CalcAngle() {
	m_angle = 0;
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
void Player::SetW(bool aux) {
	m_sDirection.W = aux;
	if (aux)
		m_sDirection.lastV = -1;
}
void Player::SetS(bool aux) {
	m_sDirection.S = aux;
	if (aux)
		m_sDirection.lastV = 1;
}
void Player::SetA(bool aux) {
	m_sDirection.A = aux;
	if (aux)
		m_sDirection.lastH = -1;
}
void Player::SetD(bool aux) {
	m_sDirection.D = aux;
	if (aux)
		m_sDirection.lastH = 1;
}
void Player::MakeSound(bool aux){
	if(!m_sound && aux){
		m_clockSound.restart();
		m_sound = true;

	}
	if(m_sound && !aux){
		m_sound = false;
		int numRays;
		sf::Int32 time = m_clockSound.getElapsedTime().asMilliseconds()/10;
		if (time > 2) {
			numRays = time;
			if (numRays > 50) {
				numRays = 50;
			}
			for (int i = 0; i < numRays; i++) {
				float angle = (i / (float)numRays) * 360;
				m_map->CreateSoundWave(m_gObj->GetPosition(), Vec2(sinf(angle*3.14f/180.f)*4, cosf(angle*3.14f / 180.f)*4), numRays);
			}
		}
	}
}