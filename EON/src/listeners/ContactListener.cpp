#include "ContactListener.h"
#include "SoundWave.h"
#include "Enemy.h"
#include "Rock.h"
#include "Player.h"
#include "Map.h"

ContactListener::ContactListener(Map* map):m_map(map){
}
void ContactListener::BeginContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Method * it = beginContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Method::p)();
            break;
        }
        it++;
    }
}
void ContactListener::EndContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Method * it = endContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Method::p)();
            break;
        }
        it++;
    }
}


void ContactListener::Win() {
	m_map->Life();
}
void ContactListener::RockColision() {
	GetRock()->Colision();
}
void ContactListener::PlayerWaterBegin() {
	m_map->GetPlayer()->SetInWater(true);
}
void ContactListener::PlayerWaterEnd() {
	m_map->GetPlayer()->SetInWater(false);
}

void ContactListener::KillPlayer(){
	m_map->Dead();
}
void ContactListener::SWaveDWallBegin() {
	GetSoundWave()->SetColor(102, 0, 0);
}
void ContactListener::SWaveGoalBegin() {
	GetSoundWave()->SetColor(60, 224, 6);
}
void ContactListener::SWaveWaterBegin() {
	GetSoundWave()->SetColor(4, 64, 124);
}
void ContactListener::SWaveResetColor() {
	GetSoundWave()->ResetColor();
}
void ContactListener::SWaveEnemy() {
	GetEnemy()->SetTarget(GetSoundWave()->GetOrigin());
}

SoundWave* ContactListener::GetSoundWave() {
	auto waves = m_map->GetSoundWaves();
	for (auto it = waves->GetBegin(); it != waves->GetEnd(); ++it) {
		if ((*it)->GetId() == (int)contact->GetFixtureA()->GetBody()->GetUserData()
			|| (*it)->GetId() == (int)contact->GetFixtureB()->GetBody()->GetUserData()) {
			return (*it);
		}
	}
	return nullptr;
}
Enemy* ContactListener::GetEnemy() {
	auto enemies = m_map->GetEnemies();
	for (auto it = enemies->GetBegin(); it != enemies->GetEnd(); ++it) {
		if ((*it)->GetId() == (int)contact->GetFixtureA()->GetBody()->GetUserData()
			|| (*it)->GetId() == (int)contact->GetFixtureB()->GetBody()->GetUserData()) {
			return (*it);
		}
	}
	return nullptr;
}

Rock* ContactListener::GetRock() {
	auto rocks = m_map->GetRocks();
	for (auto it = rocks->GetBegin(); it != rocks->GetEnd(); ++it) {
		if ((*it)->GetId() == (int)contact->GetFixtureA()->GetBody()->GetUserData()
			|| (*it)->GetId() == (int)contact->GetFixtureB()->GetBody()->GetUserData()) {
			return (*it);
		}
	}
	return nullptr;
}
