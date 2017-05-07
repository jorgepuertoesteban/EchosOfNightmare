#include "GameObject.h"
#include "VisualBody.h"
#include "physicbodies\PhysicBody.h"

GameObject::GameObject():m_id(-1){
}
GameObject::~GameObject(){
}
int GameObject::Inicialize(PhysicBody *physicBody, VisualBody *visualBody){
	m_GRphysicBody.Reset(physicBody);
	m_GRVisualBody.Reset(visualBody);
	m_pPhysicBody = m_GRphysicBody.Get();
	m_pVisualBody = m_GRVisualBody.Get();
	m_id = m_pPhysicBody->GetId();
    return m_id;
}
void GameObject::Update(){
	m_pVisualBody->SetPosition(Vec2(m_pPhysicBody->GetPosition().x*PPM, m_pPhysicBody->GetPosition().y*PPM));
	m_pVisualBody->SetRotation(m_pPhysicBody->GetRotation()*RadToGrad);
}
Vec2 GameObject::GetPosition(){
    return  Vec2(m_pPhysicBody->GetPosition().x, m_pPhysicBody->GetPosition().y);
}
float GameObject::GetRotation(){
    return m_pPhysicBody->GetRotation();
}
Vec2 GameObject::GetLinearVelocity(){
    return Vec2(m_pPhysicBody->GetLinearVelocity().x, m_pPhysicBody->GetLinearVelocity().y);
}
int GameObject::GetId(){
    return m_id;
}
int GameObject::SetMode(PhysicBody* body){
    b2Vec2  pos = m_pPhysicBody->GetPosition();
    b2Vec2  vel = m_pPhysicBody->GetLinearVelocity();
    pos.y = pos.y*-1;
    b2Vec2  tam(m_tam.x,m_tam.x);
    m_GRphysicBody.Reset(body);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_id = m_pPhysicBody->Inicialize(pos,tam);
    m_pPhysicBody->SetLinearVelocity(vel);
    return m_id;
}
void GameObject::SetVisible(bool visible){
	m_pVisualBody->SetVisible(visible);
}
void GameObject::SetFixedRotation(bool fixed){
    m_pPhysicBody->SetFixedRotation(fixed);
}
void GameObject::SetRotation(float angle){
    m_pPhysicBody->SetRotation(angle);
}
void GameObject::SetAngularVelocity(float imp){
    m_pPhysicBody->SetAngularVelocity(imp);
}
void GameObject::SetLinearVelocity(Vec2 vel){
    m_pPhysicBody->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}
void GameObject::SetPosition(Vec2 pos){
    m_pPhysicBody->SetPosition(b2Vec2(pos.x, pos.y));
}
void GameObject::Catch(int id){
    m_pPhysicBody->Catch(id);
}
void GameObject::Release(){
    m_pPhysicBody->Release();
}
bool GameObject::Visible() {
	return m_pVisualBody->GetVisible();
}
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(*m_pVisualBody, states);
}
