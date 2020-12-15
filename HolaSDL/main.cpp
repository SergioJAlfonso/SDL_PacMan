//Sergio José Alfonso Rojas
//Daniel Illanes Morillas
//Grupo 15
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <cstdlib>
#include <iostream>
#include "Game.h"

using namespace std;
const int LEVELS = 5;
using uint = unsigned int;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	int cont = 1;

	string s = "level01.dat";
	
	Game g; //PUNTERO INNECASRIO--------

	// Crea un puntero a Game y ejecuta run por cada nivel //TRY CATCH----------
	while(cont <= LEVELS){
		//Iterador de niveles
		g.run();
		if (g.win()) {
			++cont;
			s = "level";
			if (cont < 10) s += "0";
			s += to_string(cont) + ".dat";
		}	
	}
	return 0;
}