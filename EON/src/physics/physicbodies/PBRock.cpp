#include "physicbodies\PBRock.h"
#include "PhysicWorld.h"

PBRock::PBRock(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBRock::~PBRock(){
    DestroyBody();
}
int PBRock::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBRock::Stop() {
	PhysicBody::DefStop();
}
void PBRock::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_dynamicBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBRock::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0 ;
	fixtureDef.restitution = 1;
	fixtureDef.density = 0 ;
	fixtureDef.filter.categoryBits = C_ROCK;
	fixtureDef.filter.maskBits = C_WALL;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_ROCK);
}
void PBRock::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBRock::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBRock::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBRock::ApplyForce(b2Vec2 force) {
	PhysicBody::DefApplyForce(force);
}
void PBRock::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBRock::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBRock::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBRock::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBRock::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBRock::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBRock::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBRock::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBRock::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBRock::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBRock::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBRock::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBRock::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBRock::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBRock::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBRock::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}