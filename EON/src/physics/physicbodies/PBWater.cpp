#include "physicbodies\PBWater.h"
#include "PhysicWorld.h"

PBWater::PBWater(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBWater::~PBWater(){
    DestroyBody();
}
int PBWater::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBWater::Stop() {
	PhysicBody::DefStop();
}
void PBWater::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_staticBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBWater::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 0.01f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = C_WATER;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_WATER);
}
void PBWater::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBWater::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBWater::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBWater::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
void PBWater::ApplyForce(b2Vec2 force) {
	PhysicBody::DefApplyForce(force);
}
b2Vec2 PBWater::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBWater::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBWater::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBWater::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBWater::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBWater::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBWater::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBWater::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBWater::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBWater::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBWater::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBWater::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBWater::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBWater::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBWater::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
