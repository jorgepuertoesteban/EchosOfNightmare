#include "Door.h"
#include "GameObject.h"
#include "Map.h"

Door::Door(GameObject *gObj, Map* map, int id): m_door (id), m_pressed(false), m_map(map){
	m_gObj.Reset(gObj);
}
Door::~Door(){
	
}
void Door::Update() {
	if (m_pressed) {
		auto plus = rand() % 45;
		for (unsigned int i = 0; i < 40; i++) {
			float angle = ((i / (float)40) * 360) + plus;
			m_map->CreateSoundWave(m_gObj.Get()->GetPosition(), Vec2(sinf(angle*3.14f / 180.f), cosf(angle*3.14f / 180.f)) * 5, Vec2(8, 8), 20);
		}
	}
}
void Door::Press() {
	m_pressed = true;
}
bool Door::GetPressed() {
	return m_pressed;
}
int  Door::GetId() {
	return m_door;
}
