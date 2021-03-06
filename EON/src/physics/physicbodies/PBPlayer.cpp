#include "physicbodies\PBPlayer.h"
#include "PhysicWorld.h"

PBPlayer::PBPlayer(){
    m_pJoint  = nullptr;
    m_pBody   = nullptr;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBPlayer::~PBPlayer(){
    DestroyBody();
}
int PBPlayer::Inicialize(b2Vec2 pos, b2Vec2 tam){
	return PhysicBody::DefInicialize( pos,  tam);
}
void PBPlayer::InitBody(b2Vec2 pos, b2Vec2 tam) {
	return PhysicBody::DefInitBody( pos,  tam);
}
void PBPlayer::Stop() {
	PhysicBody::DefStop();
}
void PBPlayer::InitFixtures(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x / 2), (tam.y / 2));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 1.f;
	fixtureDef.density = 1;
	fixtureDef.filter.categoryBits = C_PLAYER;
	fixtureDef.filter.maskBits = C_DEADWALL|C_WALL|C_GOAL | C_WATER | C_ENEMY | C_MECHANISM | C_MAGNET;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)D_PLAYER);
}
void PBPlayer::Catch(int id) {
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_pBody;
	jointDef.bodyB = GetBodyWithId(id);
	jointDef.localAnchorA.Set(0, 0.3f);
	jointDef.localAnchorB.Set(0, 0);
	m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
	m_pJoint->EnableMotor(true);
}
void PBPlayer::Release() {
	if (m_pJoint)
		m_pWorld->DestroyJoint(m_pJoint);
	m_pJoint = nullptr;
}
void PBPlayer::DestroyFixtures() {
	PhysicBody::DefDestroyFixtures();
}
void PBPlayer::ApplyForce(b2Vec2 force) {
	PhysicBody::DefApplyForce(force);
}
void PBPlayer::DestroyBody() {
	PhysicBody::DefDestroyBody();
}
b2Vec2 PBPlayer::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBPlayer::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBPlayer::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBPlayer::GetId(){
    return PhysicBody::DefGetId();
}
b2Vec2 PBPlayer::GetVertexPosition(int vertex) {
	return PhysicBody::DefGetVertexPosition(vertex);
}
void   PBPlayer::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBPlayer::SetRotationFromCorner(float angle) {
	PhysicBody::DefSetRotationFromCorner(angle);
}
void   PBPlayer::SetWorld(b2World* world) {
	PhysicBody::DefSetWorld(world);
}
void   PBPlayer::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBPlayer::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBPlayer::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBPlayer::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBPlayer::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBPlayer::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBPlayer::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
