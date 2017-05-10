#include "SoundWave.h"
#include "GameObject.h"
#include "Trail.h"


SoundWave::SoundWave(GameObject *gameobj,int lifetime)
	:m_lifetime(lifetime), m_dead(false), m_TrailFree(false) {
	m_gObj.Reset(gameobj);
	m_clockLife.restart();
	m_clockTrail.restart();
}
SoundWave::~SoundWave() {
}
void SoundWave::Update() {
	if (!m_TrailFree && m_clockTrail.getElapsedTime().asMilliseconds() >= 40) {
		m_Trails.Add(new Trail(Vec2(7,7), m_gObj.Get()->GetPosition(), atan(m_gObj.Get()->GetLinearVelocity().y / m_gObj.Get()->GetLinearVelocity().x)));
		m_clockTrail.restart();
		m_gObj.Get()->Update();
	}
	if (!m_TrailFree && m_clockLife.getElapsedTime().asMilliseconds() >= m_lifetime) {
		m_TrailFree = true;
	}
	if (!m_dead && m_TrailFree) {
		if (m_Trails.Size() == 0) {
			m_dead = true;
		}
	}
	for (unsigned int i = 0; i < m_Trails.Size(); i++) {
		m_Trails.Get(i)->Update();
		if (m_Trails.Get(i)->GetDead()) {
			m_Trails.Remove(i);
		}
	}
}
bool SoundWave::GetDead() {
	return m_dead;
}
void SoundWave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (unsigned int i = 0; i < m_Trails.Size(); i++) {
		target.draw(*m_Trails.Get(i), states);
	}
}
