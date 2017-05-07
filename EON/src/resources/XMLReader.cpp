#include "physicbodies\PBWall.h"
#include "VWall.h"
#include "XMLReader.h"
#include "tinyxml2.h"
#include "Map.h"
#include <iostream>

const Layer2Method XMLReader::m_layers[5] = {
	 { "Player"       , &AddPlayer    }
	,{ "Enemies"      , &AddEnemy     }
	,{ "Walls"        , &AddWall      }
	,{ "DeadWalls"    , &AddDeadWall  }
	,{ "0"            , 0             }
};
XMLReader::XMLReader()
	:m_map(nullptr), m_x(0), m_y(0), m_width(0), m_height(0) {
}
XMLReader::~XMLReader(){
}
void XMLReader::Inicialize(Map* map,const char* path) {
	m_map = map;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(path);
	tinyxml2::XMLElement* mapLayer = doc.FirstChildElement("map");
	tinyxml2::XMLElement* objectGroups = mapLayer->FirstChildElement("objectgroup");
	if(objectGroups) do {
		tinyxml2::XMLElement* object = objectGroups->FirstChildElement("object");
		const char *layer = objectGroups->Attribute("name");
		if(object) do {
			 m_x =        object->FloatAttribute("x");
			 m_y =        object->FloatAttribute("y");
			 m_width =    object->FloatAttribute("width");
			 m_height =   object->FloatAttribute("height");
			 m_rotation = object->FloatAttribute("rotation");
			 const Layer2Method * it = m_layers;
			 while (it->layer != "0") {
				 if (strcmp(it->layer, layer) == 0) {
					 (this->*it->Layer2Method::p)();
					 break;
				 }
				 it++;
			 }
		}while (object = object->NextSiblingElement("object"));
	} while (objectGroups = objectGroups->NextSiblingElement("objectgroup"));
}
void XMLReader::AddPlayer() {
	m_map->CreatePlayer(Vec2(m_x,m_y));
}
void XMLReader::AddEnemy() {
}
void XMLReader::AddWall() {
	m_map->CreateWall(Vec2(m_x,m_y), Vec2(m_width,m_height),m_rotation);
}
void XMLReader::AddDeadWall() {

}