#include "SceneFabric.h"
#include "Map_Intro.h"
#include "Map_1.h"
#include "Map_2.h"
#include "Map_3.h"
#include "Map_4.h"
#include "Map_5.h"
#include "Map_6.h"
#include "Map_7.h"
#include "Map_8.h"


SceneFabric::SceneFabric(sf::View* view):m_view(view), m_Number(6){
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
	m_Number++;
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

void SceneFabric::Intro()      { m_scene.Reset(new Map_Intro(m_view)); }
void SceneFabric::Map1()       { m_scene.Reset(new Map_1     (m_view)); }
void SceneFabric::Map2()       { m_scene.Reset(new Map_2     (m_view)); }
void SceneFabric::Map3()       { m_scene.Reset(new Map_3     (m_view)); }
void SceneFabric::Map4()       { m_scene.Reset(new Map_4     (m_view)); }
void SceneFabric::Map5()       { m_scene.Reset(new Map_5     (m_view)); }
void SceneFabric::Map6()       { m_scene.Reset(new Map_6     (m_view)); }
void SceneFabric::Map7()       { m_scene.Reset(new Map_7     (m_view)); }
void SceneFabric::Map8()       { m_scene.Reset(new Map_8      (m_view)); }
void SceneFabric::NullPointer(){ m_scene.Reset(nullptr); }
