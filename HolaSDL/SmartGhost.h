#pragma once
#include "Ghost.h"
class SmartGhost: public Ghost
{
protected:
	enum State {Child, Adult, Quarantine, Dead};
	State state = Child;
	int deadTime;
public:
	SmartGhost();
	void update();
	void handleState();
};

