#include "SoundWave.h"


SoundWave::SoundWave(GameObject *gameobj):m_gObj(gameobj){
}
SoundWave::~SoundWave() {
}
void SoundWave::Update() {
	m_gObj->Update();
}
