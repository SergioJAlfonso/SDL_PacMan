#include "Pacman.h"
#include "Game.h"
#include <iostream>

//Constructora de la clase
Pacman::Pacman(Point2D pos, int w, int h, Game* g, Point2D ipos, int v) : GameCharacter(pos, w, h, g, ipos, v), nextDir(Vector2D(0, 0)){
	frameRow = frameRowPacman;
	frameBase = frameBasePacman;
	frameCol = frameColPacman;
	energy = 0;
}

//void Pacman::render() {
//	GameCharacter::render();
//}

void Pacman::update(){
	//Si la siguiente dirección a avanzar es viable
	Point2D newPos = pos;
	if (game->tryMove(getDestRect(), nextDir * speed, newPos)) {  
		move(newPos);
	}
	else if (game->tryMove(getDestRect(), dir * speed, newPos)) { 
		move(newPos);
	}
	/*if (energy > 0) {
		if (energy == 1) game->unpowerGhosts();
		energy--;
	}*/
}

//Mueve a Pacman en la dir actual 
void Pacman::move(const Point2D& newPos) {
	pos = newPos;
	game->eatCell(pos);
	changeTexture(dir);
}
void Pacman::powerUp(){ 
	energy = maxEnergy; 
}

//Gestiona el input, de manera que cambia la próxima dirección de pacman (nextDir) dependiendo de la flecha presionada
void Pacman::handleEvent() {  
	SDL_Event e;
	if (SDL_PollEvent(&e) != 0)
	{
		//User presses a key
		if (e.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				nextDir.set(0, -1);
				break;
			case SDLK_DOWN:
				nextDir.set(0, 1);
				break;
			case SDLK_LEFT:
				nextDir.set(-1, 0);
				break;
			case SDLK_RIGHT:
				nextDir.set(1, 0);
				break;
			default:
				break;
			}

			//cout << "(" << act.getX() << ", " << act.getY() << ")"<< endl;
		}
	}
}

//Resta una vida y resetea la posicion del pacman
void Pacman::die() {
	pos = ini;
}

//Animación del pacman dependiendo de la dirección
void Pacman::changeTexture(Vector2D const& dir) {
	if (dir.getX() != 0) {
		if (dir.getX() > 0) {
			frameRow = Right;
		}
		else {
			frameRow = Left;
		}
	}
	else {
		if (dir.getY() > 0) {
			frameRow = Down;
		}
		else {
			frameRow = Up;
		}
	}

	if (frameCol == frameBase) //Animación de abrir y cerrar boca
		frameCol++;
	else
		frameCol = frameBase;
}