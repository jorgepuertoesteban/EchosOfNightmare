#pragma once

#include <SFML\Graphics.hpp>
#include "Pointer.h"
#include "Vec2.h"

class PhysicBody;
class PhysicWorld;
class VisualBody;


class GameObject : public sf::Drawable {
    public:
        GameObject();
        virtual int Inicialize(PhysicBody *physicBody,VisualBody *visualBody);
        virtual ~GameObject();
		virtual void   Update();
        virtual int    SetMode(PhysicBody* body);
        virtual void   SetVisible(bool visible);
        virtual Vec2   GetPosition();
        virtual float  GetRotation();
        virtual Vec2   GetLinearVelocity();
		virtual Vec2   GetVertexPosition(int vertex);
        virtual int    GetId();
        virtual void   SetFixedRotation(bool fixed);
        virtual void   SetRotation(float angle);
        virtual void   SetAngularVelocity(float imp);
        virtual void   SetLinearVelocity(Vec2 vel);
        virtual void   SetPosition(Vec2 pos);
		virtual void   ApplyForce(Vec2 force);
		virtual void   Stop();
		virtual void   Catch(int id);
        virtual void   Release();
		virtual bool   Visible();
    private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		const float RadToGrad = 180.f / 3.14159265f;
		const float PPM = 64.0f;
		const float MPP = 1.0f / PPM;
		Pointer<PhysicBody> m_GRphysicBody;
		PhysicBody *m_pPhysicBody = nullptr;
		Pointer<VisualBody> m_GRVisualBody;
		VisualBody *m_pVisualBody = nullptr;
        PhysicWorld *m_pWorld = nullptr;
		unsigned int m_id = -1;
		Vec2 m_tam;
		Vec2 m_pos;
};

