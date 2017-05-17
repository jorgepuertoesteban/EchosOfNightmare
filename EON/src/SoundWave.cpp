#include "SoundWave.h"
#include "GameObject.h"


SoundWave::SoundWave(GameObject *gameobj,int lifetime, int r, int g, int b)
	:m_lifetime(lifetime*50+100), m_dead(false), m_TrailFree(false), m_delete(false)
	, m_r(r), m_g(g), m_b(b), m_oR(r), m_oG(g), m_oB(b) {
	m_gObj.Reset(gameobj);
	m_clockLife.restart();
	m_clockTrail.restart();
	m_origin = m_gObj.Get()->GetPosition();
	m_points.insert(m_points.begin(), Point(m_gObj.Get()->GetVertexPosition(0) * 64));
	m_points.insert(m_points.begin(), Point(m_gObj.Get()->GetVertexPosition(3) * 64));
}
SoundWave::~SoundWave() {
}
void SoundWave::Update() {
	if (m_clockTrail.getElapsedTime().asMilliseconds() >= 20) {
		float angle = atan(m_gObj.Get()->GetLinearVelocity().y / m_gObj.Get()->GetLinearVelocity().x);
		m_gObj.Get()->SetRotation(angle);
		int a, z;
		if (m_gObj.Get()->GetLinearVelocity().x > 0)
			a = 0, z = 3;
		else              
			a = 1, z = 2;
		m_points.insert(m_points.begin(), Point(m_gObj.Get()->GetVertexPosition(a) * 64,m_r,m_g,m_b));
		m_points.insert(m_points.begin(), Point(m_gObj.Get()->GetVertexPosition(z) * 64,m_r,m_g,m_b ));
		if (m_points.size() > m_lifetime / 40 || m_points.size() > 100 ) {
			m_points.pop_back();
			m_points.pop_back();
		}
		if (m_TrailFree) {
			if (m_points.size() > 5) {
				m_points.pop_back();
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
	unsigned int alpha = m_lifetime/6;
	if (alpha > 255) alpha = 255;
	unsigned int downgrade = (alpha / m_points.size());

	
	for (auto it = m_points.begin(); it != m_points.end(); it++) {
		float x = (it->x),
			y = (it->y);
		m_trail[cont].position = sf::Vector2f(x , y);
		m_trail[cont].color = sf::Color(it->r, it->g, it->b, alpha);
		if(alpha > alpha - downgrade)alpha -= downgrade;
		cont++;
	}
	
}
bool SoundWave::GetDead() {
	return m_dead;
}
int  SoundWave::GetId() {
	return m_gObj.Get()->GetId();
}
Vec2 SoundWave::GetOrigin() {
	return m_origin;
}
void SoundWave::SetColor(int r, int g, int b) {
	m_r = r, m_g = g, m_b = b;
}
void SoundWave::ResetColor() {
	m_r = m_oR, m_g = m_oG, m_b = m_oB;
}
void SoundWave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_trail, states);
}
