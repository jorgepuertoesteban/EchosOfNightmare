#include "SoundWave.h"
#include "GameObject.h"
#include "Trail.h"


SoundWave::SoundWave(GameObject *gameobj,int lifetime)
	:m_lifetime(lifetime*50+1000), m_dead(false), m_TrailFree(false) {
	m_gObj.Reset(gameobj);
	m_clockLife.restart();
	m_clockTrail.restart();
	m_points.insert(m_points.begin(), m_gObj.Get()->GetVertexPosition(0));
	m_points.insert(m_points.begin(), m_gObj.Get()->GetVertexPosition(3));
}
SoundWave::~SoundWave() {
}
void SoundWave::Update() {
	if (m_clockTrail.getElapsedTime().asMilliseconds() >= 20) {
		m_gObj.Get()->SetRotation(atan(m_gObj.Get()->GetLinearVelocity().y / m_gObj.Get()->GetLinearVelocity().x));
		m_points.insert(m_points.begin(), m_gObj.Get()->GetVertexPosition(0));
		m_points.insert(m_points.begin(), m_gObj.Get()->GetVertexPosition(3));
		if (m_points.size() > m_lifetime / 40) {
			m_points.pop_back();
			m_points.pop_back();
		}
		if (m_TrailFree) {
			if (m_points.size() > 4) {
				m_points.pop_back();
				m_points.pop_back();
				m_points.pop_back();
			}
			else if (!m_dead) {
				m_dead = true;
			}
		}
		m_clockTrail.restart();
	}
	if (!m_TrailFree && (unsigned int)m_clockLife.getElapsedTime().asMilliseconds() >= m_lifetime) {
		m_TrailFree = true;
	}
	m_trail = sf::VertexArray(sf::TrianglesStrip, m_points.size());
	auto cont = 0;
	unsigned int alpha = m_lifetime/10;
	if (alpha > 255) alpha = 255;
	unsigned int downgrade = (alpha / m_points.size());
	for (auto it = m_points.begin(); it != m_points.end(); it++) {
		float x = it->x * 64,
			y = it->y * 64;
		m_trail[cont].position = sf::Vector2f(x , y);
		m_trail[cont].color = sf::Color(200, 200, 200, alpha);
		if(alpha > alpha - downgrade)alpha -= downgrade;
		cont++;
	}
}
bool SoundWave::GetDead() {
	return m_dead;
}
void SoundWave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_trail, states);
}
