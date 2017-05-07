#include "ContactListener.h"
//#include "Teleport.h"
//#include "Player.h"

ContactListener::ContactListener(){
    //World::Inst()  = World::Inst();
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
void ContactListener::PlayerTeleport(){
    Teleport* tp = GetTeleport();
    //for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
    //    if(World::Inst()->GetTeleports().at(i)){
    //        if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
    //            GetPlayer()->setNextPos(World::Inst()->GetTeleports().at(i)->getPosition());
    //            return;
    //        }
    //    }
    //}
}

Player* ContactListener::GetPlayer(){
	//for(unsigned int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
	//    if(World::Inst()->GetPlayers().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
	//    || World::Inst()->GetPlayers().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
	//        return World::Inst()->GetPlayers().at(i);
	//    }
	//}
    return nullptr;
}
Teleport* ContactListener::GetTeleport(){
	//for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
	//    if(World::Inst()->GetTeleports().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
	//    || World::Inst()->GetTeleports().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
	//        return World::Inst()->GetTeleports().at(i);
	//    }
	//}
    return nullptr;
}
