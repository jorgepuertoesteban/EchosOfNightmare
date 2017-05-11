#include "VSoundWave.h"

VSoundWave::VSoundWave(){
}
VSoundWave::~VSoundWave(){
}
void VSoundWave::Initialize(Vec2 tam) {

	m_rect = sf::RectangleShape(sf::Vector2f(tam.x, tam.y));
	m_rect.setOrigin(tam.x / 2.f, tam.y / 2.f);

}
bool VSoundWave::GetVisible() {
	return 	m_visible;
}
void   VSoundWave::SetPosition(Vec2 pos){
	m_rect.setPosition(sf::Vector2f(pos.x, pos.y));
}
void   VSoundWave::SetRotation(float angle){
	m_rect.setRotation(angle);
}
void   VSoundWave::SetVisible(bool aux) {
	m_visible = aux;
}
void  VSoundWave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_rect, states);
}
