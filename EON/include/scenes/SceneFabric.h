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
		const Num2Scene scenes[14] = {
			 { 0       , &SceneFabric::Intro       }
			,{ 1       , &SceneFabric::Map1        }
			,{ 2       , &SceneFabric::Map2        }
			,{ 3       , &SceneFabric::Map3        }
			,{ 4       , &SceneFabric::Map4        }
			,{ 5       , &SceneFabric::Map5        }
			,{ 6       , &SceneFabric::Map6        }
			,{ 7       , &SceneFabric::Map7        }
			,{ 8       , &SceneFabric::Map8        }
			,{ 8       , &SceneFabric::Map8        }
			,{ 9       , &SceneFabric::Map9        }
			,{ 10      , &SceneFabric::Map10       }
			,{ 11      , &SceneFabric::End         }
			,{ 12      , &SceneFabric::NullPointer }
		};
		void Intro();
		void Map1();
		void Map2();
		void Map3();
		void Map4();
		void Map5();
		void Map6();
		void Map7();
		void Map8();
		void Map9();
		void Map10();
		void End();
		void NullPointer();
		sf::View*       m_view;
		Pointer<Scene>  m_scene;
		int             m_Number;
};

