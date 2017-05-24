#include "Mechanism.h"
#include "GameObject.h"

Mechanism::Mechanism(GameObject *gObj, int door): m_door (door), m_pressed(false){
	m_gObj.Reset(gObj);
}
Mechanism::~Mechanism(){
	
}
void Mechanism::Press() {
	m_pressed = true;
}
bool Mechanism::GetPressed() {
	return m_pressed;
}
int  Mechanism::GetDoor() {
	return m_door;
}
int  Mechanism::GetId() {
	return m_gObj.Get()->GetId();
}
