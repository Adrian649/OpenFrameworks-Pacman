#include "GameState.h"
#include "Entity.h"
#include "RandomGhost.h"

GameState::GameState()
{
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick()
{
	if (!music.isPlaying())
	{
		music.play();
	}
	map->tick();
	if (map->getPlayer()->getHealth() == 0)
	{
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	else if (map->getPlayer()->getScore() == 4680)
	{
		setFinished(true);
		setNextState("win");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	else if (getNextState() == "pause")
	{
		setNextState("pause");
		setFinished(true);
	}
	score = map->getPlayer()->getScore(); 
	map->getGhostSpawner()->score = score;
	map->getEntityManager()->playerPositionX = map->getPlayer()->getPos();
	map->getEntityManager()->playerPositionX = map->getPlayer()->getPosY();
}
void GameState::render()
{
	map->render();
}

void GameState::keyPressed(int key)
{
	map->keyPressed(key);
	if (key == 'y')
	{
		setFinished(true);
		setNextState("win");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	else if (key == 'p')
	{
		isPaused = true;
		setNextState("pause");
		setFinished(true);
	}
}

void GameState::mousePressed(int x, int y, int button)
{
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key)
{
	map->keyReleased(key);
}

void GameState::reset()
{
	setFinished(false);
	setNextState("");
	if (!isPaused)
	{
		delete map;
		map = MapBuilder().createMap(mapImage);
	}
}

int GameState::getFinalScore()
{
	return finalScore;
}

GameState::~GameState()
{
	delete map;
}