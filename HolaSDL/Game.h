#ifndef Game
#define GAME

#include <fstream>
#include <array>
#include "checkML.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"
#include "InfoBar.h"
#include <list>

using namespace std;

using uint = unsigned int;

struct TextureAtribs {
	string filename;
	int numRows;
	int numCols;
};

enum textureName{WallText, CharactersText, FoodText, BurguerText, DigitsText};
enum dirs { Right, Down, Left, Up };
enum levelState {Playing, LevelPassed};

const int offsetX = 0;
const int offsetY = 1;

const uint maxEnergy = 101;
const uint maxHp = 3;

const uint numTextures = 5;
//const uint numGhosts = 4;

// Frames animación pacman
const uint frameBasePacman = 10;
const uint frameRowPacman = 0;
const uint frameColPacman = 10;

const TextureAtribs TEXTURES_ATRIBS[numTextures] = { {"wall.png",1,1} , {"characters.png",4,14}, {"food.png",1,1}, {"vitamin.png",1,1}, {"digits.jpeg",3,4} };

const uint DELAY = 100;
const int cellSize = 32;
const uint winWidth = cellSize * cellSize;
const uint winHeight = cellSize * cellSize;

const string saveFile = "save.txt";
const string firstLevel = "level01.dat";
const string levelDir = "..\\levels\\";

const uint ghostSpeed = 1;
const uint pacmanSpeed = 10;

class Game
{
private:
	int actualLevel; //Guarda el nº del nivel en que se está jugando

	levelState levelS; //Refleja el estado del nivel actual

	SDL_Window* window;
	SDL_Renderer* renderer;

	array<Texture*, numTextures> textures;
	//array<Ghost*, numGhosts> ghosts;

	uint cellsLeft;

	bool exit = false;

	GameMap* map;
	Pacman* pacman;
	InfoBar* info;

	list<Ghost*> ghosts;
	list<GameObject*> objects;
	list<list<GameObject*>::iterator> objectsToErase;

	/*list<GameObject*>::iterator map;
	list<GameObject*>::iterator pacman;
	list<GameObject*>::iterator info;*/

	bool powerUp;
	int actualEnergy;

	int lives;
	int score;

public:
	Game();
	~Game();
	void run();
	void eatCell(Point2D pos);
	//MapCell checkCell(Point2D pos) const;
	bool tryMove(const SDL_Rect& rect, Vector2D dir, Point2D& newPos);
	Texture* getTexture(int t) const;
	bool win() const;
	void unpowerGhosts();
	void loadMap(string file);
	Point2D mapCoordsToSDLPoint(Point2D coord);
	Point2D SDLPointToMapCoords(Point2D point);
	Point2D mapCoordsToSDLPoint(int x, int y);
	Point2D SDLPointToMapCoords(int x, int y);
	void Game::eraseGhost(list<GameObject*>::iterator it);
private:
	void saveGame();
	void loadSavedGame();
	void render();
	void update();
	void handleEvents();
	list<Ghost*>::iterator checkCollisions();
	void loadObj(int code, int h, int w);
	void kill(list<Ghost*>::iterator it);
	void checkExit();
	void loadNextLevel();
};
#endif

