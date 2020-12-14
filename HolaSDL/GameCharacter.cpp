#include "GameCharacter.h"
#include "Game.h"

GameCharacter::GameCharacter(Point2D pos, int w, int h, Game* g, Point2D ipos, int v) : GameObject(pos, w, h, g), ini(ipos), speed(v) { 
	texture = game->getTexture(CharactersText); 
}


void GameCharacter::render() {
	SDL_Rect rect;
	rect.w = cellSize;
	rect.h = cellSize;
	rect.x = pos.getX();
	rect.y = pos.getY();

	texture->renderFrame(rect, frameRow, frameCol);
}

void GameCharacter::update() {}

GameCharacter::GameCharacter(ifstream& file, Game* g) {
	int xPos, yPos, xIni, yIni;
	
	file >> xPos >> yPos >> width >> height >> xIni >> yIni >> speed;
	
	pos.set(xPos, yPos);
	ini.set(xIni, yIni);

	game = g;
	texture = game->getTexture(CharactersText);
}

void GameCharacter::saveToFile(ifstream& ifs) {
	//ifs << pos.getX() << pos.getY() << " " << width << " " << height << " " << ini.getX() << ini.getY() << " " << speed;

}

