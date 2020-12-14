#include "SmartGhost.h"
#include "Game.h"

void SmartGhost::update() {
	handleState();
	switch (state) {
		case Child:

			break;
		case Adult:

			break;
		case Quarantine:

			break;
		case Dead:

			break;
	}
}

void SmartGhost::handleState() {
	if (deadTime == 0 && state == Dead) game->eraseGhost(it);
}