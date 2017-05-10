#include "physicbodies\PBWall.h"
#include "PhysicWorld.h"
//#include "World.h"

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
	b2Vec2 position(pos.x*MPP, -pos.y*MPP);
	b2Vec2 size(tam.x*MPP, tam.y*MPP);
	DestroyBody();
	InitBody(position, size);
    //SetFixedRotation(true);
    InitFixtures(size);
    return m_bodyId;
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
	fixtureDef.filter.categoryBits = 2;
	fixtureDef.filter.maskBits = 1|3|4;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	//fixture->SetUserData((void*)DATA_PLAYER);
	polyShape.SetAsBox(tam.x / 4, tam.y / 4, b2Vec2(0, -tam.y / 2), 0);
	fixtureDef.isSensor = true;
	//fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
	//sensorFixture->SetUserData((void*)DATA_PLAYER_PIES);
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
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;) {
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_pBody->DestroyFixture(fixtureToDestroy);
	}
}
void PBWall::DestroyBody() {
	if (m_pWorld && m_pBody) {
		DestroyFixtures();
		m_pWorld->DestroyBody(m_pBody);
		m_pBody = NULL;
	}
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
