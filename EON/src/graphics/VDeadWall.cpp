#include "VDeadWall.h"

VDeadWall::VDeadWall():m_visible(true){
}
VDeadWall::~VDeadWall(){
}
void VDeadWall::Initialize(Vec2 tam) {
	m_rect = sf::RectangleShape(sf::Vector2f(tam.x, tam.y));
	m_rect.setOrigin(m_rect.getSize().x / 2.f, m_rect.getSize().y / 2.f);
}
bool VDeadWall::GetVisible() {
	return 	m_visible;
}
void   VDeadWall::SetPosition(Vec2 pos){
	m_rect.setPosition(sf::Vector2f(pos.x,pos.y));
}
void   VDeadWall::SetRotation(float angle) {
	m_rect.setRotation(angle);
}
void   VDeadWall::SetVisible(bool aux) {
	m_visible = aux;
}
void  VDeadWall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_rect, states);
}
