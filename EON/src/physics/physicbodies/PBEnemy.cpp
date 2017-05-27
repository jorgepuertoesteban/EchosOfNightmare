#include "physicbodies\PBEnemy.h"
#include "PhysicWorld.h"

PBEnemy::PBEnemy(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBEnemy::~PBEnemy(){
    DestroyBody();
}
int PBEnemy::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBEnemy::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_dynamicBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBEnemy::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2CircleShape circleShape;
	circleShape.m_radius = tam.x / 1.5f;
	fixtureDef.shape = &circleShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 1;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = C_ENEMY;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_ENEMY);
}
void PBEnemy::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBEnemy::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBEnemy::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBEnemy::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBEnemy::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBEnemy::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBEnemy::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBEnemy::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBEnemy::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBEnemy::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBEnemy::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBEnemy::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBEnemy::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBEnemy::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBEnemy::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBEnemy::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBEnemy::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBEnemy::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBEnemy::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
