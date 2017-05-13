#pragma once

#include "Pointer.h"
#include "Vec2.h"

class b2World;
class ContactListener;
class PhysicBody;
class PhysicWorld{
	public:
		PhysicWorld();
		~PhysicWorld();
		void Update();
		void SetContactListener(ContactListener*);
		PhysicBody* CreateBody(PhysicBody* body, Vec2 pos, Vec2 size);
	private:	
		const unsigned int       m_refreshIterations = 5;
		const float			     m_timeStep = 1.f/45.f;
		Pointer<b2World>         m_pb2World;
		b2World*                 m_b2World;
};