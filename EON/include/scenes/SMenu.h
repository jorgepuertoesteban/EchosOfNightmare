#pragma once

#include "Scene.h"

class SMenu: public Scene  {
	public:
		SMenu();
		virtual ~SMenu();
		virtual void Inicialice(EventListener*);
		virtual void Update();
		virtual void Render();
		virtual void CheckEvents() = 0;
		virtual bool End() = 0;
private:
};

