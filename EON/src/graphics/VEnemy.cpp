#include "VEnemy.h"

VEnemy::VEnemy():m_visible(true){
}
VEnemy::~VEnemy(){
}
void VEnemy::Initialize(Vec2 tam) {
	m_rect = sf::RectangleShape(sf::Vector2f(tam.x, tam.y));
	m_rect.setOrigin(m_rect.getSize().x / 2.f, m_rect.getSize().y / 2.f);
}
bool VEnemy::GetVisible() {
	return 	m_visible;
}
void   VEnemy::SetPosition(Vec2 pos){
	m_rect.setPosition(sf::Vector2f(pos.x,pos.y));
}
void   VEnemy::SetRotation(float angle) {
	m_rect.setRotation(angle);
}
void   VEnemy::SetVisible(bool aux) {
	m_visible = aux;
}
void  VEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if(m_visible)target.draw(m_rect, states);
}
