#include "VWall.h"

VWall::VWall():m_visible(true){
}
VWall::~VWall(){
}
void VWall::Initialize(Vec2 tam) {
	m_rect = sf::RectangleShape(sf::Vector2f(tam.x, tam.y));
	m_rect.setOrigin(m_rect.getSize().x / 2.f, m_rect.getSize().y / 2.f);
}
bool VWall::GetVisible() {
	return 	m_visible;
}
void   VWall::SetPosition(Vec2 pos){
	m_rect.setPosition(sf::Vector2f(pos.x,pos.y));
}
void   VWall::SetRotation(float angle) {
	m_rect.setRotation(angle);
}
void   VWall::SetVisible(bool aux) {
	m_visible = aux;
}
void  VWall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_rect, states);
}
