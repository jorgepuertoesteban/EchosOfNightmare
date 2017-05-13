#include "physicbodies\PBGoal.h"
#include "PhysicWorld.h"

PBGoal::PBGoal(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBGoal::~PBGoal(){
    DestroyBody();
}
int PBGoal::Inicialize(b2Vec2 pos, b2Vec2 tam){
	b2Vec2 position(pos.x*MPP, -pos.y*MPP);
	b2Vec2 size(tam.x*MPP, tam.y*MPP);
	DestroyBody();
	InitBody(position, size);
    InitFixtures(size);
    return m_bodyId;
}
void PBGoal::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_staticBody;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBGoal::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 0.01f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = C_GOAL;
	fixtureDef.filter.maskBits = C_PLAYER|C_SOUNDWAVE;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_GOAL);
}
void PBGoal::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBGoal::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBGoal::DestroyFixtures() {
	//for (b2Fixture* f = m_pBody->GetFixtureList(); f;) {
	//	b2Fixture* fixtureToDestroy = f;
	//	f = f->GetNext();
	//	m_pBody->DestroyFixture(fixtureToDestroy);
	//}
}
void PBGoal::DestroyBody() {
	//if (m_pWorld && m_pBody) {
	//	DestroyFixtures();
	//	m_pWorld->DestroyBody(m_pBody);
	//	m_pBody = NULL;
	//}
}
b2Vec2 PBGoal::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBGoal::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBGoal::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBGoal::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBGoal::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBGoal::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBGoal::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBGoal::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBGoal::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBGoal::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBGoal::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBGoal::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBGoal::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBGoal::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBGoal::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
