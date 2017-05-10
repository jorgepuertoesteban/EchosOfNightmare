#include "Trail.h"
#include "GameObject.h"


Trail::Trail(Vec2 tam,Vec2 pos, float rotation):m_lifetime(1000), m_dead(false){
	m_rect = sf::RectangleShape(sf::Vector2f(tam.x, tam.y));
	m_rect.setOrigin(m_rect.getSize().x / 2.f, m_rect.getSize().y / 2.f);
	m_rect.setPosition(sf::Vector2f(pos.x,pos.y));
	m_rect.setRotation(rotation*180/3.14);
	m_clockLife.restart();
	m_clockVanish.restart();
}
Trail::~Trail() {
}
void Trail::Update() {
	if (!m_dead && m_clockLife.getElapsedTime().asMilliseconds() >= m_lifetime) {
		m_dead = true;
	}
	sf::Color color = m_rect.getFillColor();
	if(color.a-5 > 0)
		color.a = color.a - 5;
	m_rect.setFillColor(sf::Color(255,255,255, color.a));
}
bool Trail::GetDead() {
	return m_dead;
}
void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_rect, states);
}
