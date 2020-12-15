#pragma once
#include "GameCharacter.h"

class Ghost: public GameCharacter
{
private:
	const int frameVul = 13;
public:
	Ghost(Point2D pos, int w, int h, Game* g, Point2D ipos, int v, int c);
	virtual void update();
	virtual SDL_Rect getDestRect() { return SDL_Rect{ pos.getX(), pos.getY(), width, height }; };
	void die() {pos = ini;} // El fantasma vuelve a su pos inicial
	void vulnerable();
private:
	void changeTexture();
};