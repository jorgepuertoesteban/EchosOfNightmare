#pragma once

#include "nocopy.h"
#include <SFML/Graphics.hpp>

class EventListener;

class Scene :public nocopy {
	public:
		virtual ~Scene() {}
		virtual void Update() = 0;
		virtual void Inicialice(EventListener*) = 0;
		virtual void Render(sf::RenderWindow*) = 0;
		virtual void CheckEvents() = 0;
		virtual bool End() = 0;
};

