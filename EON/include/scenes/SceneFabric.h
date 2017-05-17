#pragma once

#include "SceneFabric.h"
#include "Pointer.h"
#include "Scene.h"


class SceneFabric{
	public:
		SceneFabric(sf::View* view);
		Scene* Get(unsigned int id);
		Scene* GetSame();
		Scene* GetNext();
		virtual ~SceneFabric();
	private:
		struct Num2Scene {
			int A;
			void (SceneFabric::*p)();
		};
		const Num2Scene scenes[3] = {
			 { 0       , &SceneFabric::Intro       }
			,{ 1       , &SceneFabric::Map1        }
			,{ 2       , &SceneFabric::NullPointer }
		};
		void Intro();
		void Map1();
		void NullPointer();
		sf::View*       m_view;
		Pointer<Scene>  m_scene;
		int             m_Number;
};

