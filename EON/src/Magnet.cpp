#include "Magnet.h"
#include "Map.h"
#include "GameObject.h"

Magnet::Magnet(GameObject *gObj, Map* map) : m_map(map) {
	m_gObj.Reset(gObj);
	m_clockWaves.restart();
}
Magnet::~Magnet(){
	
}
int  Magnet::GetId() {
	return m_gObj.Get()->GetId();
}
Vec2 Magnet::GetPosition() {
	return m_gObj.Get()->GetPosition();
}
void Magnet::Update() {
	if (m_clockWaves.getElapsedTime().asMilliseconds() > 200) {
		GenerateSound();
		m_clockWaves.restart();
	}
}
void Magnet::GenerateSound() {
	auto plus = rand() % 10;
	auto cant = 20;
	for (unsigned int i = 0; i < cant; i++) {
		float angle = ((i / (float)cant) * 360) + plus;
		Vec2 dir(sinf(angle*3.14f / 180.f), cosf(angle*3.14f / 180.f));

		float velX = rand() % 40 / 10 + 3.5f;
		if (rand() % 2 == 1) velX *= -1;

		float velY = rand() % 40 / 10 + 3.5f;
		if (rand() % 2 == 1) velY *= -1;

		m_map->CreateSoundWave(m_gObj.Get()->GetPosition() + (dir * 59), Vec2(velX, velY), Vec2(3, 3), 10, 230, 0, 230);
	}
}
