#include "InfoBar.h"
#include "Game.h"
#include <iostream>

InfoBar::InfoBar(Point2D pos, int w, int h, Game* g, Texture* l, Texture* point, int vidas, int puntuacion) : GameObject(pos, w, h, g) {
	livesT = l;
	scoreT = point;
	lives = vidas;
	score = puntuacion;
}

void InfoBar::render() {
	SDL_Rect rect;
	rect.w = cellSize;
	rect.h = cellSize;
	rect.y = 0;
	//Dibujar vidas
	for (int i = 0; i < lives; i++){
		rect.x = i * cellSize;
		livesT->renderFrame(rect, frameRowP, frameColP);
	}

	//Dibujar puntos
	/*  ROW - - ->
		0 1 2 3 COL
		4 5 6 7  |
		8 9 X X  v
	*/

	int aux = score;
	int x = winWidth / cellSize;

	do {
		frameColS = aux % 10;
		aux = aux / 10;
		
		x--;
		rect.x = x * cellSize; //Columna de posición
		
		frameRowS = 0;

		if (frameColS > 3 && frameColS < 8) { //Cálculo de columnas y filas del frame
			frameColS -= 4;
			frameRowS = 1;
		}
		else if(frameColS > 7){
			frameColS -= 8;
			frameRowS = 2;
		}

		scoreT->renderFrame(rect, frameRowS, frameColS);
	} while (aux != 0);
}

void InfoBar::setHp(int v) {
	lives = v;
}

void InfoBar::addPoint(int p) {
	score += p;
}
void InfoBar::update(){}