#include "Rock.h"
#include "Map.h"
#include "GameObject.h"


Rock::Rock(GameObject *gameobj, Map* map):m_dead(false), m_colisioned(false),m_map(map), m_sound(false){
	m_gObj.Reset(gameobj);
	m_clockTrail.restart();
	Vec2 origin = m_gObj.Get()->GetPosition();
	m_trail = sf::VertexArray(sf::TrianglesStrip, 4);
	m_trail[0].position = sf::Vector2f(m_gObj.Get()->GetVertexPosition(0).x * 64.f , m_gObj.Get()->GetVertexPosition(0).y * 64.f);
	m_trail[1].position = sf::Vector2f(m_gObj.Get()->GetVertexPosition(3).x * 64.f , m_gObj.Get()->GetVertexPosition(3).y * 64.f);
	m_trail[2].position = sf::Vector2f(m_gObj.Get()->GetVertexPosition(0).x * 64.f , m_gObj.Get()->GetVertexPosition(0).y * 64.f);
	m_trail[3].position = sf::Vector2f(m_gObj.Get()->GetVertexPosition(3).x * 64.f , m_gObj.Get()->GetVertexPosition(3).y * 64.f);
	m_trail[0].color = sf::Color(255, 255, 255, 150);
	m_trail[1].color = sf::Color(255, 255, 255, 150);
	m_trail[2].color = sf::Color(255, 255, 255, 0);
	m_trail[3].color = sf::Color(255, 255, 255, 0);
}
Rock::~Rock() {
}
void Rock::Update() {
	if (!m_colisioned && m_clockTrail.getElapsedTime().asMilliseconds() >= 20) {
		float angle = atan(m_gObj.Get()->GetLinearVelocity().y / m_gObj.Get()->GetLinearVelocity().x);
		m_gObj.Get()->SetRotation(angle);
		int a, z;
		if (m_gObj.Get()->GetLinearVelocity().x > 0)
			a = 0, z = 3;
		else              
			a = 1, z = 2;
		m_trail[0].position = sf::Vector2f(m_gObj.Get()->GetVertexPosition(a).x * 64.f, m_gObj.Get()->GetVertexPosition(a).y * 64.f);
		m_trail[1].position = sf::Vector2f(m_gObj.Get()->GetVertexPosition(z).x * 64.f, m_gObj.Get()->GetVertexPosition(z).y * 64.f);
		m_clockTrail.restart();
	}
	if (m_colisioned) {
		if (!m_sound) {
			m_sound = true;
			GenerateSound();
		}
		if (m_trail[0].color.a >= 10) {
			sf::Color color = m_trail[0].color;
			int alpha = color.a;
			color.a = alpha - 10;
			m_trail[0].color = color;
			m_trail[1].color = color;
		}
		else {

			m_dead = true;
			return;
		}
	}
}
void Rock::GenerateSound() {
	auto plus = rand() % 45;
	for (unsigned int i = 0; i < 20; i++) {
		float angle = ((i / (float)20) * 360) + plus;
		m_map->CreateSoundWave(m_gObj.Get()->GetPosition(), Vec2(sinf(angle*3.14f / 180.f), cosf(angle*3.14f / 180.f)) * 5, Vec2(8, 8), 20);
	}
}
void Rock::Colision(){
	m_colisioned = true;
}
bool Rock::GetDead() {
	return m_dead;
}
int  Rock::GetId() {
	return m_gObj.Get()->GetId();
}
void Rock::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_trail, states);
}
