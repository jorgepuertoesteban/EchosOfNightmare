#include "VSoundWave.h"

VSoundWave::VSoundWave(){
}
VSoundWave::~VSoundWave(){
}
void VSoundWave::Initialize(Vec2 tam) {
	m_circle = sf::CircleShape(tam.x/1.75f);
	m_circle.setOrigin(tam.x / 2.f, tam.x / 2.f);
}
bool VSoundWave::GetVisible() {
	return 	m_visible;
}
void   VSoundWave::SetPosition(Vec2 pos){
	m_circle.setPosition(sf::Vector2f(pos.x,pos.y));
}
void   VSoundWave::SetRotation(float angle){
	m_sprite.setRotation(angle);
}
void   VSoundWave::SetVisible(bool aux) {
	m_visible = aux;
}
void  VSoundWave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_circle, states);
}
