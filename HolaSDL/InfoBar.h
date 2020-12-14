#pragma once
#include "GameObject.h"
class Game;

class InfoBar : public GameObject
{
private:
	const int frameRowP = 0;
	const int frameColP = 11;

	int lives;
	int score;
	Texture* livesT;
	Texture* scoreT;

	int frameRowS = 0;
	int frameColS = 0;

public:
	InfoBar(Point2D pos, int w, int h, Game* g, Texture* l, Texture* point, int vidas, int puntuacion);
	virtual void render();
	virtual void update();
	void setHp(int v);
	void addPoint(int p);
};

