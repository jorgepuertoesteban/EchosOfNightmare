#include "ContactListener.h"
#include "SoundWave.h"
#include "Map.h"

ContactListener::ContactListener(Map* map):m_map(map){
}
void ContactListener::BeginContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Method * it = beginContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Method::p)();
            break;
        }
        it++;
    }
}
void ContactListener::EndContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Method * it = endContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Method::p)();
            break;
        }
        it++;
    }
}


void ContactListener::KillPlayer(){

}
void ContactListener::SWaveDWallBegin() {
	GetSoundWave()->SetColor(255, 0, 0);
}
void ContactListener::SWaveGoalBegin() {
	GetSoundWave()->SetColor(0, 255, 0);
}
void ContactListener::SWaveWaterBegin() {
	GetSoundWave()->SetColor(0, 0, 255);
}
void ContactListener::SWaveResetColor() {
	GetSoundWave()->SetColor(255, 255, 255);

}
void ContactListener::PlayerTeleport(){
    //Teleport* tp = GetTeleport();
    //for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
    //    if(World::Inst()->GetTeleports().at(i)){
    //        if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
    //            GetPlayer()->setNextPos(World::Inst()->GetTeleports().at(i)->getPosition());
    //            return;
    //        }
    //    }
    //}
}

SoundWave* ContactListener::GetSoundWave(){
	auto waves = m_map->GetSoundWaves();
	for(auto it = waves->GetBegin(); it != waves->GetEnd(); ++it){
	    if((*it)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
	    || (*it)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
	        return (*it);
	    }
	}
    return nullptr;
}
