//#ifndef GameMap
//#define GAMEMAP
#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "SDL.h"

enum MapCell { Empty, Wall, Food, Vitamins };

class GameMap: public GameObject
{
	friend class Game;
private: //Sólo usada por Game (friend)
	MapCell** map;

	GameMap(Point2D pos, int w, int h, Game* g);
	~GameMap();
	void setCell(MapCell cell, Point2D pos);
	void setCell(MapCell cell, int posX, int posY);
	MapCell getCell(Vector2D pos) const { return map[pos.getX()][pos.getY()]; };
	MapCell getCell(int x, int y) const { return map[x][y]; };
	
	virtual void render();
	virtual void update() {};
	virtual SDL_Rect getDestRect();

	void removeMap();
	void createMap(int h, int w);
	bool intersectsWall(SDL_Rect rect);
};
//#endif