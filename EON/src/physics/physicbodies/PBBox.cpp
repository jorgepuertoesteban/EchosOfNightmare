#include "physicbodies\PBBox.h"
#include "PhysicWorld.h"

PBBox::PBBox(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBBox::~PBBox(){
    DestroyBody();
}
int PBBox::Inicialize(b2Vec2 pos, b2Vec2 tam){
	b2Vec2 position(pos.x*MPP, -pos.y*MPP);
	b2Vec2 size(tam.x*MPP, tam.y*MPP);
	DestroyBody();
	InitBody(position, size);
    InitFixtures(size);
    return m_bodyId;
}
void PBBox::InitBody(b2Vec2 pos, b2Vec2 tam) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x / 2), -1 * (pos.y - (tam.y / 2)));
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = true;
	bodyDef.angularDamping = true;
	m_pBody = m_pWorld->CreateBody(&bodyDef);
	m_bodyId = PhysicBody::GenerateId();
	m_pBody->SetUserData((void*)m_bodyId);
}
void PBBox::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.3f;
	fixtureDef.density = 0.9f;
	fixtureDef.filter.categoryBits = 3;
	fixtureDef.filter.maskBits = 1|2;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	//fixture->SetUserData((void*)DATA_PLAYER);
	polyShape.SetAsBox(tam.x / 4, tam.y / 4, b2Vec2(0, -tam.y / 2), 0);
	fixtureDef.isSensor = true;
	//fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
	//sensorFixture->SetUserData((void*)DATA_PLAYER_PIES);
}
void PBBox::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBBox::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBBox::DestroyFixtures() {
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;) {
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_pBody->DestroyFixture(fixtureToDestroy);
	}
}
void PBBox::DestroyBody() {
	if (m_pWorld && m_pBody) {
		DestroyFixtures();
		m_pWorld->DestroyBody(m_pBody);
		m_pBody = NULL;
	}
}

b2Vec2 PBBox::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBBox::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBBox::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBBox::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBBox::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBBox::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBBox::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBBox::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBBox::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBBox::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBBox::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBBox::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBBox::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBBox::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}