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
		auto num = rand() % 15 + 10;
		auto desp = 32;
		Vec2 pos = m_gObj.Get()->GetPosition();
		MakeNoise(num , pos);
		MakeNoise(num, Vec2(pos.x + desp, pos.y + desp));
		MakeNoise(num, Vec2(pos.x + desp, pos.y - desp));
		MakeNoise(num, Vec2(pos.x - desp, pos.y + desp));
		MakeNoise(num, Vec2(pos.x - desp, pos.y - desp));
	}
}
void Door::MakeNoise(int num, Vec2 pos) {
	auto plus = rand() % 45;
	for (auto i = 0; i < num; i++) {
		float angle = ((i / (float)num) * 360) + plus;
		m_map->CreateSoundWave(pos, Vec2(sinf(angle*3.14f / 180.f), cosf(angle*3.14f / 180.f)) * 5, Vec2(8, 8), 20);
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
