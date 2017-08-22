#pragma once

#include "PhysicBody.h"

class PBPlayer: public PhysicBody{
    public:
        PBPlayer();
        virtual ~PBPlayer();
        virtual int   Inicialize(b2Vec2 pos, b2Vec2 tam);
		virtual void   ApplyForce(b2Vec2 force);
		virtual b2Vec2 GetPosition();
		virtual b2Vec2 GetLinearVelocity();
        virtual float  GetRotation();
        virtual int    GetId();
		virtual b2Vec2 GetVertexPosition(int vertex);
		virtual void   SetFixedRotation(bool fixed);
        virtual void   SetRotation(float angle);
		virtual void   SetRotationFromCorner(float angle);
		virtual void   SetWorld(b2World* world);
		virtual void   SetAngularVelocity(float imp);
        virtual void   SetLinearVelocity(b2Vec2 vel);
        virtual void   SetPosition(b2Vec2 pos);
        virtual void   DestroyFixtures();
        virtual void   SetCategory(uint16 i);
        virtual void   SetUserData(int i);
        virtual void   SetMask(uint16 i);
        virtual void   Catch(int id);
		virtual void   Stop();
		virtual void   Release();

    private:
    	virtual void   InitBody(b2Vec2 pos,b2Vec2 tam);
        virtual void   InitFixtures(b2Vec2 tam);
        virtual void   DestroyBody();
        
        b2RevoluteJoint *m_pJoint;
};
