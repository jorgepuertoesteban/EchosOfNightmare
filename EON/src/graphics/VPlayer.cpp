#include "VPlayer.h"

VPlayer::VPlayer():m_visible(true), m_setedPos(false), m_actNumText(0), m_stop(true){
	char* path = "Media/step.png";
	m_texture[0].loadFromFile(path, sf::IntRect(0, 0, 626, 626));
	m_texture[1].loadFromFile(path, sf::IntRect(626, 0, 626, 626));
	m_texture[2].loadFromFile(path, sf::IntRect(1252, 0, 626, 626));
	m_texture[0].setSmooth(true);
	m_texture[1].setSmooth(true);
	m_texture[2].setSmooth(true);
	m_actualTxt = &m_texture[0];
}
VPlayer::~VPlayer(){
}
void VPlayer::Initialize(Vec2 size) {
	m_size = size;
	sf::Sprite sprite;
	sf::Vector2f scale(size.x / m_actualTxt->getSize().x, size.y / m_actualTxt->getSize().y);
	sprite.setOrigin(m_actualTxt->getSize().x / 2.f, m_actualTxt->getSize().y / 2.f);
	sprite.setScale(scale);
	sprite.setTexture(*m_actualTxt);
	m_sprites.Add(new step(sprite));
}
bool VPlayer::GetVisible() {
	return 	m_visible;
}
void   VPlayer::SetPosition(Vec2 pos){
	bool addSprite = false;
	if (!m_setedPos) {
		auto it = m_sprites.GetBegin();
		(*it)->sprite.setPosition(sf::Vector2f(pos.x, pos.y));
		m_actPos = pos;
		m_setedPos = true;
	}
	else{
		if (pos.x != m_actPos.x || pos.y != m_actPos.y) {
			//Me he movido
			m_actPos = pos;
			if (!m_move) {
				m_clockMove.restart();
				m_stop = false;
				m_move = true;
			}
			else if (m_clockMove.getElapsedTime().asMilliseconds() > 400) {
				m_actNumText = ((m_actNumText) % 2) +1;
				m_actualTxt = &m_texture[m_actNumText];
				addSprite = true;
				m_clockMove.restart();
			}
		}
		else {
			//No me he movido
			if (!m_stop) {
				m_clockStop.restart();
				m_stop = true;
				m_move = false;
			}
			else if (m_clockStop.getElapsedTime().asMilliseconds() > 300) {
				m_actualTxt = &m_texture[0];
				m_actNumText = 0;
				addSprite = true;
				m_clockStop.restart();
			}
		}
	}
	if (addSprite) {
		sf::Sprite sprite;
		sf::Vector2f scale(m_size.x / m_actualTxt->getSize().x, m_size.y / m_actualTxt->getSize().y);
		sprite.setOrigin(m_actualTxt->getSize().x / 2.f, m_actualTxt->getSize().y / 2.f);
		sprite.setScale(scale);
		sprite.setTexture(*m_actualTxt);
		sprite.setPosition(sf::Vector2f(pos.x, pos.y));
		sprite.setRotation(m_angle);
		m_sprites.Add(new step(sprite));
	}
	auto it = m_sprites.GetBegin();
	while (it != m_sprites.GetEnd()) {
		auto dead = (*it)->Update();
		if (dead) {
			int index = std::distance(m_sprites.GetBegin(), it);
			it = m_sprites.Remove(index);
		}
		else {
			it++;
		}
	}
}
void   VPlayer::SetRotation(float angle) {
	m_angle = angle;
}
void   VPlayer::SetVisible(bool aux) {
	m_visible = aux;
}
void  VPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto it = m_sprites.GetBegin(); it != m_sprites.GetEnd(); it++) {
		target.draw((*it)->sprite, states);
	}
}
