#include "Ghost.h"
#include "Game.h"
#include <cstdlib>
#include <vector>


Ghost::Ghost(Point2D pos, int w, int h, Game* g, Point2D ipos, int v, int c) : GameCharacter(pos, w, h, g, ipos, v){
	frameBase = frameCol = c * 2 + 1; //Cálculo de la textura
	frameRow = 0;
}

void Ghost::update() {
	vector <Vector2D> posDirs; //Almacena direcciones posibles

	Point2D newPos = pos;
	if (game->tryMove(getDestRect(), dir, newPos)) {  //Guardamos la dir actual si puede seguir
		posDirs.push_back(dir);
	} 
		
	Vector2D newDir;

	//Tomamos una direccion en el eje opuesto de dir
	if (dir.getX() != 0) 
		newDir.set(0, -1);
	else
		newDir.set(-1, 0);

	newPos = pos;

	//Se comprueba dicha direccion
	if (game->tryMove(getDestRect(), newDir, newPos))
		posDirs.push_back(newDir);

	//Cogemos la opuesta en el mismo eje
	newDir = newDir * -1; 

	newPos = pos;
	//Volvemos a comprobar
	if (game->tryMove(getDestRect(), newDir, newPos))
		posDirs.push_back(newDir);

	//En caso de haber +1, se elige al azar
	if (posDirs.size() > 1) {
		int e = rand() % posDirs.size();
		dir = posDirs[e];
	}
	//Si sólo hay 1, es seguir adelante
	else if (posDirs.size() == 1) {
		dir = posDirs[0];
	}
	//Si no hay, damos la vuelta
	else {
		dir = dir * -1;
	}

	//Realizamos movimiento
	pos = pos + dir * speed;

	changeTexture(dir);
}

void Ghost::render() {

}

void Ghost::vulnerable() {
	if (frameCol != frameBase) {
		frameCol = frameBase;
	}
	else {
		frameRow = 0; //Resetea la fila
		frameCol = frameVul;
	}
}

//Animación de los fantasmas 
void Ghost::changeTexture(Vector2D const &dir) {
	if (frameCol == frameBase){
		if (dir.getX() != 0) {
			if (dir.getX() > 0){
				frameRow = Right;
			}
			else{
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
	}
}