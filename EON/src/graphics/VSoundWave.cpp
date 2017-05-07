#include "VSoundWave.h"

VSoundWave::VSoundWave(){
}
VSoundWave::~VSoundWave(){
}
void VSoundWave::Initialize(Vec2 tam) {
	m_texture.loadFromFile("Media/icecube.jpg");
	sf::Vector2f scale(tam.x / m_texture.getSize().x, tam.y / m_texture.getSize().y);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2.f, m_texture.getSize().y / 2.f);
	m_sprite.setScale(scale);
}
bool VSoundWave::GetVisible() {
	return 	m_visible;
}
void   VSoundWave::SetPosition(Vec2 pos){
	m_sprite.setPosition(sf::Vector2f(pos.x,pos.y));
}
void   VSoundWave::SetRotation(float angle){
	m_sprite.setRotation(angle);
}
void   VSoundWave::SetVisible(bool aux) {
	m_visible = aux;
}
void  VSoundWave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}
