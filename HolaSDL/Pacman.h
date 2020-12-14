#pragma once
#include "GameCharacter.h"

class Pacman: public GameCharacter
{
private:
	int energy;
	Vector2D nextDir;
public:
	Pacman(Point2D pos, int w, int h, Game* g, Point2D ipos, int v);
	//Pacman(int h, int e, Point2D init, Texture* text, Game* gam);
	virtual void update();
	//virtual void render();
	void die();
	void handleEvent();
	//Activa el temporizador del PowerUp
	void powerUp();
private:
	void move(const Point2D& newPos);
	//Cambia la textura de Pacman en funcion de dir
	void changeTexture(Vector2D const& dir);
};