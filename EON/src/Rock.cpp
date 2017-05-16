#include "Rock.h"
#include "GameObject.h"


Rock::Rock(GameObject *gameobj):m_dead(false), m_colisioned(false){
	m_gObj.Reset(gameobj);
	m_clockTrail.restart();
	Vec2 origin = m_gObj.Get()->GetPosition();
	m_points[0] = m_points[1] = Point(m_gObj.Get()->GetVertexPosition(0));
	m_points[2] = m_points[3] = Point(m_gObj.Get()->GetVertexPosition(3),0,0,0);
	m_trail = sf::VertexArray(sf::TrianglesStrip, 4);
	m_trail[0].position = sf::Vector2f(origin.x*64.f , origin.y*64.f);
	m_trail[1].position = sf::Vector2f(origin.x*64.f , origin.y*64.f);
	m_trail[2].position = sf::Vector2f(origin.x*64.f , origin.y*64.f);
	m_trail[3].position = sf::Vector2f(origin.x*64.f , origin.y*64.f);
	m_trail[0].color = sf::Color(255,255,255,255);
	m_trail[1].color = sf::Color(255,255,255,255);
	m_trail[2].color = sf::Color(0,0,0,0);
	m_trail[3].color = sf::Color(0,0,0,0);
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
		m_points[0] = Point(m_gObj.Get()->GetVertexPosition(a));
		m_points[1] = Point(m_gObj.Get()->GetVertexPosition(z));
		m_clockTrail.restart();
	}
	if (m_colisioned && m_trail[0].color.a >= 4 ) {
		sf::Color color = m_trail[0].color;
		color.a = color.a-4;
		m_trail[0].color = color;
	}
	else if(m_trail[0].color.a <= 0){
		m_dead = true;
		return;
	}
	m_trail[0].position = sf::Vector2f(m_points[0].x*64.f , m_points[0].y*64.f);
	m_trail[1].position = sf::Vector2f(m_points[1].x*64.f , m_points[1].y*64.f);
	
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
