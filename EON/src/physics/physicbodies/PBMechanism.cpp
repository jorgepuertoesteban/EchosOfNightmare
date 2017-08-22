#include "physicbodies\PBMechanism.h"
#include "PhysicWorld.h"

PBMechanism::PBMechanism(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBMechanism::~PBMechanism(){
    DestroyBody();
}
int PBMechanism::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBMechanism::InitBody(b2Vec2 pos, b2Vec2 tam) {
	return PhysicBody::DefInitBody(pos, tam);
}
void PBMechanism::Stop() {
	PhysicBody::DefStop();
}
void PBMechanism::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 0.01f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = C_MECHANISM;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_MECHANISM);
}
void PBMechanism::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBMechanism::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBMechanism::ApplyForce(b2Vec2 force) {
	PhysicBody::DefApplyForce(force);
}
void PBMechanism::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBMechanism::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBMechanism::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBMechanism::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float  PBMechanism::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBMechanism::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBMechanism::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBMechanism::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBMechanism::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBMechanism::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBMechanism::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBMechanism::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBMechanism::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBMechanism::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBMechanism::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBMechanism::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBMechanism::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
