#pragma once

#include <Box2D/Box2D.h>
#include "PhysicColiders.h"

class ContactListener;
class SoundWave;
class Player;
class Map;

struct Contact2Method {
     unsigned long A;
     unsigned long B;
     void (ContactListener::*p)();
};

class ContactListener: public b2ContactListener{
    public:
        ContactListener(Map *map);
        virtual ~ContactListener(){}
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PlayerTeleport();
    private:
    	const Contact2Method beginContact[5] = {
			  { D_PLAYER         , D_DEADWALL      , &ContactListener::KillPlayer          }
			 ,{ D_SOUNDWAVE      , D_DEADWALL      , &ContactListener::SWaveDWallBegin }
			,{ D_SOUNDWAVE      , D_GOAL          , &ContactListener::SWaveGoalBegin }
			, { D_SOUNDWAVE      , D_WATER          , &ContactListener::SWaveWaterBegin     }
			, { 0                , 0               , 0                   }
        };
        const Contact2Method endContact[4] = {
              { D_SOUNDWAVE         , D_DEADWALL   , &ContactListener::SWaveResetColor }
			  ,{ D_SOUNDWAVE         , D_GOAL       , &ContactListener::SWaveResetColor }
			,{ D_SOUNDWAVE         , D_WATER       , &ContactListener::SWaveResetColor }
			, { 0                   , 0            , 0               }
        };
        b2Contact* contact;
		SoundWave* GetSoundWave();
		Map *m_map;
		void KillPlayer();
		void SWaveDWallBegin();
		void SWaveGoalBegin();
		void SWaveWaterBegin();
		void SWaveResetColor();
};
