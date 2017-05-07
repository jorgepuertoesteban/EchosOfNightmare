#include "PhysicWorld.h"
#include "physicbodies\PhysicBody.h"
#include "ContactListener.h"
#include <Box2D/Box2D.h>

PhysicWorld::PhysicWorld(){
	m_pb2World.Reset(new b2World(b2Vec2(0, 0)));
	m_b2World = m_pb2World.Get();
}
PhysicWorld::~PhysicWorld(){
}
void PhysicWorld::Update(){
	m_b2World->Step(m_timeStep, m_refreshIterations, m_refreshIterations);
}
void PhysicWorld::SetContactListener(ContactListener* contactListener) {
	m_b2World->SetContactListener(contactListener);
}
PhysicBody* PhysicWorld::CreateBody(PhysicBody* body, Vec2 pos, Vec2 size ) {
	body->SetWorld(m_b2World);
	body->Inicialize(b2Vec2(pos.x, pos.y), b2Vec2(size.x, size.y));
	return body;
}
