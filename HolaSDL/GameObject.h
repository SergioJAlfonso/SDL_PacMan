#pragma once

#include "Vector2D.h"
#include "Texture.h"
class Game;

class GameObject
{
protected:
	Point2D pos;
	int width, height;
	Game* game;
public:
	GameObject() : pos(Point2D(0, 0)), width(0), height(0), game(nullptr){};
	GameObject(Point2D pos, int w, int h, Game* g) : pos(pos), width(w), height(h), game(g) {};
	virtual ~GameObject() {};
	virtual void update() = 0;
	virtual void render() = 0;
	virtual SDL_Rect getDestRect() { return SDL_Rect{ pos.getX(), pos.getY(), width, height }; };
};