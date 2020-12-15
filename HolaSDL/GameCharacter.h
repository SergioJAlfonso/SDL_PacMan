#pragma once
#include "GameObject.h"
#include <list>
#include <iostream>

class GameCharacter: public GameObject
{
protected:
	Point2D ini;
	Vector2D dir;
	int	speed;
	Texture* texture;
	int frameRow, frameCol, frameBase;
	list<GameObject*>::iterator it;
	GameCharacter(Point2D pos, int w, int h, Game* g, Point2D ipos, int v);
	GameCharacter(ifstream& file, Game* g);
	virtual void changeTexture();
public:
	virtual void update();
	virtual void render();
	virtual void saveToFile(ifstream& file);
	virtual Point2D getAct() const { return pos; }
	virtual void setItList(list<GameObject*>::iterator iter) { it = iter; };
};