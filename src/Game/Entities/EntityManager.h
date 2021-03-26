#pragma once

#include "BoundBlock.h"

class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> BoundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);
	vector<Entity*> getEntities();
	void getPlayerScore();
	bool flag = false;
	int randGhostCount = 0;
	int normalGhostCount = 4;
	int counter = 0;
    int PosX;
	int PosY;
private:
	bool killable = false;
	int killableCounter;
};