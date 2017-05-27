#include "physicbodies\PBEnemySoundWave.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Map.h"
#include <math.h>
#include <iostream>

Enemy::Enemy(GameObject *gObj, Map *map)
	:m_gObj(gObj),m_dir(Vec2(0,0)), m_speed(2), m_target(Vec2(0, 0)), m_map(map), m_stoped(true){
	m_clockSound.restart();
}
Enemy::~Enemy() {
}
void Enemy::Update() {
	Move();	
	if (m_clockSound.getElapsedTime().asMilliseconds() > 500) {
		GenerateSound(rand() % 10 + 6);
		m_clockSound.restart();
	}
}
void Enemy::Move() {
	if (!m_stoped) {
		if (ReachTarget()) {
			m_gObj->SetLinearVelocity(Vec2(0,0));
			m_stoped = true;
		}
	}
}
bool Enemy::ReachTarget() {
	float margin = 1;
	if (   m_gObj->GetPosition().x < m_target.x + margin && m_gObj->GetPosition().x > m_target.x - margin
 		&& m_gObj->GetPosition().y < m_target.y + margin && m_gObj->GetPosition().y > m_target.y - margin) {
		return true;
	}
	return false;
}
void Enemy::SetTarget(Vec2 target) {
	m_stoped = false;
	m_target = target;
	CalcDir();
	m_gObj->SetLinearVelocity(m_dir*m_speed);
}
void Enemy::CalcDir() {
	Vec2 dist =  m_target - m_gObj->GetPosition();
	m_dir.x = dist.x / (sqrt(pow(dist.x, 2) + pow(dist.y, 2)));
	m_dir.y = dist.y /(sqrt(pow(dist.x, 2) + pow(dist.y, 2)));
}

void Enemy::GenerateSound(unsigned int count) {
	auto plus = rand() % 45;
	for (unsigned int i = 0; i < count; i++) {
		float angle = ((i / (float)count) * 360) + plus ;
		m_map->CreateSoundWave(m_gObj->GetPosition(), Vec2(sinf(angle*3.14f / 180.f)/1.5f, cosf(angle*3.14f / 180.f)/ 1.5f),Vec2(5,5), 20,150,0,0, new PBEnemySoundWave);
	}
}
int Enemy::GetId() {
	return m_gObj->GetId();
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_gObj, states);
}