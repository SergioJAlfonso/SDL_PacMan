#include "Game.h"
#include <iostream>

Game::Game(){
	//Inic. SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr) throw string("Error inicializando SDL"); 

	//Creación texturas
	for (int i = 0; i < numTextures; ++i) {
		textures[i] = new Texture(renderer, TEXTURES_ATRIBS[i].filename, TEXTURES_ATRIBS[i].numRows, TEXTURES_ATRIBS[i].numCols);
	}

	cellsLeft = 0;
	actualLevel = 1;

	lives = maxHp;
	score = 0;

	actualEnergy = 0;
	powerUp = false;

	info = new InfoBar(Point2D(0,0), cellSize, cellSize ,this, textures[CharactersText], textures[DigitsText], lives, score);
	objects.push_back(info);

	loadMap(firstLevel);
	
	//for (int i = 0; i < numGhosts; i++) {
	//	ghosts[i] = nullptr;
	//}
}

Game::~Game(){ //MEJOR DESTRUCTORA -------------
	delete map;
	delete pacman;

	//for (int i = 0; i < numGhosts; ++i) {
	//	delete ghosts[i];
	//}

	for (int i = 0; i < numTextures; ++i) {
		delete textures[i];
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Carga el mapa a partir de un archivo de texto
void Game::loadMap(string file) {
	cellsLeft = 0;
	ifstream input;
	file = levelDir + file; 
	input.open(file);
	if (!input.is_open()) throw string("Error opening: " + file);
	else {
		int h, w, cell;
		
		input >> h;
		input >> w;

		//if (map != nullptr)
			//map->remake(h, w);
		//else {
		map = new GameMap(Point2D(offsetX, offsetY), w, h, this);
		objects.push_back(map);
		//}

		for (int i = 0; i < h; ++i) {
			for (int e = 0; e < w; ++e) {
				input >> cell;
				if (cell > 3) { // Si hay un objeto móvil, se trata de una casilla vacía					
					loadObj(cell, e, i);
					cell = 0;
				}
				map->setCell((MapCell)cell, e, i); 
				if (cell >= 2){ // Si es comida o vitaminas se añade 1 al num de celdas que quedan por comer
					cellsLeft++;
				}
			}
		}
	}
	input.close();
}
//Carga los objetos móviles dependiendo de code
void Game::loadObj(int code, int h, int w) { 
	Point2D pos(h, w);
	pos = mapCoordsToSDLPoint(pos);
	Ghost* g;
	switch (code) {
	case(5):
	case(6):
	case(7):
	case(8):
		/*g = new Ghost(pos, cellSize, cellSize, this, pos, ghostSpeed, code - 5);
		storeGhost(g);*/
		break;
	case(9):
		pacman = new Pacman(pos, cellSize, cellSize, this, pos, pacmanSpeed);
		objects.push_back(pacman);
		break;
	}
}

Texture* Game::getTexture(int t) const {
	//if (t > 5 || t < 0) return nullptr;
	return textures[t];
}


void Game::run() { // Ejcuta el bucle principal de juego
	uint startT = SDL_GetTicks();
	exit = false;
	while (!exit) {
		if ((SDL_GetTicks() - startT) > DELAY) {
			handleEvents();
			render();
			update();
			checkExit();
			startT = SDL_GetTicks();
		}
	}

	//if (!win()) info->reset();
}

void Game::update() {
	//for (Ghost* g: ghosts) {
	//	g->update();
	//}
	//kill(checkCollisions()); //Comprueba la colisiones antes y despues del movimiento para evitar comportamientos inadecuados
	//pacman->update();
	//kill(checkCollisions());

	for (GameObject* o : objects) o->update();
	for (auto it: objectsToErase) {
		delete *it;
		objects.erase(it);
	}
	objectsToErase.clear();
	if (levelS == LevelPassed) {
		/*if (...);
		else loadNextLevel();*/
	}
}

//Ejecuta la gestión de eventos en cada clase 
void Game::handleEvents() { 
	pacman->handleEvent();
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (GameObject* o : objects) o->render();
	SDL_RenderPresent(renderer);
}

////Comprueba qué es la casilla dada por pos
//MapCell Game::checkCell(Point2D pos) const{ 
//	return map->getCell(pos.getX(), pos.getY()); //MEJORAR --------------------
//}

//Comprueba que la casilla dada por pos no es pared
bool Game::tryMove(const SDL_Rect& rect, Vector2D dir, Point2D& newPos){ 
	SDL_Rect mapRect = map->getDestRect();
	newPos = newPos + dir;

	//Toroide
	if (dir.getX() > 0 && (newPos.getX() + rect.w) >= mapRect.x + mapRect.w){
		newPos.set(mapRect.x, newPos.getY());
	}
	else if (dir.getX() < 0 && newPos.getX() < mapRect.x) {
		newPos.set(mapRect.x + mapRect.w - cellSize, newPos.getY());
	}
	else if (dir.getY() > 0 && (newPos.getY() + rect.h) >= mapRect.y + mapRect.h) {
		newPos.set(newPos.getX(), mapRect.y);
	}
	else if (dir.getY() < 0 && newPos.getY() <= mapRect.y) {
		newPos.set(newPos.getX(), mapRect.y + mapRect.h - cellSize);
	}

	SDL_Rect newRect{newPos.getX(), newPos.getY(), rect.w, rect.h};

	return !(map->intersectsWall(newRect));
}

Point2D Game::mapCoordsToSDLPoint(Point2D coords){
	Point2D SDLPoint{coords.getX() * cellSize + offsetX * cellSize, coords.getY() * cellSize + offsetY * cellSize};
	return SDLPoint;
}

Point2D Game::SDLPointToMapCoords(Point2D point){
	Point2D SDLPoint{ point.getX() / cellSize - offsetX, point.getY() / cellSize - offsetY};
	return SDLPoint;
}

Point2D Game::mapCoordsToSDLPoint(int x, int y) {
	Point2D SDLPoint{ x * cellSize + offsetX * cellSize, y * cellSize + offsetY * cellSize };
	return SDLPoint;
}

Point2D Game::SDLPointToMapCoords(int x, int y) {
	Point2D SDLPoint{ x / cellSize - offsetX, y / cellSize - offsetY};
	return SDLPoint;
}

//Vacía casillas con vitaminas o comida
void Game::eatCell(Point2D pos) { // COSA DE MEJORAR EN EL FUTURO AAAAAAAAAAAAAAASAAAASDA
	pos = SDLPointToMapCoords(pos);
	int i = map->getCell(pos);
	if (i == Food || i == Vitamins){
		if (i == Vitamins){ // Activa el powerUp
			pacman->powerUp();
			info->addPoint(4);
			if(!powerUp) unpowerGhosts(); //Si ya estaba activo, no se cambia la txt de los ghosts
		}
		map->setCell(Empty, pos);
		info->addPoint(1);
		cellsLeft--;
	}
}

 //Devuelve el iterador del fantasma con el que colisiona, ghosts.end() en caso contrario
list<Ghost*>::iterator Game::checkCollisions() {
	SDL_Rect pacRect = pacman->getDestRect();

	int leftP, leftG;
	int rightP, rightG;
	int topP, topG;
	int bottomP, bottomG;

	leftP = pacRect.x;
	rightP = pacRect.x + pacRect.w;
	topP = pacRect.y;
	bottomP = pacRect.y + pacRect.h;

	for (auto it = ghosts.begin(); it != ghosts.end(); ++it) {
		SDL_Rect gRect = (*it)->getDestRect();
		
		leftG = gRect.x;
		rightG = gRect.x + gRect.w; 
		topG = gRect.y;
		bottomG = gRect.y + gRect.h; 
		
		if (((bottomP <= topG) || (topP >= bottomG) || (rightP <= leftG) || (leftP >= rightG)) == false){
			//A collision is detected
			return it;
		}
	}
	return ghosts.end();
}

void Game::kill(list<Ghost*>::iterator it) {
	if (it != ghosts.end()) {
		if (actualEnergy > 0){
			(*it)->die();
			info->addPoint(10);
		}
		else {
			pacman->die(); //Al morir Pacman, reseteamos todos los fantasmas
			info->setHp(lives); // Actualiza InfoBar
			for (Ghost* g : ghosts) g->die(); //Reseteamos a los fantasmas
		}
		SDL_Delay(75); //Feedback visual al comer o ser comido
	}
}


void Game::unpowerGhosts() {
	for (Ghost* g : ghosts) g->vulnerable();
	powerUp = !powerUp;
}

//Cambia exit
void Game::checkExit() {
	exit = (cellsLeft == 0); //Si no queda comida, obviamos la vida
	if(!exit)
		exit = lives == 0; //Si no quedan vidas, acaba el juego
}

//Comprueba si se ha ganado
bool Game::win() const {
	return cellsLeft == 0;
}

void Game::saveGame() {
	ifstream ifs (saveFile, ifstream::in);
	ifs.open(saveFile);
	for (GameObject* o : objects) {
		GameCharacter* c = dynamic_cast<GameCharacter*>(o);
		if (c != nullptr) c->saveToFile(ifs);
	}
	ifs.close();
}

void Game::loadNextLevel() {
	for (GameObject* o : objects) delete o;
	objects.clear();
	ghosts.clear();
	//loadLevelFile("x");
}

void Game::loadSavedGame() {
	ifstream file;
	file.open(saveFile);
	//...
	//map = new GameMap(file);
	//pacman = new Pacman(file);
	file.close();
}

void Game::storeGhost(Ghost* g) {
	auto it = objects.insert(objects.end(), g);
	g->setItList(it);
	ghosts.push_back(g);
}

void Game::eraseGhost(list<GameObject*>::iterator it) {
	ghosts.remove(static_cast<Ghost*>(*it));
	objectsToErase.push_back(it);
}