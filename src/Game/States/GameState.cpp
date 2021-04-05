#include "GameState.h"
#include "Entity.h"
#include "RandomGhost.h"

GameState::GameState()
{
	music.load("music/pacman_chomp.wav");
	BonusMusic.load("music/Megalovania.mp3");
	mapImage.load("images/map1.png");
	level2.load("images/level1.png");
	SansLevel.load("images/mapSans.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick()
{
	if (hasStarted)
	{
		for (Entity *entity : map->getEntityManager()->entities)
		{
			if (dynamic_cast<Dot *>(entity))
			{
				totalDots += 1;
			}
			if (dynamic_cast<BigDot *>(entity))
			{
				totalDots += 1;
			}
		}
		hasStarted = false;
	}
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
		BonusMusic.setPaused(true);
	}
	else if (map->getPlayer()->removedDots == (totalDots - map->getEntityManager()->removedDots) && totalDots != 0)
	{
		mapCounter += 1;
		if (mapCounter == 2) {
			secondMapLoad();
			BonusMusic.setPaused(true);
		}
		if (mapCounter == 3)
		{
			bonusMapLoad();
			BonusMusic.play();
			BonusMusic.setLoop(true);
			BonusMusic.setPaused(false);
		}
		hasStarted = true;
		totalDots = 0;
		if (mapCounter == 4)
		{
			setFinished(true);
			setNextState("win");
			map->getPlayer()->setHealth(3);
			finalScore = map->getPlayer()->getScore();
			map->getPlayer()->setScore(0);
			BonusMusic.setPaused(true);
		}
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
		BonusMusic.setPaused(true);
	}
	else if (key == 'p')
	{
		isPaused = true;
		setNextState("pause");
		setFinished(true);
	}
	else if (key == '1')
	{
		hasStarted = true;
		totalDots=0;
		secondMapLoad();
		BonusMusic.setPaused(true);
	}
	else if (key == '2')
	{
		hasStarted = true;
		totalDots=0;
        bonusMapLoad();
		BonusMusic.play();
		BonusMusic.setLoop(true);
		BonusMusic.setPaused(false);
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

void GameState::secondMapLoad()
{
	delete map;
	map = MapBuilder().createMap(level2);
	Player *n = map->getPlayer();
	n->setScore(n->getScore() + score);
}
void GameState::bonusMapLoad(){
	delete map;
	map = MapBuilder().createMap(SansLevel);
	Player *n = map->getPlayer();
	n->setScore(n->getScore() + score);
}
