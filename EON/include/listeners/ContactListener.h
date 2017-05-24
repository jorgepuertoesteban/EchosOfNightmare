#pragma once

#include <Box2D/Box2D.h>
#include "PhysicColiders.h"

class ContactListener;
class SoundWave;
class Mechanism;
class Player;
class Enemy;
class Rock;
class Map;



class ContactListener: public b2ContactListener{
    public:
        ContactListener(Map *map);
        virtual ~ContactListener(){}
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
    private:
		struct Contact2Method {
			unsigned long A;
			unsigned long B;
			void (ContactListener::*p)();
		};
    	const Contact2Method beginContact[13] = {
			  { D_PLAYER         , D_DEADWALL      , &ContactListener::KillPlayer          }
			 ,{ D_SOUNDWAVE      , D_DEADWALL      , &ContactListener::SWaveDWallBegin     }
			 ,{ D_SOUNDWAVE      , D_GOAL          , &ContactListener::SWaveGoalBegin      }
			 ,{ D_SOUNDWAVE      , D_WATER         , &ContactListener::SWaveWaterBegin     }
			 ,{ D_SOUNDWAVE      , D_ENEMY         , &ContactListener::SWaveEnemy          }
			 ,{ D_SOUNDWAVE      , D_MECHANISM     , &ContactListener::SWaveMechanismBegin }
			 ,{ D_PLAYER         , D_MECHANISM     , &ContactListener::PlayerMechanism     }
			 ,{ D_PLAYER         , D_DEADWALL      , &ContactListener::KillPlayer          }
			 ,{ D_PLAYER         , D_ENEMY         , &ContactListener::KillPlayer          }
			 ,{ D_PLAYER         , D_GOAL          , &ContactListener::Win                 }
			 ,{ D_ROCK           , D_WALL          , &ContactListener::RockColision        }
			 ,{ D_PLAYER         , D_WATER         , &ContactListener::PlayerWaterBegin    }
			 ,{ 0                , 0               , 0                                     }
        };
        const Contact2Method endContact[7] = {
              { D_SOUNDWAVE      , D_DEADWALL   , &ContactListener::SWaveResetColor }
			 ,{ D_SOUNDWAVE      , D_GOAL       , &ContactListener::SWaveResetColor }
			 ,{ D_SOUNDWAVE      , D_WATER      , &ContactListener::SWaveResetColor }
			 ,{ D_SOUNDWAVE      , D_ENEMY      , &ContactListener::SWaveResetColor }
			 ,{ D_SOUNDWAVE      , D_MECHANISM  , &ContactListener::SWaveResetColor }
			 ,{ D_PLAYER         , D_WATER      , &ContactListener::PlayerWaterEnd  }
			,{ 0                 , 0            , 0                                 }
        };
        b2Contact* contact;
		SoundWave* GetSoundWave();
		Mechanism* GetMechanism();
		Enemy*     GetEnemy();
		Rock*      GetRock();
		Map *m_map;
		void Win();
		void RockColision();
		void KillPlayer();
		void PlayerMechanism();
		void SWaveDWallBegin();
		void SWaveGoalBegin();
		void SWaveWaterBegin();
		void SWaveMechanismBegin();
		void PlayerWaterBegin();
		void SWaveResetColor();
		void PlayerWaterEnd();
		void SWaveEnemy();
};
