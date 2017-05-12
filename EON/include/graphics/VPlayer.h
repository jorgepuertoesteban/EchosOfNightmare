#pragma once

#include <SFML/Graphics.hpp>
#include "VisualBody.h"
#include "PVector.h"

struct step {
	sf::Sprite   sprite;
	bool         dead;
	step(sf::Sprite sprite) :sprite(sprite) { 
		dead  = false; 
	}
	bool Update() {
		auto alpha = sprite.getColor().a - 1;
		sprite.setColor(sf::Color(255, 255, 255, alpha));
		if (alpha == 0) {
			dead = true;
		}
		return dead;
	}

};

class VPlayer: public VisualBody{
    public:
        VPlayer();
        virtual ~VPlayer();
		virtual void Initialize(Vec2 size);
		virtual bool   GetVisible();
		virtual void   SetPosition(Vec2 pos);
        virtual void   SetRotation(float angle);
		virtual void   SetVisible(bool aux);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	    bool                     m_visible,
								 m_setedPos,
								 m_stop,
				                 m_move;
		Vec2					 m_actPos,
								 m_size;
		sf::Texture              m_texture[3];
		sf::Texture              *m_actualTxt;
		PVector<step>            m_sprites;
		sf::Clock				 m_clockStop,
								 m_clockMove;
		unsigned int             m_actNumText;
		float                    m_angle;
};
