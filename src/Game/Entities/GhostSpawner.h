#pragma once

#include "EntityManager.h"

class GhostSpawner: public Entity{
    public:
        GhostSpawner(int, int, int , int, EntityManager*, ofImage);
        void spawnGhost(string);
        void spawnRandomGhost(int, int, string);
        void randomGhostSpawner();
        void spawnPeekABooGhost(string);
        EntityManager* getEntityManager();
        void keyPressed(int);
        void tick();
        string random_color;
        int score = 0;
        bool flag = false;
        bool peekABooFlag = false;
        
    private:
        EntityManager* em;
        int spawnCounter = 30*5;

};