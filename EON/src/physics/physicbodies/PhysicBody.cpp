#include "physicbodies\PhysicBody.h"

int PhysicBody::c_id= -1;
b2Vec2 PhysicBody::DefGetPosition(){
	return m_pBody->GetPosition();
}
b2Vec2 PhysicBody::DefGetLinearVelocity(){
	return m_pBody->GetLinearVelocity();
}
float PhysicBody::DefGetRotation(){
	return m_pBody->GetAngle();
}
int PhysicBody::DefGetId(){
	return m_bodyId;
}
b2Vec2 PhysicBody::DefGetVertexPosition(int vertex) {
	b2PolygonShape* shape = dynamic_cast<b2PolygonShape *>(m_pBody->GetFixtureList()->GetShape());
	if (shape)
		return m_pBody->GetWorldPoint(shape->GetVertex(vertex));
	else
		return b2Vec2(0,0);
}
void  PhysicBody::DefSetFixedRotation(bool fixed){
    m_pBody->SetFixedRotation(fixed);
}
void PhysicBody::DefSetRotation(float angle) {
	m_pBody->SetTransform(m_pBody->GetPosition(), angle);
}
void PhysicBody::DefSetRotationFromCorner(float angle) {
	b2PolygonShape* shape = dynamic_cast<b2PolygonShape *>(m_pBody->GetFixtureList()->GetShape());
	if (shape) {
		int vertex = 0;
		b2Vec2 p1 = m_pBody->GetWorldPoint(shape->GetVertex(vertex));
		m_pBody->SetTransform(m_pBody->GetPosition(), angle);
		b2Vec2 p2 = m_pBody->GetWorldPoint(shape->GetVertex(vertex));
		m_pBody->SetTransform(m_pBody->GetPosition() + p1 - p2, m_pBody->GetAngle());
	}
}
void PhysicBody::DefSetWorld(b2World* world) {
	m_pWorld = world;
}
void   PhysicBody::DefSetPosition(b2Vec2 pos){
	m_pBody->SetTransform(pos,m_pBody->GetAngle());
}
void   PhysicBody::DefSetAngularVelocity(float vel){
	m_pBody->ApplyAngularImpulse(vel,true);
}
void   PhysicBody::DefSetLinearVelocity(b2Vec2 vel){
	m_pBody->SetLinearVelocity(vel);
}
void PhysicBody::DefSetCategory(uint16 i){
	m_category = i;
}
void PhysicBody::DefSetUserData(int i){
	m_userData = i;
}
void PhysicBody::DefSetMask(uint16 i){
	m_mask = i;
}
void PhysicBody::DefCatch(int id){
}
void PhysicBody::DefRelease(){
}
int PhysicBody::GenerateId(){
	c_id++;
	return c_id;
}
b2Body* PhysicBody::GetBodyWithId(int id){
	for ( b2Body* b = m_pWorld->GetBodyList(); b; b = b->GetNext()){
        if((int)b->GetUserData() == id){
            return b;
        }
	}
	return nullptr;
}
