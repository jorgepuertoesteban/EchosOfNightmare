/*
#include "Director.h"

int main(){
	Director *director = new Director();
	while (director->Update()) {
		director->Render();
	}
}
*/

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Box2D\Box2D.h"	
#include <queue>




#define TIMESTEP 1.0f/60.0f     //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL




int main(){

	b2World world(b2Vec2(0.0f, 0.0f));

	b2BodyDef sueloBodyDef;
	sueloBodyDef.position.Set(300 * MPP, 0 * MPP);
	b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
	b2PolygonShape sueloBox;
	sueloBox.SetAsBox(600 / 2 * MPP, 1 / 2 * MPP);
	sueloBody->CreateFixture(&sueloBox, 0.0f);

	sueloBodyDef.position.Set(300 * MPP, 630 * MPP);
	sueloBody = world.CreateBody(&sueloBodyDef);
	sueloBox.SetAsBox(600 / 2 * MPP, 1 / 2 * MPP);
	sueloBody->CreateFixture(&sueloBox, 0.0f);

	sueloBodyDef.position.Set(0 * MPP, 300 * MPP);
	sueloBody = world.CreateBody(&sueloBodyDef);
	sueloBox.SetAsBox(1 / 2 * MPP, 600 / 2 * MPP);
	sueloBody->CreateFixture(&sueloBox, 0.0f);

	sueloBodyDef.position.Set(600 * MPP, 300 * MPP);
	sueloBody = world.CreateBody(&sueloBodyDef);
	sueloBox.SetAsBox(1 / 2 * MPP, 600 / 2 * MPP);
	sueloBody->CreateFixture(&sueloBox, 0.0f);

	b2PolygonShape polyShape;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody; //Definimos un cuerpo dinamico (afectado por la gravedad y resto de objetos box2d creados)
	bodyDef.position.Set(100 * MPP, 100 * MPP);
	b2Body* caja = world.CreateBody(&bodyDef);

	polyShape.SetAsBox(10 / 2 * MPP, 10 / 2 * MPP);

	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 1;
	fixtureDef.density = 1;

	caja->CreateFixture(&fixtureDef);

	caja->SetLinearVelocity(b2Vec2(5,7));
	caja->SetFixedRotation(true);

	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML WORKS!");
	window.setFramerateLimit(60);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
 
	//estela[0].position = sf::Vector2f(0, 100);
	//estela[0].color = sf::Color(255,255,255,0);


	std::vector<b2Vec2> points;

	b2PolygonShape* shape = dynamic_cast<b2PolygonShape *>(caja->GetFixtureList()->GetShape());
	points.insert(points.begin(),caja->GetWorldPoint(b2Vec2(shape->GetVertex(0).x, shape->GetVertex(0).y)));
	points.insert(points.begin(), caja->GetWorldPoint(b2Vec2(shape->GetVertex(1).x, shape->GetVertex(1).y)));
	points.insert(points.begin(), caja->GetWorldPoint(b2Vec2(shape->GetVertex(2).x, shape->GetVertex(2).y)));
	points.insert(points.begin(), caja->GetWorldPoint(b2Vec2(shape->GetVertex(3).x, shape->GetVertex(3).y)));

	sf::VertexArray estela;

	while (window.isOpen()){
		
		window.clear(sf::Color::Black);
		world.Step(TIMESTEP, VELITER, POSITER);

		caja->SetTransform(caja->GetPosition(), atan(caja->GetLinearVelocity().y / caja->GetLinearVelocity().x));
		b2PolygonShape* shape = dynamic_cast<b2PolygonShape *>(caja->GetFixtureList()->GetShape());
		b2Vec2 p1 = caja->GetWorldPoint(b2Vec2(shape->GetVertex(0).x, shape->GetVertex(0).y)),
			   p2 = caja->GetWorldPoint(b2Vec2(shape->GetVertex(3).x, shape->GetVertex(3).y));
		points.insert(points.begin(), p1);
		points.insert(points.begin(), p2);

		if (points.size() > 60) {
			points.pop_back();
			points.pop_back();
			points.pop_back();
			points.pop_back();
		}

		estela = sf::VertexArray(sf::TrianglesStrip, points.size());
		auto cont = 0;
		auto aplha = 255;
		auto downgrade = aplha / points.size();
		for (auto it = points.begin(); it != points.end(); it++) {
			estela[cont].position = sf::Vector2f(it->x* PPM, it->y* PPM);
			estela[cont].color = sf::Color(255, 255, 255, aplha);
			aplha -= downgrade;
			cont++;
		}


		float angle = caja->GetAngle();
		b2Vec2 pos = caja->GetPosition();

		window.draw(estela);

		window.display();
	}
}