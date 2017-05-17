#include "SceneFabric.h"
#include "Map_Intro.h"
#include "Map_1.h"


SceneFabric::SceneFabric(sf::View* view):m_view(view), m_Number(0){
	m_scene.Reset(new Map_Intro(m_view));
}
SceneFabric::~SceneFabric(){

}
Scene* SceneFabric::Get(unsigned int id){
	const Num2Scene * it = scenes;
	while (it->A != -1) {
		if (it->A == id) {
			(this->*it->Num2Scene::p)();
			break;
		}
		it++;
	}
	return m_scene.Get();
}
Scene* SceneFabric::GetSame(){
	const Num2Scene * it = scenes;
	while (it->A != -1) {
		if (it->A == m_Number) {
			(this->*it->Num2Scene::p)();
			break;
		}
		it++;
	}
	return m_scene.Get();
}
Scene* SceneFabric::GetNext(){
	const Num2Scene * it = scenes;
	while (it->A != -1) {
		if (it->A == m_Number) {
			(this->*it->Num2Scene::p)();
			break;
		}
		it++;
	}
	m_Number++;
	return m_scene.Get();
}

void SceneFabric::Intro() { m_scene.Reset(new Map_Intro(m_view)); }
void SceneFabric::Map1()  { m_scene.Reset(new Map_1    (m_view)); }
void SceneFabric::NullPointer(){ m_scene.Reset(nullptr); }
