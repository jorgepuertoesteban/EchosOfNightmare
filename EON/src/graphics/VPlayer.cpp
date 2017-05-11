#include "VPlayer.h"

VPlayer::VPlayer():m_visible(true), m_setedPos(false){
	char* path = "Media/player.png";
	m_texture[0].loadFromFile(path, sf::IntRect(0, 0, 626, 626));
	m_texture[1].loadFromFile(path, sf::IntRect(626, 0, 626, 626));
	m_texture[2].loadFromFile(path, sf::IntRect(626*2, 0, 626, 626));
	m_actualTxt = &m_texture[0];
}
VPlayer::~VPlayer(){
}
void VPlayer::Initialize(Vec2 tam) {
	sf::Vector2f scale(tam.x / m_actualTxt->getSize().x, tam.y / m_actualTxt->getSize().y);
	m_sprite.setOrigin(m_actualTxt->getSize().x / 2.f, m_actualTxt->getSize().y / 2.f);
	m_sprite.setScale(scale);
	m_sprite.setTexture(*m_actualTxt);
}
bool VPlayer::GetVisible() {
	return 	m_visible;
}
void   VPlayer::SetPosition(Vec2 pos){
	/*if (!m_setedPos) {
		m_sprite.setPosition(sf::Vector2f(pos.x, pos.y));
		m_actPos = pos;
		m_setedPos = true;
	}
	if (pos != m_actPos) {

	}
	else {

	}*/
	m_sprite.setPosition(sf::Vector2f(pos.x, pos.y));
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
