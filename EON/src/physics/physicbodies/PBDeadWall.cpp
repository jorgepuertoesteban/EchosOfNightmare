#include "physicbodies\PBDeadWall.h"
#include "PhysicWorld.h"

PBDeadWall::PBDeadWall(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBDeadWall::~PBDeadWall(){
    DestroyBody();
}
int PBDeadWall::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBDeadWall::Stop() {
	PhysicBody::DefStop();
}
void PBDeadWall::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_staticBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBDeadWall::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 0.01f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = C_DEADWALL;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_DEADWALL);
}
void PBDeadWall::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBDeadWall::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBDeadWall::ApplyForce(b2Vec2 force) {
	PhysicBody::DefApplyForce(force);
}
void PBDeadWall::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBDeadWall::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBDeadWall::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBDeadWall::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBDeadWall::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBDeadWall::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBDeadWall::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBDeadWall::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBDeadWall::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBDeadWall::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBDeadWall::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBDeadWall::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBDeadWall::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBDeadWall::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBDeadWall::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBDeadWall::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBDeadWall::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
