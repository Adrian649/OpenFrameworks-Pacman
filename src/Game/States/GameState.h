#pragma once
#include "State.h"
#include "Player.h"
#include "MapBuilder.h"

class GameState: public State{
    public: 
        GameState();
		~GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		int getFinalScore();
		void spawnRandomGhost();
		void secondMapLoad();
		bool flag = false;
		bool hasStarted = true;
		int score = 0;
		int totalDots = 0;
		int mapCounter = 1;
	
	private:
		ofSoundPlayer music;
		ofImage mapImage;
		ofImage level2;
		Map* map;
		int finalScore=0;

};