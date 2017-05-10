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
	b2Vec2 position(pos.x*MPP, -pos.y*MPP);
	b2Vec2 size(tam.x*MPP, tam.y*MPP);
	DestroyBody();
	InitBody(position, size);
    InitFixtures(size);
    return m_bodyId;
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
	fixtureDef.density = 1 ;
	fixtureDef.filter.categoryBits = 4;
	fixtureDef.filter.maskBits = 2;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	//fixture->SetUserData((void*)DATA_PLAYER);
	polyShape.SetAsBox(tam.x / 4, tam.y / 4, b2Vec2(0, -tam.y / 2), 0);
	fixtureDef.isSensor = true;
	//fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
	//sensorFixture->SetUserData((void*)DATA_PLAYER_PIES);
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
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;) {
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_pBody->DestroyFixture(fixtureToDestroy);
	}
}
void PBSoundWave::DestroyBody() {
	if (m_pWorld && m_pBody) {
		DestroyFixtures();
		m_pWorld->DestroyBody(m_pBody);
		m_pBody = NULL;
	}
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
void   PBSoundWave::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
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