#include "VPlayer.h"

VPlayer::VPlayer():m_visible(true){
}
VPlayer::~VPlayer(){
}
void VPlayer::Initialize(Vec2 tam) {
	m_texture.loadFromFile("Media/player.png");
	sf::Vector2f scale(tam.x / m_texture.getSize().x, tam.y / m_texture.getSize().y);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2.f, m_texture.getSize().y / 2.f);
	m_sprite.setScale(scale);
}
bool VPlayer::GetVisible() {
	return 	m_visible;
}
void   VPlayer::SetPosition(Vec2 pos){
	m_sprite.setPosition(sf::Vector2f(pos.x,pos.y));
}
void   VPlayer::SetRotation(float angle) {
	m_sprite.setRotation(angle);
}
void   VPlayer::SetVisible(bool aux) {
	m_visible = aux;
}
void  VPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}
