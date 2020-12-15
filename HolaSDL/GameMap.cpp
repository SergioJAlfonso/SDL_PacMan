#include "GameMap.h"
#include "Game.h"

GameMap::GameMap(Point2D pos, int w, int h, Game* g) : GameObject(pos,w,h,g) {
	createMap(h, w);
}

GameMap::~GameMap() {
	removeMap();
}

void GameMap::setCell(MapCell cell, Point2D pos){
	map[pos.getX()][pos.getY()] = cell;
}

void GameMap::setCell(MapCell cell, int posX, int posY){
	map[posX][posY] = cell;
}

void GameMap::render() {
	SDL_Rect rect;
	rect.w = cellSize;
	rect.h = cellSize;

	int x;

	for (int i = 0; i < height; ++i) {
		for (int e = 0; e < width; ++e) {
			rect.x = (e + offsetX) * cellSize;
			rect.y = (i + offsetY) * cellSize;
			x = map[e][i];
			if (x != 0) {
				if (x == 1) x = 0;
				game->getTexture(x)->render(rect);
			}
		}
	}
}

void GameMap::removeMap() {
	for (int i = 0; i < width; i++) {
		delete[] map[i];
	}
	delete[] map;
}

void GameMap::createMap(int h, int w) {
	height = h;
	width = w;

	map = new MapCell* [w];
	for (int i = 0; i < w; i++) {
		map[i] = new MapCell[h];
	}
}

SDL_Rect GameMap::getDestRect() {
	return SDL_Rect{ pos.getX() * cellSize, pos.getY() * cellSize, width * cellSize, height * cellSize };
}

bool GameMap::intersectsWall(SDL_Rect rect) {
	Point2D topLeft = game->SDLPointToMapCoords(rect.x, rect.y);
	Point2D botRight = game->SDLPointToMapCoords(rect.x + rect.w, rect.y + rect.h);

	for(int i = topLeft.getX(); i <= botRight.getX(); ++i)
		for (int j = topLeft.getY(); j <= botRight.getY(); ++j)
			if (map[i][j] == Wall)
				return true;
	
	return false;
}