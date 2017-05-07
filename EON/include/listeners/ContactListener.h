#pragma once

#include <Box2D/Box2D.h>
//#include "World.h"

class ContactListener;
class Player;
class Teleport;
struct Contact2Method {
     unsigned long A;
     unsigned long B;
     void (ContactListener::*p)();
};

class ContactListener: public b2ContactListener{
    public:
        ContactListener();
        virtual ~ContactListener(){}
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PlayerTeleport();
    private:
    	const Contact2Method beginContact[2] = {
            //  { DATA_PLAYER         , DATA_TELEPORT       , PlayerTeleport      }
            //, { 0                   , 0                   , 0                   }
        };
        const Contact2Method endContact[1] = {
            //  { DATA_PLAYER         , DATA_COGIBLE_SENSOR , PlayerCogibleEnd    }
            //, { 0                   , 0                   , 0                   }
        };
        //World* m_pWorld;
        b2Contact* contact;
        Player* GetPlayer();
        Teleport* GetTeleport();
};
