#include "physicbodies\PBWall.h"
#include "PhysicWorld.h"

PBWall::PBWall(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBWall::~PBWall(){
    DestroyBody();
}
int PBWall::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBWall::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_staticBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBWall::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 0.01f;
	fixtureDef.filter.categoryBits = C_WALL;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_WALL);
}
void PBWall::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBWall::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBWall::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBWall::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBWall::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBWall::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBWall::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBWall::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBWall::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBWall::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBWall::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBWall::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBWall::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBWall::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBWall::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBWall::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBWall::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBWall::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBWall::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
