#include "physicbodies\PBEnemySoundWave.h"
#include "PhysicWorld.h"

PBEnemySoundWave::PBEnemySoundWave(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBEnemySoundWave::~PBEnemySoundWave(){
    DestroyBody();
}
int PBEnemySoundWave::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBEnemySoundWave::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_dynamicBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBEnemySoundWave::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0 ;
	fixtureDef.restitution = 1;
	fixtureDef.density = 0;
	fixtureDef.isSensor = true ;
	fixtureDef.filter.categoryBits = C_ENEMYSOUNDWAVE;
	fixtureDef.filter.maskBits = C_NONE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_SOUNDWAVE);
}
void PBEnemySoundWave::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBEnemySoundWave::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBEnemySoundWave::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBEnemySoundWave::DestroyBody() {
	PhysicBody::DefDestroyBody();
}

b2Vec2 PBEnemySoundWave::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBEnemySoundWave::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBEnemySoundWave::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBEnemySoundWave::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBEnemySoundWave::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBEnemySoundWave::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBEnemySoundWave::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBEnemySoundWave::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBEnemySoundWave::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBEnemySoundWave::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBEnemySoundWave::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBEnemySoundWave::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBEnemySoundWave::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBEnemySoundWave::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBEnemySoundWave::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}