#include "physicbodies\PBSoundWave.h"
#include "PhysicWorld.h"

PBSoundWave::PBSoundWave(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBSoundWave::~PBSoundWave(){
    DestroyBody();
}
int PBSoundWave::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBSoundWave::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_dynamicBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBSoundWave::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0 ;
	fixtureDef.restitution = 1;
	fixtureDef.density = 0 ;
	fixtureDef.filter.categoryBits = C_SOUNDWAVE;
	fixtureDef.filter.maskBits = C_WALL|C_DEADWALL|C_GOAL|C_WATER|C_ENEMY;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_SOUNDWAVE);
}
void PBSoundWave::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBSoundWave::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBSoundWave::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBSoundWave::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBSoundWave::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBSoundWave::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBSoundWave::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBSoundWave::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBSoundWave::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBSoundWave::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBSoundWave::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBSoundWave::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBSoundWave::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBSoundWave::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBSoundWave::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBSoundWave::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBSoundWave::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBSoundWave::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBSoundWave::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}