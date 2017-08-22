#include "physicbodies\PBMagnet.h"
#include "PhysicWorld.h"

PBMagnet::PBMagnet(){
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBMagnet::~PBMagnet(){
    DestroyBody();
}
int PBMagnet::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBMagnet::InitBody(b2Vec2 pos, b2Vec2 tam) {
	return PhysicBody::DefInitBody(pos, tam);
}
void PBMagnet::Stop() {
	PhysicBody::DefStop();
}
void PBMagnet::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2CircleShape circleShape;
	circleShape.m_radius = (tam.x / 2);
	fixtureDef.shape = &circleShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 0.01f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = C_MAGNET;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_MAGNET);
}
void PBMagnet::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBMagnet::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBMagnet::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBMagnet::ApplyForce(b2Vec2 force) {
	PhysicBody::DefApplyForce(force);
}
void PBMagnet::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBMagnet::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBMagnet::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float  PBMagnet::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBMagnet::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBMagnet::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBMagnet::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBMagnet::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBMagnet::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBMagnet::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBMagnet::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBMagnet::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBMagnet::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBMagnet::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBMagnet::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBMagnet::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
